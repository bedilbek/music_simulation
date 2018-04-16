/*
 * ext_interrupt.c
 *
 * Created: 17.04.2018 0:20:03
 * Author : Madina
 */

////////////////////////
///// INT0-3 for PORTD.0-3
///// INT4-7 for PORTE.4-7
///////////////////////
///////////////////////

#include <avr/io.h>
#include <avr//interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

void toggle(){
	PORTB = 0x00;
	_delay_ms(500);
	PORTB = 0xFF;
}

ISR(INT0_vect){
	toggle();
}

ISR(INT1_vect){
	toggle();
}

ISR(INT2_vect){
	toggle();
}

ISR(INT3_vect){
	toggle();
}

ISR(INT4_vect){
	toggle();
}

ISR(INT5_vect){
	toggle();
}

ISR(INT6_vect){
	toggle();
}

ISR(INT7_vect){
	PORTB = 0x88;
	_delay_ms(500);
	PORTB = 0xFF;
}

int main(void)
{
	DDRB = 0xFF;
	DDRD = 0x00;
	PORTB = 0xFF;
	EIMSK = 0xFF;
	EICRA = 0xFF;
	EICRB = 0xFF;
	EIFR = 0xFF;
	sei();
	while(1);
}

