/*
 * music_simulation.c
 *
 * Created: 14/03/2018 17:47:39
 * Author : Navruz Jandullaev, Madina Saidova, Malika Anvarjonova, Bedilbek Khamidov
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "keypad.h"

unsigned char temp; // to get keyboard input to play a note

unsigned char option; //to choose the embedded music to play

#define DELAY 1000

int main(void)
{
    DDRG = 0xff; // To send sound to BUZ speakers (BUZ is connected to PG.4)
	
	DDRD = 0x00; // Make it input, to get corresponding key to play a note
	PORTD = 0xff; // All bits are 1s, so no button is pressed in the beginning
	
	
	sei();					//Set Interrupt flag as enabled in SREG register
	option = no_music;		//No music is played on startup, this is default mode for free playing
	
	// This loop keeps playing forever, so the main functionality
	// of the program is below
	DDRB = 0xff;
	DDRD = 0x00; //ready for input
	while(1)
	{
		temp = PIND; //store keyboard input for temporary variable
		//PORTB = PIND;
		
		switch(temp)
		{
			case 254: {					// if 1st pin of PORTD is pressed
				play_note(notes5[0]);	// play corresponding note from octave 5 for 200ms
				break;
			}
			case 253: {					// if 2nd pin of PORTD is pressed
				play_note(notes5[1]);
				break;
			}
			case 251: {					// if 3rd pin of PORTD is pressed
				play_note(notes5[2]);
				break;
			}
			case 247: {					// if 4th pin of PORTD is pressed
				play_note(notes5[3]);
				break;
			}
			case 239: {					// if 5th pin of PORTD is pressed
				play_note(notes5[4]);
				break;
			}
			case 223: {					// if 6th pin of PORTD is pressed
				play_note(notes5[5]);
				break;
			}
			case 191: {					// if 7th pin of PORTD is pressed					
				play_note(notes5[6]);
				break;
			}
			case 127: {		
				if(isRecordingEnabled){
					disableRecording();
					toggleLED();
					custom_delay_ms(DELAY);
					toggleLED();	
					custom_delay_ms(DELAY);
					custom_delay_ms(DELAY);
					play_record();
				}else{
					toggleLED();
					enableRecording();
				}
				// if 8th pin of PORTD is pressed
				/*if (option > 3)			// check whether option is not out of range of music samples
					option = -1;
				option++;				// play next embedded music sample
				play_song(option);
				break;*/
			}
		}		
	}
	
	return 0;
}