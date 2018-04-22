/*
 * play.h
 *
 * Created: 15.04.2018 15:01:18
 *  Author: Madina
 */ 


#ifndef PLAY_H_
#define PLAY_H_

#define	C2	439 //Do		Octave 2
#define	C2P	415 // Do sharp/ Re minor
#define	D2	391	// Re
#define	D2P	369 // Re sharp/ Mi minor
#define	E2	348 // Mi
#define	F2	329 // Fa
#define	F2P	310 // Fa sharp/ Sol minor
#define	G2	293 // Sol
#define	G2P	276 // Sol sharp/ Lya minor
#define	A2	261 // Lya
#define	A2P	246 // Lya sharp/ Si minor
#define	B2	232 // Si
#define	C3	219
#define	C3P	207
#define	D3	195
#define	D3P	184
#define	E3	174
#define	F3	164
#define	F3P	155
#define	G3	146
#define	G3P	138
#define	A3	130
#define	A3P	123
#define	B3	116
#define	C4	109
#define	C4P	103
#define	D4	97
#define	D4P	92
#define	E4	86
#define	F4	81
#define	F4P	77
#define	G4	72
#define	G4P	68
#define	A4	64
#define	A4P	61
#define	B4	57
#define	C5	54
#define	C5P	51
#define	D5	48
#define	D5P	45
#define	E5	43
#define	F5	40
#define	F5P	38
#define	G5	36
#define	G5P	34
#define	A5	32
#define	A5P	30
#define	B5	28

unsigned int notes2[] = {C2, C2P, D2, D2P, E2, F2, F2P, G2, G2P, A2, A2P, B2}; //octave 2 notes
unsigned int notes3[] = {C3, C3P, D3, D3P, E3, F3, F3P, G3, G3P, A3, A3P, B3}; //octave 3 notes
unsigned int notes4[] = {C4, C4P, D4, D4P, E4, F4, F4P, G4, G4P, A4, A4P, B4}; //octave 4 notes
unsigned int notes5[] = {C5, C5P, D5, D5P, E5, F5, F5P, G5, G5P, A5, A5P, B5}; //octave 5 notes
	
#define no_music 0		// No music is played, for free playing mode
#define happy_bday 1	// Music option - Happy Birthday To You
#define for_elise 2		// Music option - For Elise
#define twinkle 3		// Music option - Twinkle Twinkle Little Star
#define star_wars 4		//Music option - Soundtrack from Star Wars

void play_note_timer0(unsigned int note); // setup a frequency on timer0 to play a given note
void play(unsigned int note, unsigned int ms); // play the note with the given duration
void play_happy_birthday();
void play_twinkle();
void play_for_elise();
void play_star_wars();

void custom_delay_ms(unsigned int ms);	

void custom_delay_ms(unsigned int ms)
{
	//1 ms delay for Atmega128A with XTAL=14,745,600Hz (approximated value)
	int i,j,k;
	for (i=0; i<ms; i++)
		for (j=0; j<12; j++)
			for (k=0; k<233; k++)
				asm("NOP");
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

void play_song(int song){
	if(song == happy_bday)
	play_happy_birthday();
	else if(song == for_elise)
	play_for_elise();
	else if(song == twinkle)
	play_twinkle();
	else if(song == star_wars)
	play_star_wars();
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