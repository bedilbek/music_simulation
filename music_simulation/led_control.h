/*
 * led_control.h
 *
 * Created: 30.04.2018 5:13:40
 *  Author: dfdf
 */ 


#ifndef LED_CONTROL_H_
#define LED_CONTROL_H_

#include "play.h"

#define HC595_PORT   PORTB
#define HC595_DDR    DDRB

#define HC595_DS0_POS PB0
#define HC595_DS1_POS PB1
#define HC595_DS2_POS PB2
#define HC595_DS3_POS PB3

#define HC595_SH_CP_POS PB5
#define HC595_ST_CP_POS PB6

void HC595Init(){
	HC595_DDR|=((1<<HC595_SH_CP_POS)|(1<<HC595_ST_CP_POS)|(1<<HC595_DS0_POS)|(1<<HC595_DS1_POS)|(1<<HC595_DS2_POS)|(1<<HC595_DS3_POS));
}



#define HC595Data0High() (HC595_PORT|=(1<<HC595_DS0_POS))
#define HC595Data0Low() (HC595_PORT&=(~(1<<HC595_DS0_POS)))

#define HC595Data1High() (HC595_PORT|=(1<<HC595_DS1_POS))
#define HC595Data1Low() (HC595_PORT&=(~(1<<HC595_DS1_POS)))

#define HC595Data2High() (HC595_PORT|=(1<<HC595_DS2_POS))
#define HC595Data2Low() (HC595_PORT&=(~(1<<HC595_DS2_POS)))

#define HC595Data3High() (HC595_PORT|=(1<<HC595_DS3_POS))
#define HC595Data3Low() (HC595_PORT&=(~(1<<HC595_DS3_POS)))

void HC595Pulse()
{

	HC595_PORT|=(1<<HC595_SH_CP_POS);

	HC595_PORT&=(~(1<<HC595_SH_CP_POS));

}


void HC595Latch()
{
	

	HC595_PORT|=(1<<HC595_ST_CP_POS);
	_delay_loop_1(1);
	

	HC595_PORT&=(~(1<<HC595_ST_CP_POS));
	_delay_loop_1(1);
}

void HC595Write(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
	
	for(uint8_t i=0;i<8;i++)
	{
		
		if(data0 & 0b10000000)
		{
			HC595Data0High();
		}
		else
		{
			
			HC595Data0Low();
		}
		if(data1 & 0b10000000)
		{
			HC595Data1High();
		}
		else
		{
			
			HC595Data1Low();
		}
		if(data2 & 0b00000001)
		{
			HC595Data2Low();
		}
		else
		{
			
			HC595Data2High();
		}
		if(data3 & 0b00000001)
		{
			HC595Data3Low();
		}
		else
		{
			
			HC595Data3High();
		}
		

		HC595Pulse();
		data0=data0<<1;
		data1=data1<<1;
		data2=data2>>1;
		data3=data3>>1;

	}

	
	HC595Latch();
}


void Wait()
{
	for(uint8_t i=0;i<30;i++)
	{
		_delay_loop_2(0);
	}
}



unsigned int light_notes[13]={
	0x8000,  //C
	0x4000,  //Db
	0x2000,  //D
	0x1000,  //Eb
	0x0800,  //E
	0x0400,  //F
	0x0200,  //Gb
	0x0100,  //G
	0x0080,  //Ab
	0x0040,  //A
	0x0020,  //Bb
	0x0010,   //B
	0x0000
};

unsigned int light_octs[15]={
	0x8000,  //1oct
	0x4000,  //1oct
	0x2000,  //1oct
	0x1000,  //2oct
	0x0800,  //2oct
	0x0400,  //2oct
	0x0200,  //3oct
	0x0100,  //3oct
	0x0080,  //3oct
	0x0040,  //4oct
	0x0020,  //4oct
	0x0010,  //4oct
	0x0008,  //5oct
	0x0004,  //5oct
	0x0002   //5oct
};

unsigned int happy_birthday_notes[51][3]={
	{2,12,12},
	{2, 2,12},
	{4, 2, 2},
	{4, 4, 2},
	{2, 4, 4},
	{2, 2, 4},
	{7, 2, 2},
	{7, 7, 2},
	{6, 7, 7},
	{6, 6, 7},
	{6, 6, 6},
	{6, 6, 6},
	{2, 6, 6},
	{2, 2, 6},
	{4, 2, 2},
	{4, 4, 2},
	{2, 4, 4},
	{2, 2, 4},
	{9 ,2, 2},
	{9 ,9, 2},
	{7, 9, 9},
	{7, 7, 9},
	{7, 7, 7},
	{7, 7, 7},
	{2, 7, 7},
	{2, 2, 7},
	{2, 2, 2},   //d4
	{2, 2, 2},
	{11,2, 2},   //d4
	{11,11,2},   //d4
	{7,11,11},
	{7, 7,11},
	{6, 7, 7},
	{6, 6, 7},
	{4, 6, 6},
	{4, 4, 6},
	{0, 4, 4},
	{0, 0, 4},
	{11,0, 0},
	{11,11,0},
	{7,11,11},
	{7, 7,11},
	{9, 7, 7},
	{9, 9, 7},
	{7, 9, 9},
	{7, 7, 9},
	{7, 7, 7},
	{7, 7, 7},
	{12,7, 7},
	{12,12,7},
	{12,12,12}
};

unsigned int happy_birthday_octs[51][3]={
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{9,7,8},
	{9,10,8},
	{6,10,11},
	{6,7,11},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{9,7,8},
	{9,10,8},
	{6,10,11},
	{6,7,11},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8},
	{6,7,8}
};

void led_happy_birthday(){
	for(uint8_t i=0;i<51;i++){
		int loop1, loop2, loop3;
		unsigned int ms = 5;
		for (loop1 = 0; loop1 < ms; loop1++)
		for (loop2 = 0; loop2 < 12; loop2++)
		for (loop3 = 0; loop3 < 233; loop3++)
		for (uint8_t j = 0; j < 3; j++){
			HC595Write(	light_notes[happy_birthday_notes[i][j]] >> 8,
			light_notes[happy_birthday_notes[i][j]] & 0xff,
			light_octs[happy_birthday_octs[i][j]] >> 8,
			light_octs[happy_birthday_octs[i][j]] & 0xFF );
		}
	}
}

#endif /* LED_CONTROL_H_ */