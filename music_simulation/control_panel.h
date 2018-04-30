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
#include "led_control.h"

void onLED(){
	PORTB = 0x00;
}

void offLED(){
	PORTB = 0xFF;
}

void toggleLED(){
	for (unsigned char i = 0; i < 2; i++){
		onLED();
		custom_delay_ms(200);
		offLED();
		custom_delay_ms(200);
	}
}

void initCtrlButtons(){
//	CONTROL_BTN_PIN = 0xFF;
//	CONTROL_BTN_DDR |= (1 << RECORD_PIN) | (1 << PLAY_RECORD_PIN) | (1 << GAME_START_PIN) | (1 << RECORD_LED_PIN);
	
	//set rising edge for INT0-3
	//for display buttons
	EICRA = 0xFF;
	//set rising edge for INT4-7
	//for control buttons
	EICRB = 0xFF;
	//enabling external interrupts mask
 	EIMSK = 0xFF;
	//enabling external interrupts flags
 	EIFR = 0xFF;	
}

/*ISR(RECORD_INT_VECTOR){
	if(isRecordingEnabled){
		disableRecording();
		onLED();
		
		//additional LED for RECORD_BTN is off
		CONTROL_BTN_PIN &= ~(1U << RECORD_LED_PIN);
	}else{
		enableRecording();
		offLED();
		
		//additional LED for RECORD_BTN is on
		CONTROL_BTN_PIN |= (1 << RECORD_LED_PIN);	
	}
}

ISR(PLAY_RECORD_INT_VEC){
	toggleLED();
	play_record();
}

ISR(GAME_START_INT_VEC){
	led_happy_birthday();
}
*/
#endif /* CONTROL_PANEL_H_ */