/*
 * control.h
 *
 * Created: 29.04.2018 18:05:07
 *  Author: Madina
 */ 


#ifndef CONTROL_PANEL_H_
#define CONTROL_PANEL_H_

#include "avr/interrupt.h"
#include "keypad.h"
#include "ports.h"
#include "play.h"

//Timer1B
void initCtrlButtons(){
	CONTROL_BTN_PIN = 0xFF;
	CONTROL_BTN_DDR |= (1 << RECORD_PIN) | (1 << PLAY_RECORD_PIN) | (1 << PLAY_SONG);

 	EIMSK = 0xFF;
 	EICRA = 0xFF;
 	EICRB = 0xFF;
 	EIFR = 0xFF;	
}

ISR(RECORD_INT_VECTOR){
	if(isRecordingEnabled){
		disableRecording();
		CONTROL_BTN_PIN &= ~(1U << RECORD_LED);
	}else{
		enableRecording();
		CONTROL_BTN_PIN |= (1 << RECORD_LED);	
	}
}

ISR(PLAY_RECORD_VECTOR){
	play_record();
}

ISR(PLAY_SONG_VECTOR){
	play_song();
}

#endif /* CONTROL_PANEL_H_ */