/*
 * ports.h
 *
 * Created: 29.04.2018 16:41:56
 *  Author: Madina
 */ 


#ifndef PORTS_H_
#define PORTS_H_


#define KEYPADS_ROW_PORT PORTF
#define KEYPADS_COL_DDR DDRA
#define KEYPADS_COL_PIN PINA
#define KEYPADS_ROW_DDR DDRF

#define CONTROL_BTN_PIN PINE
#define CONTROL_BTN_DDR DDRE

#define LCD_BTN_PIN PIND
#define LCD_BTN_DDR DDRD

#define SOUND_PORT PORTB
#define SOUND_DDR DDRB

#define RECORD_PIN PE4
#define PLAY_RECORD_PIN PE5
#define PLAY_SONG PE6
#define RECORD_LED PE7

#define RECORD_INT_VECTOR INT4_vect
#define PLAY_RECORD_VECTOR INT5_vect
#define PLAY_SONG_VECTOR INT6_vect


#endif /* PORTS_H_ */