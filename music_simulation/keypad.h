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

#define F_CPU 16000000UL  // 16 MHz
#include <util/delay.h>


#define BUFFER_SIZE
struct played_note buffer[BUFFER_SIZE];
int8_t i = 0;
int8_t counter = 0;
int8_t isRecordingEnabled = 0;
int8_t recordIndex = 0;
int8_t isPressed = 0;
int8_t pressedNote;

ISR(TIMER1_COMPA_vect){
	// every time when timer0 reaches corresponding frequency,
	// invert the output signal for BUZ, so it creates reflection, which leads to sound generation
	PORTG = ~(PORTG);
	
	if(isRecordingEnabled){
		counter += isPressed;
		if(PIND == 0xFF){
			//note was pressed and delay is started
			if(isPressed == 1){
				//store counter and note
				buffer[i] = counter;
				buffer[i] = pressedNote;
				//start new delay counting
				counter = 0;
				isPressed = -1;
				//value for delay, not possible to press all keys, so it is suitable for delay
				buffer[++i].note = 0xFF;
				buffer[i].counter = counter;
			}
		}else{
			//note is played and isPressed value is negative, so we need to store the value for delay
			if(isPressed == -1){
				//store counter of delay
				buffer[i].counter = counter;
				//start new counter for the note pressed
				counter = 0;
				isPressed = 1;
				i++;
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
	initTimer1();
}

void disableRecording(){
	isRecordingEnabled = 0;
	isPressed = 0;
	stopTimer1();
}

//Timer1A
void play_note(unsigned int note){
	OCR1A = note;
	if(isRecordingEnabled)	{
		counter = 0;
		isPressed = 1;
		pressedNote = note;
	}
				
	initTimer1();
}

//delay should be added because time between the notes are different
void play_record(){
	recordIndex = 0;
	int8_t j;
	while(recordIndex < i){
		j = 0;
		while(j < buffer[recordIndex].counter){
			play_note_timer0(buffer[recordIndex].note);
			j++;
		}
		recordIndex++;
	}
}

void showNotes(){
	int8_t j = 0;
	while(j < i){
		PORTB = buffer[j++].note;
		_delay_ms(1000);
	}
}


#endif /* KEYPAD_H_ */