/*
 * keypad.h
 *
 * Created: 16.04.2018 0:02:55
 *  Author: Madina
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "structs.h"
#include "play.h"


#define BUFFER_SIZE 100
struct played_note buffer[BUFFER_SIZE];
int i = 0;
int8_t isRecordingEnabled = 0;
int8_t recordIndex = 0;
int8_t pressedNote;
int8_t isPressed = 0;
int8_t isPlaying = 0;
unsigned int ms_count = 0;

#define INTERVAL 1
#define DELAY_VALUE 0xFF

void toggleLED();

void initTimer1();
void stopTimer1();

void enableRecording();
void disableRecording();

void play_record();
//using Timer1A
void play_note_during(unsigned int note, unsigned int duration);
//using Timer1A
void play_note(unsigned int note);

void initKeypads(){
	KEYPADS_ROW_DDR = 0xFF;
	KEYPADS_ROW_PORT = 0x00;
	KEYPADS_COL_DDR = 0x00;
	KEYPADS_COL_PIN = 0xFF;
}

ISR(TIMER1_COMPA_vect){
	// every time when timer0 reaches corresponding frequency,
	// invert the output signal for BUZ, so it creates reflection, which leads to sound generation
	//check whether the key was pressed because
	//when the recording is enabled the interrupt is working make sound
	if(isPressed || isPlaying)
		PORTG = ~(PORTG);
	
	if(isRecordingEnabled){
		//int temp = PIND;
		
		if(PIND == DELAY_VALUE)
			pressedNote = DELAY_VALUE;
		if(i == 0){
			buffer[i].note = pressedNote;
			buffer[i].counter = 0;
			i++;
			}else{
			if(buffer[i - 1].note == pressedNote){
				//the same note is being pressed
				buffer[i - 1].counter++;
				}else{
				buffer[i++].note = pressedNote;
				buffer[i].counter = 0;
			}
		}
	}
}

void initTimer1(){
	TIMSK = (1 << OCIE1A);					//Timer1 Comparator Interrupt is enabled
	TCCR1B |= (1 << WGM12) | (1 << CS12);	//CTC mode, prescale = 256
}

void stopTimer1(){
	TIMSK &= ~(1UL << OCIE1A);
	TCCR1A = 0;					//stop the timer1
	TIFR = (1 << OCF1A);		//Clear the timer1 Comparator Match flag
}

void enableRecording(){
	isRecordingEnabled = 1;
	i = 0;
	ms_count = 0;
	initTimer1();
}

void disableRecording(){
	isRecordingEnabled = 0;
	stopTimer1();
}

//Timer1A
void play_note_during(unsigned int note, unsigned int duration){
	OCR1A = note;
	pressedNote = note;
	
	isPressed = 1;
	
	initTimer1();
	custom_delay_ms(duration);
	stopTimer1();
	
	isPressed = 0;
}

//Timer1A
void play_note(unsigned int note){
	play_note_during(note, INTERVAL);
}

void play_record(){
	isPlaying = 1;
	recordIndex = 0;
	unsigned int duration;
	while(recordIndex < i){
		duration = INTERVAL * buffer[recordIndex].counter;
		if(buffer[recordIndex].note == DELAY_VALUE)
		custom_delay_ms(duration);
		else
		play_note_during(buffer[recordIndex].note, duration);
		recordIndex++;
	}
	isPlaying = 0;
}

#endif /* KEYPAD_H_ */