/*
 * keypads.h
 *
 * Created: 29.04.2018 15:53:16
 *  Author: Madina
 */ 


#ifndef KEYPAD_NOTES_H_
#define KEYPAD_NOTES_H_

#include "notes.h"

#define ROW_COUNT 7
#define COL_COUNT 8

unsigned int keypad_notes[ROW_COUNT][COL_COUNT] = 
{{C2, C2P, D2, D2P, E2, F2, F2P, G2},
{G2P, A2, A2P, B2, C3, C3P, D3, D3P},
{E3, F3, F3P, G3, G3P, A3, A3P, B3},
{C4, C4P, D4, D4P, E4, F4, F4P, G4},
{G4P, A4, A4P, B4, C5, C5P, D5, D5P},
{E5, F5, F5P, G5, G5P, A5, A5P, B5},
{C6, C6P, D6, D6P, E6, F6, F6P, G6}};





#endif /* KEYPAD_NOTES_H_ */