/*
 * main.c
 *
 *  Created on: Aug 31, 2021
 *      Author: jcaf
 */
#include "system.h"
#include "types.h"

#include "main.h"
#include "pump.h"

volatile struct _isr_flag
{
	unsigned sysTickMs :1;
	unsigned __a :7;
} isr_flag = { 0 };
struct _mainflag mainflag;

/*
 * El footprint del hardware original esta OK, el actual estaba corrido por 1 switch
 * FootprintOK(SW_Rotary12_ORIGINAL)
 * Footprint NO ACORDE (SW_Rotary12)
 */
void rsw_setRSW0(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW6,PINx_RSW6);
	else
		PinTo0(PORTWxRSW6,PINx_RSW6);
}
void rsw_setRSW1(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW7,PINx_RSW7);
	else
		PinTo0(PORTWxRSW7,PINx_RSW7);
}
void rsw_setRSW2(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW8,PINx_RSW8);
	else
		PinTo0(PORTWxRSW8,PINx_RSW8);
}
void rsw_setRSW3(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW9,PINx_RSW9);
	else
		PinTo0(PORTWxRSW9,PINx_RSW9);
}
void rsw_setRSW4(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW10,PINx_RSW10);
	else
		PinTo0(PORTWxRSW10,PINx_RSW10);
}
void rsw_setRSW5(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW11,PINx_RSW11);
	else
		PinTo0(PORTWxRSW11,PINx_RSW11);
}
void rsw_setRSW6(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW0,PINx_RSW0);
	else
		PinTo0(PORTWxRSW0,PINx_RSW0);
}
void rsw_setRSW7(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW1,PINx_RSW1);
	else
		PinTo0(PORTWxRSW1,PINx_RSW1);
}
void rsw_setRSW8(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW2,PINx_RSW2);
	else
		PinTo0(PORTWxRSW2,PINx_RSW2);
}
void rsw_setRSW9(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW3,PINx_RSW3);
	else
		PinTo0(PORTWxRSW3,PINx_RSW3);
}
void rsw_setRSW10(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW4,PINx_RSW4);
	else
		PinTo0(PORTWxRSW4,PINx_RSW4);
}
void rsw_setRSW11(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW5,PINx_RSW5);
	else
		PinTo0(PORTWxRSW5,PINx_RSW5);
}

/////////////////////////////////////////////////

uint8_t rsw_readRSW13_A1(void)
{
	return PinRead(PORTRxRSW13_A1,PINx_RSW13_A1);
}
uint8_t rsw_readRSW13_A2(void)
{
	return PinRead(PORTRxRSW13_A2,PINx_RSW13_A2);
}
uint8_t rsw_readRSW13_A3(void)
{
	return PinRead(PORTRxRSW13_A3,PINx_RSW13_A3);
}
/////////////////////////////////////////////////
PTRFX_retVOID_arg1_UINT8_T rsw_setRSWx[RSW_INTERNAL_SWITCHES_NUMAX]=
{	rsw_setRSW0,
	rsw_setRSW1,
	rsw_setRSW2,
	rsw_setRSW3,
	rsw_setRSW4,
	rsw_setRSW5,
	rsw_setRSW6,
	rsw_setRSW7,
	rsw_setRSW8,
	rsw_setRSW9,
	rsw_setRSW10,
	rsw_setRSW11
};
const int8_t KTIME_SEC[RSW_INTERNAL_SWITCHES_NUMAX]={0,2,4,9,11,15,16,25,33,42,55,72};//sec

void setLED1(uint8_t level)
{
	if (level)
		PinTo1(PORTWxLED1, PINx_LED1);
	else
		PinTo0(PORTWxLED1, PINx_LED1);
}
void setLED2(uint8_t level)
{
	if (level)
		PinTo1(PORTWxLED2, PINx_LED2);
	else
		PinTo0(PORTWxLED2, PINx_LED2);
}
void setLED3(uint8_t level)
{
	if (level)
		PinTo1(PORTWxLED3, PINx_LED3);
	else
		PinTo0(PORTWxLED3, PINx_LED3);
}
void setLED_OIL(uint8_t level)
{
	if (level)
		PinTo1(PORTWxLED_OIL, PINx_LED_OIL);
	else
		PinTo0(PORTWxLED_OIL, PINx_LED_OIL);
}
void setPUMPpairA1(uint8_t level)
{
	if (level)
	{
		PinTo1(PORTWxPUMP1, PINx_PUMP1);
		PinTo1(PORTWxPUMP2, PINx_PUMP2);
	}
	else
	{
		PinTo0(PORTWxPUMP1, PINx_PUMP1);
		PinTo0(PORTWxPUMP2, PINx_PUMP2);
	}

}
void setPUMPpairA2(uint8_t level)
{
	if (level)
	{
		PinTo1(PORTWxPUMP3, PINx_PUMP3);
		PinTo1(PORTWxPUMP4, PINx_PUMP4);
	}
	else
	{
		PinTo0(PORTWxPUMP3, PINx_PUMP3);
		PinTo0(PORTWxPUMP4, PINx_PUMP4);
	}

}
void setPUMPpairA3(uint8_t level)
{
	if (level)
	{
		PinTo1(PORTWxPUMP5, PINx_PUMP5);
		PinTo1(PORTWxPUMP6, PINx_PUMP6);
	}
	else
	{
		PinTo0(PORTWxPUMP5, PINx_PUMP5);
		PinTo0(PORTWxPUMP6, PINx_PUMP6);
	}
}
void pumpStart_A1(uint8_t tick)
{
	rsw[RSW13_A1].pump.ticks = tick;
}
void pumpStart_A2(uint8_t tick)
{
	rsw[RSW13_A2].pump.ticks = tick;
}
void pumpStart_A3(uint8_t tick)
{
	rsw[RSW13_A3].pump.ticks = tick;
}

//////////////////////////////////////////////
void pumpStop_A1(void)
{
	rsw[RSW13_A1].pump.ticks = 0;
	rsw[RSW13_A1].pump.sm0 = 0;
	rsw[RSW13_A1].setPUMPpairAx(0);
	//
	rsw[RSW13_A1].setLEDx(0);
}
void pumpStop_A2(void)
{
	rsw[RSW13_A2].pump.ticks = 0;
	rsw[RSW13_A2].pump.sm0 = 0;
	rsw[RSW13_A2].setPUMPpairAx(0);
	//
	rsw[RSW13_A2].setLEDx(0);
}
void pumpStop_A3(void)
{
	rsw[RSW13_A3].pump.ticks = 0;
	rsw[RSW13_A3].pump.sm0 = 0;
	rsw[RSW13_A3].setPUMPpairAx(0);
	//
	rsw[RSW13_A3].setLEDx(0);
}

struct _rsw rsw[RSW_NUM_ROTARYSW_IN_PCB];

void rsw_getSwPositions(struct _rsw *rsw)
{
	//muxing
	for (int8_t sw=0; sw<RSW_INTERNAL_SWITCHES_NUMAX; sw++)
	{
		if (sw == 0)
		{
			rsw_setRSWx[RSW_INTERNAL_SWITCHES_NUMAX-1](1);//restore the 11th to 1
		}
		else
		{
			rsw_setRSWx[sw-1](1);						//restore the previous sw-line to 1
		}
		rsw_setRSWx[sw](0);								//Put to 0 sw-line
		//
		__delay_us(10);
		//
		for (int8_t A=0; A<RSW_NUM_ROTARYSW_IN_PCB; A++)
		{
			if (rsw[A].readRSW13_Ax() == 0)
			{
				rsw[A].swposition = sw;//save position
			}
		}
		//
	}
}

/*
 * Put all pins to '1'
 */
void rsw_mux_init(void)
{
	rsw[RSW13_A1].readRSW13_Ax =rsw_readRSW13_A1;
	rsw[RSW13_A2].readRSW13_Ax =rsw_readRSW13_A2;
	rsw[RSW13_A3].readRSW13_Ax =rsw_readRSW13_A3;
	//
	rsw[RSW13_A1].setLEDx = setLED1;
	rsw[RSW13_A2].setLEDx = setLED2;
	rsw[RSW13_A3].setLEDx = setLED3;

	rsw[RSW13_A1].setPUMPpairAx = setPUMPpairA1;
	rsw[RSW13_A2].setPUMPpairAx = setPUMPpairA2;
	rsw[RSW13_A3].setPUMPpairAx = setPUMPpairA3;

	rsw[RSW13_A1].pumpStart = pumpStart_A1;
	rsw[RSW13_A2].pumpStart = pumpStart_A2;
	rsw[RSW13_A3].pumpStart = pumpStart_A3;

	rsw[RSW13_A1].pumpStop = pumpStop_A1;
	rsw[RSW13_A2].pumpStop = pumpStop_A2;
	rsw[RSW13_A3].pumpStop = pumpStop_A3;

	for (int8_t i=0; i<RSW_INTERNAL_SWITCHES_NUMAX; i++)
	{
		rsw_setRSWx[i](1);				//all sw-lines to 1
	}
	//
	rsw_getSwPositions(rsw);
	for (int8_t i=0; i<RSW_NUM_ROTARYSW_IN_PCB; i++)
	{
		rsw[i].swposition_old = rsw[i].swposition;
	}
	//
}

int main(void)
{
	//Active pull-up
	PinTo1(PORTWxRSW13_A1, PINx_RSW13_A1);
	PinTo1(PORTWxRSW13_A2, PINx_RSW13_A2);
	PinTo1(PORTWxRSW13_A3, PINx_RSW13_A3);
	ConfigInputPin(CONFIGIOxRSW13_A1,PINx_RSW13_A1);
	ConfigInputPin(CONFIGIOxRSW13_A2,PINx_RSW13_A2);
	ConfigInputPin(CONFIGIOxRSW13_A3,PINx_RSW13_A3);
	//
	ConfigOutputPin(CONFIGIOxRSW0, PINx_RSW0);
	ConfigOutputPin(CONFIGIOxRSW1, PINx_RSW1);
	ConfigOutputPin(CONFIGIOxRSW2, PINx_RSW2);
	ConfigOutputPin(CONFIGIOxRSW3, PINx_RSW3);
	ConfigOutputPin(CONFIGIOxRSW4, PINx_RSW4);
	ConfigOutputPin(CONFIGIOxRSW5, PINx_RSW5);
	ConfigOutputPin(CONFIGIOxRSW6, PINx_RSW6);
	ConfigOutputPin(CONFIGIOxRSW7, PINx_RSW7);
	ConfigOutputPin(CONFIGIOxRSW8, PINx_RSW8);
	ConfigOutputPin(CONFIGIOxRSW9, PINx_RSW9);
	ConfigOutputPin(CONFIGIOxRSW10, PINx_RSW10);
	ConfigOutputPin(CONFIGIOxRSW11, PINx_RSW11);
	//
	rsw_mux_init();
	//
	ConfigOutputPin(CONFIGIOxRELAY, PINx_RELAY);
	//
	ConfigOutputPin(CONFIGIOxLED1, PINx_LED1);
	ConfigOutputPin(CONFIGIOxLED2, PINx_LED2);
	ConfigOutputPin(CONFIGIOxLED3, PINx_LED3);
	//
	ConfigOutputPin(CONFIGIOxLED_OIL, PINx_LED_OIL);
	//
	PinTo1(PORTWxSWFLUSH, PINx_SWFLUSH);//pullup
	ConfigInputPin(CONFIGIOxSWFLUSH, PINx_SWFLUSH);
	//
	PinTo1(PORTWxOIL_LEVEL, PINx_OIL_LEVEL);//pullup
	ConfigInputPin(CONFIGIOxOIL_LEVEL, PINx_OIL_LEVEL);
	//
	PinTo1(PORTWxSTART, PINx_START);//pullup
	ConfigInputPin(CONFIGIOxSTART, PINx_START);
	//
	ConfigOutputPin(CONFIGIOxPUMP1, PINx_PUMP1);
	ConfigOutputPin(CONFIGIOxPUMP2, PINx_PUMP2);
	ConfigOutputPin(CONFIGIOxPUMP3, PINx_PUMP3);
	ConfigOutputPin(CONFIGIOxPUMP4, PINx_PUMP4);
	ConfigOutputPin(CONFIGIOxPUMP5, PINx_PUMP5);
	ConfigOutputPin(CONFIGIOxPUMP6, PINx_PUMP6);
	//

	//Config to 10ms, antes de generar la onda senoidal
	TCNT0 = 0x00;
	TCCR0 = (1 << WGM01) | (1 << CS02) | (0 << CS01) | (1 << CS00); //CTC, PRES=1024
	OCR0 = CTC_SET_OCR_BYTIME(10e-3, 1024); //TMR8-BIT @16MHz @PRES=1024-> BYTIME maximum = 16ms
	TIMSK |= (1 << OCIE0);
	//
	sei();

	while (1)
	{
		if (isr_flag.sysTickMs)
		{
			isr_flag.sysTickMs = 0;
			mainflag.sysTickMs = 1;
		}
		//----------------------------------
		rsw_getSwPositions(rsw);

		for (int A=0; A<RSW_NUM_ROTARYSW_IN_PCB; A++)
		{
			if (rsw[A].swposition_old != rsw[A].swposition)
			{
				rsw[A].swposition_old = rsw[A].swposition;
				//
				rsw[A].sm0 = 0x00;								//ante cualquier cambio, reiniciar el contador
			}
			//
			if (rsw[A].sm0 == 0)
			{
				rsw[A].counter_sec = 0x00;
				//
				//
				if (rsw[A].swposition ==  RSW_POS0)
				{
					//off all
					rsw[A].pumpStop();
				}
				else
				{
					rsw[A].sm0++;
					//arrancar de una vez
					rsw[A].pumpStart(1);//1 tick
				}
			}
			else if (rsw[A].sm0 == 1)
			{
				if (mainflag.sysTickMs)
				{
					if (++rsw[A].counter_sec >= (KTIME_SEC[rsw[A].swposition]*1000.0/SYSTICK_MS) )
					{
						rsw[A].counter_sec = 0;
						//
						rsw[A].pumpStart(1);//1 tick
					}
				}
			}
		}

		pump_job();

		mainflag.sysTickMs = 0;

	}//End while
	return 0;
}

ISR(TIMER0_COMP_vect)
{
	isr_flag.sysTickMs = 1;
}
