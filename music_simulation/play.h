/*
* play.h
*
* Created: 15.04.2018 15:01:18
*  Author: Madina
*/


#ifndef PLAY_H_
#define PLAY_H_

#define F_CPU 14000000
#include "util/delay.h"

#include "ports.h"
#include "notes.h"

#define happy_bday 1	// Music option - Happy Birthday To You
#define for_elise 2		// Music option - For Elise
#define twinkle 3		// Music option - Twinkle Twinkle Little Star
#define star_wars 4		//Music option - Soundtrack from Star Wars

int option = happy_bday;

// setup a frequency on timer0 to play a given note
void play_note_timer0(unsigned int note);
// play the note with the given duration
void play(unsigned int note, unsigned int ms);
void play_happy_birthday();
void play_twinkle();
void play_for_elise();
void play_star_wars();

void custom_delay_ms(unsigned int ms);

void custom_delay_ms(unsigned int ms){
	unsigned int i,j,k;
	for (i = 0; i< ms; i++)
	for (j = 0; j < 12; j++)
	for (k = 0; k < 233; k++)
	asm("NOP");
}

void initPlay(){
	// To send sound to BUZ speakers (BUZ is connected to PB.4)
	SOUND_DDR = 0xFF;
	SOUND_PORT = 0xFF;
}

void initTimer0(){
	TIMSK = (1 << OCIE0);	//Timer0 Comparator Interrupt is enabled
	TCCR0 |= (1 << WGM01) | (1 << CS02);	//CTC mode, prescale = 256
}

void stopTimer0(){
	TIMSK &= ~(1UL << OCIE0);
	TCCR0 = 0;				//stop the timer0
	TIFR = (1 << OCF0);		//Clear the timer0 Comparator Match flag
}

//Timer0 for built-in song
void play(unsigned int note, unsigned int ms)
{
	play_note_timer0(note);		//setup note parameters on timer0 and start playing
	custom_delay_ms(ms);			//wait until note is played till the end of the duration
	stopTimer0();
}

void play_note_timer0(unsigned int note)
{
	OCR0 = note;			//load calculated note number that corresponds to specific frequency
	initTimer0();
}

ISR(TIMER0_COMP_vect)
{
	// every time when timer0 reaches corresponding frequency,
	// invert the output signal for BUZ, so it creates reflection, which leads to sound generation
	PORTG = ~(PORTG);
}


///////////////////////////////////////////////
///////////////////////////////////////////////
////////////PLAYING BUILT-IN SONGS/////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

void play_song(){
	if(option > star_wars)
	option = happy_bday;
	
	if(option == happy_bday)
	play_happy_birthday();
	else if(option == for_elise)
	play_for_elise();
	else if(option == twinkle)
	play_twinkle();
	else if(option == star_wars)
	play_star_wars();
	
	option++;
}

void play_happy_birthday(){
	play (D3, 300);
	custom_delay_ms(100);
	play (D3, 100);
	play (E3, 400);
	play (D3, 400);
	play (G3, 400);
	play (F3P, 800);
	play (D3, 400);
	custom_delay_ms(100);
	play (D3, 100);
	play (E3, 400);
	play (D3, 400);
	play (A3, 400);
	play (G3, 800);
	play (D3, 300);
	custom_delay_ms(100);
	play (D3, 100);
	play (D4, 400);
	play (B3, 400);
	play (G3, 400);
	play (F3P, 400);
	play (E3, 400);
	play (C4, 300);
	play (C4, 100);
	play (B3, 400);
	play (G3, 400);
	play (A3, 400);
	play (G3, 1200);
}

void play_twinkle(){
	play(C5, 200);
	custom_delay_ms(350);
	play(C5, 200);
	custom_delay_ms(350);
	play(G5, 200);
	custom_delay_ms(350);
	play(G5, 200);
	custom_delay_ms(350);
	play(A5, 200);
	custom_delay_ms(350);
	play(A5, 200);
	custom_delay_ms(350);
	play(G5, 200);
	custom_delay_ms(350);
	play(F5, 200);
	custom_delay_ms(350);
	play(F5, 200);
	custom_delay_ms(350);
	play(E5, 200);
	custom_delay_ms(350);
	play(E5, 200);
	custom_delay_ms(350);
	play(E5, 200);
	custom_delay_ms(350);
	play(D5, 200);
	custom_delay_ms(350);
	play(D5, 200);
	custom_delay_ms(350);
	play(C5, 500);
	custom_delay_ms(350);
	play(C5, 1000);
}

void play_for_elise(){
	//Part 1
	play(E5, 300);
	play(D5P, 300);
	play(E5, 300);
	play(B4, 300);
	play(D5, 300);
	play(C5P, 300);
	play(A4, 600);
	custom_delay_ms(300);
	
	//Part 2
	play(C4, 300);
	play(E4, 300);
	play(A4, 300);
	play(B4, 600);
	custom_delay_ms(300);
	
	//Part 3
	play(E4, 300);
	play(G4P, 300);
	play(B4, 300);
	play(C4P, 600);
	custom_delay_ms(300);
	
	//smooth move
	play(E4, 300);
	
	//Part 1
	play(E5, 300);
	play(D5P, 300);
	play(E5, 300);
	play(B4, 300);
	play(D5, 300);
	play(C5P, 300);
	play(A4, 600);
	custom_delay_ms(300);
	
	//Part 2
	play(C4, 300);
	play(E4, 300);
	play(A4, 300);
	play(B4, 600);
	custom_delay_ms(300);
	
	//Part 4
	play(E4, 300);
	play(C5P, 300);
	play(B4, 300);
	play(A4, 600);
	custom_delay_ms(300);
}

void play_star_wars(){
	play(B4, 200);
	play(E5, 200);
	play(B4, 200);
	play(E5, 200);
	play(B4, 100);
	play(E5, 200);
	
	play(B4, 100);
	custom_delay_ms(100);
	play(A4P, 100);
	play(B4, 200);
	
	play(B4, 100);
	play(A4P, 100);
	play(B4, 100);
	play(A4, 100);
	custom_delay_ms(100);
	
	play(G4P, 100);
	play(A4, 100);
	play(G4, 100);
	custom_delay_ms(100);
	play(G4P, 100);
	play(A4, 100);
	play(G4, 100);
	
	play(G4, 200);
	play(E4, 400);
	
	play(B4, 200);
	play(E5, 200);
	play(B4, 200);
	play(E5, 200);
	
	play(B4, 100);
	play(E5, 200);
	play(B4, 100);
	custom_delay_ms(100);
	play(A4P, 100);
	play(B4, 200);
}

#endif /* SONG_H_ */