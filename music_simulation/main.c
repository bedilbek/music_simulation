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
	initKeypads();	
	initCtrlButtons();
	
	//Set Interrupt flag as enabled in SREG register
	sei();

	unsigned char i;
	unsigned char j;
	unsigned char keypad;
	
	while(1){
		for (i = 0; i < ROW_COUNT; i++){
			//giving 1 to the PORT
			KEYPADS_ROW_PORT = (1 << i);
			for (j = 0; j < COL_COUNT; j++){
				keypad = PINA;
				if (keypad & (1 <<  j)){
					//note i,j is pressed
					play_note(keypad_notes[i][j]);
					
				}
			}
			KEYPADS_ROW_PORT &= ~(1 << i);
		}
	}
	
	return 0;
}