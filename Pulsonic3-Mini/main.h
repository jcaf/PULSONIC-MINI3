/*
 * main.h
 *
 *  Created on: Aug 31, 2021
 *      Author: jcaf
 */

#ifndef MAIN_H_
#define MAIN_H_

struct _mainflag
{
	unsigned sysTickMs :1;
	unsigned __a:7;
};
extern struct _mainflag mainflag;

#define SYSTICK_MS 10//10ms

//Rotary Switch
#define RSW_NUM_ROTARYSW_IN_PCB 3
#define RSW_INTERNAL_SWITCHES_NUMAX 12//12 SWITCHS + PIN CENTRAL DE LECTURA


//////////////////////////////
enum _ROTARY_SWITCH_IN_PCB
{
	RSW0=0,
	RSW1,
	RSW2,
};

/*
 * Posiciones = 0..11
 */
enum _RSW_POS
{
	RSW_POS0 = 0,
	RSW_POS1,
	RSW_POS2,
	RSW_POS3,
	RSW_POS4,
	RSW_POS5,
	RSW_POS6,
	RSW_POS7,
	RSW_POS8,
	RSW_POS9,
	RSW_POS10,
	RSW_POS11,
};
#include "types.h"
struct _rsw
{
	PTRFX_retUINT8_T readSwPosition;
	int8_t swposition, swposition_old;
	//
	//uint16_t counter_sec;
	uint32_t counter_sec;
	int8_t sm0;
	PTRFX_retVOID_arg1_UINT8_T setLED;
	PTRFX_retVOID_arg1_UINT8_T setPumpPair;
	PTRFX_retVOID_arg1_UINT8_T pumpStart;
	PTRFX_retVOID pumpStop;

	struct _rsw_pump
	{
		uint16_t ticks;
		int8_t sm0;
		uint16_t counter0;
	}pump;

};
extern struct _rsw rsw[RSW_NUM_ROTARYSW_IN_PCB];
//////////////////////////////
#define PORTWxRSW0 		PORTD
#define PORTRxRSW0 		PIND
#define CONFIGIOxRSW0 	DDRD
#define PINx_RSW0		5
//
#define PORTWxRSW1 		PORTD
#define PORTRxRSW1 		PIND
#define CONFIGIOxRSW1 	DDRD
#define PINx_RSW1		6
//
#define PORTWxRSW2 		PORTD
#define PORTRxRSW2 		PIND
#define CONFIGIOxRSW2 	DDRD
#define PINx_RSW2		7
//
#define PORTWxRSW3 		PORTC
#define PORTRxRSW3 		PINC
#define CONFIGIOxRSW3 	DDRC
#define PINx_RSW3		0
//
#define PORTWxRSW4 		PORTC
#define PORTRxRSW4 		PINC
#define CONFIGIOxRSW4 	DDRC
#define PINx_RSW4		1
//
#define PORTWxRSW5 		PORTC
#define PORTRxRSW5 		PINC
#define CONFIGIOxRSW5 	DDRC
#define PINx_RSW5		2
//
#define PORTWxRSW6 		PORTC
#define PORTRxRSW6 		PINC
#define CONFIGIOxRSW6 	DDRC
#define PINx_RSW6		3
//
#define PORTWxRSW7 		PORTC
#define PORTRxRSW7 		PINC
#define CONFIGIOxRSW7 	DDRC
#define PINx_RSW7		4
//
#define PORTWxRSW8 		PORTC
#define PORTRxRSW8 		PINC
#define CONFIGIOxRSW8 	DDRC
#define PINx_RSW8		5
//
#define PORTWxRSW9 		PORTC
#define PORTRxRSW9 		PINC
#define CONFIGIOxRSW9 	DDRC
#define PINx_RSW9		6
//
#define PORTWxRSW10		PORTC
#define PORTRxRSW10		PINC
#define CONFIGIOxRSW10	DDRC
#define PINx_RSW10		7
//
#define PORTWxRSW11		PORTA
#define PORTRxRSW11		PINA
#define CONFIGIOxRSW11	DDRA
#define PINx_RSW11		7
//
///////////////////////////
#define PORTWxRSW13_A1		PORTA
#define PORTRxRSW13_A1 		PINA
#define CONFIGIOxRSW13_A1 	DDRA
#define PINx_RSW13_A1		4
//
#define PORTWxRSW13_A2 		PORTA
#define PORTRxRSW13_A2 		PINA
#define CONFIGIOxRSW13_A2 	DDRA
#define PINx_RSW13_A2		6
//
#define PORTWxRSW13_A3 		PORTA
#define PORTRxRSW13_A3 		PINA
#define CONFIGIOxRSW13_A3 	DDRA
#define PINx_RSW13_A3		5
//
///////////////////////////
#define PORTWxRELAY		PORTA
#define PORTRxRELAY 	PINA
#define CONFIGIOxRELAY 	DDRA
#define PINx_RELAY		3
//
///////////////////////////
#define PORTWxLED1		PORTD
#define PORTRxLED1 		PIND
#define CONFIGIOxLED1 	DDRD
#define PINx_LED1		2
//
#define PORTWxLED2		PORTD
#define PORTRxLED2 		PIND
#define CONFIGIOxLED2 	DDRD
#define PINx_LED2		3
//
#define PORTWxLED3		PORTD
#define PORTRxLED3 		PIND
#define CONFIGIOxLED3 	DDRD
#define PINx_LED3		4
//
///////////////////////////
#define PORTWxLED_OIL		PORTD
#define PORTRxLED_OIL 		PIND
#define CONFIGIOxLED_OIL 	DDRD
#define PINx_LED_OIL		1
//
///////////////////////////
#define PORTWxSWFLUSH		PORTD
#define PORTRxSWFLUSH 		PIND
#define CONFIGIOxSWFLUSH 	DDRD
#define PINx_SWFLUSH		0
//
///////////////////////////
#define PORTWxOIL_LEVEL		PORTB
#define PORTRxOIL_LEVEL 	PINB
#define CONFIGIOxOIL_LEVEL 	DDRB
#define PINx_OIL_LEVEL		4
//
///////////////////////////
#define PORTWxSTART		PORTB
#define PORTRxSTART 	PINB
#define CONFIGIOxSTART 	DDRB
#define PINx_START		3

//
///////////////////////////
#define PORTWxPUMP1		PORTB
#define PORTRxPUMP1 	PINB
#define CONFIGIOxPUMP1 	DDRB
#define PINx_PUMP1		2
//
#define PORTWxPUMP2		PORTB
#define PORTRxPUMP2 	PINB
#define CONFIGIOxPUMP2 	DDRB
#define PINx_PUMP2		1
//
#define PORTWxPUMP3		PORTB
#define PORTRxPUMP3 	PINB
#define CONFIGIOxPUMP3 	DDRB
#define PINx_PUMP3		0
//
#define PORTWxPUMP4		PORTA
#define PORTRxPUMP4 	PINA
#define CONFIGIOxPUMP4 	DDRA
#define PINx_PUMP4		0
//
#define PORTWxPUMP5		PORTA
#define PORTRxPUMP5 	PINA
#define CONFIGIOxPUMP5 	DDRA
#define PINx_PUMP5		1
//
#define PORTWxPUMP6		PORTA
#define PORTRxPUMP6 	PINA
#define CONFIGIOxPUMP6 	DDRA
#define PINx_PUMP6		2


#endif
