/*
 * keypad.h
 *
 * Created: 16.04.2018 0:02:55
 *  Author: Madina
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "structs.h"
#include <util/delay.h>

#define F_CPU 16000000UL  // 16 MHz

#define BUFFER_SIZE
struct played_note buffer[BUFFER_SIZE];
int i = 0;
int counter = 0;

//Timer1A
void play_note(unsigned int note){
	counter = 0;
	OCR1A = note;							//load calculated note number that corresponds to specific frequency
	TIMSK = (1 << OCIE1A);					//Timer1 Comparator Interrupt is enabled
	TCCR1B |= (1 << WGM12) | (1 << CS12);	//CTC mode, prescale = 256
}

ISR(TIMER1_COMPA_vect){
	// every time when timer0 reaches corresponding frequency,
	// invert the output signal for BUZ, so it creates reflection, which leads to sound generation
	PORTG = ~(PORTG);
	counter++;
	if(PIND == 0xFF){
		TIMSK &= ~(1UL << OCIE1A);
		buffer[i].counter = counter;
		buffer[i].note = OCR1A;
		i++;
	}
}

void showNotes(){
	int j = 0;
	while(j < i){
		PORTB = buffer[j++].note;
		_delay_ms(500);
	}
}


#endif /* KEYPAD_H_ */