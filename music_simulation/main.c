/*
 * music_simulation.c
 *
 * Created: 14/03/2018 17:47:39
 * Author : Navruz Jandullaev, Madina Saidova, Malika Anvarjonova, Bedilbek Khamidov
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"
#include "keypad_notes.h"
#include "control_panel.h"

unsigned char temp; // to get keyboard input to play a note

#define DELAY 1000

int main(void){
	initPlay();
	initCtrlButtons();
	initKeypads();	
	HC595Init();
	
	PORTB = 0xFF;
	
	//Set Interrupt flag as enabled in SREG register
	sei();

	unsigned char i;
	unsigned char j;
	unsigned char keypad;
	
// 	while(1){
// 		play_song(happy_bday);
// 	}

	while(1){
		KEYPADS_ROW_PORT |= 0x7F;
// 		unsigned int keypad;
// 		unsigned row = -1, col = -1;
// 		for (unsigned char k = 0; k < ROW_COUNT; k++){
// 			//giving 1 to the PORT
// 			KEYPADS_ROW_PORT = (1 << k);
// 			for (unsigned char l = 0; l < COL_COUNT; l++){
// 				keypad = KEYPADS_COL_PIN;
// 				if (keypad & (1 <<  l)){
// 					play_note(keypad_notes[k][l]);
// 				}
// 			}
// 			KEYPADS_ROW_PORT &= ~(1 << i);
// 		}
	}
	
	return 0;
}