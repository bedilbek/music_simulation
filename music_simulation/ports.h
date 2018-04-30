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

#define SOUND_PORT PORTF
#define SOUND_DDR DDRF
#define SOUND_BIT 7

#define RECORD_PIN PD0
#define PLAY_RECORD_PIN PD1
#define GAME_START_PIN PD2
#define RECORD_LED_PIN PD3

//#define RECORD_INT_VECTOR INT4_vect
#define PLAY_RECORD_INT_VEC INT1_vect
#define GAME_START_INT_VEC INT2_vect

#define KEYPAD_EXTERNAL_INT_VEC INT4_vect
#define KEYPAD_PIN PE4
#define KEYPAD_PORT PORTE
#define KEYPAD_DDR DDRE

#endif /* PORTS_H_ */