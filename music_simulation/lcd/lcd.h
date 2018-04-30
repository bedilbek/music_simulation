/*
 * lcd.h
 *
 * Created: 30.04.2018 7:12:37
 *  Author: Student
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "lcdLibrary.h"

int main()
{
	LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PC_4,PC_5,PC_6,PC_7);
	LCD_Init(2,16);
	
	LCD_DisplayString("Navruz");
	LCD_DisplayString("The best");
	while(1);
	
	return (0);
}


#endif /* LCD_H_ */