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
#include "pinGetLevel/pinGetLevel.h"

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
void rsw_setInternalSwitch0(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW6,PINx_RSW6);
	else
		PinTo0(PORTWxRSW6,PINx_RSW6);
}
void rsw_setInternalSwitch1(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW7,PINx_RSW7);
	else
		PinTo0(PORTWxRSW7,PINx_RSW7);
}
void rsw_setInternalSwitch2(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW8,PINx_RSW8);
	else
		PinTo0(PORTWxRSW8,PINx_RSW8);
}
void rsw_setInternalSwitch3(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW9,PINx_RSW9);
	else
		PinTo0(PORTWxRSW9,PINx_RSW9);
}
void rsw_setInternalSwitch4(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW10,PINx_RSW10);
	else
		PinTo0(PORTWxRSW10,PINx_RSW10);
}
void rsw_setInternalSwitch5(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW11,PINx_RSW11);
	else
		PinTo0(PORTWxRSW11,PINx_RSW11);
}
void rsw_setInternalSwitch6(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW0,PINx_RSW0);
	else
		PinTo0(PORTWxRSW0,PINx_RSW0);
}
void rsw_setInternalSwitch7(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW1,PINx_RSW1);
	else
		PinTo0(PORTWxRSW1,PINx_RSW1);
}
void rsw_setInternalSwitch8(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW2,PINx_RSW2);
	else
		PinTo0(PORTWxRSW2,PINx_RSW2);
}
void rsw_setInternalSwitch9(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW3,PINx_RSW3);
	else
		PinTo0(PORTWxRSW3,PINx_RSW3);
}
void rsw_setInternalSwitch10(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW4,PINx_RSW4);
	else
		PinTo0(PORTWxRSW4,PINx_RSW4);
}
void rsw_setInternalSwitch11(uint8_t level)
{
	if (level)
		PinTo1(PORTWxRSW5,PINx_RSW5);
	else
		PinTo0(PORTWxRSW5,PINx_RSW5);
}

/////////////////////////////////////////////////

uint8_t rsw_readSwPositionRSW0(void)
{
	return PinRead(PORTRxRSW13_A1,PINx_RSW13_A1);
}
uint8_t rsw_readSwPositionRSW1(void)
{
	return PinRead(PORTRxRSW13_A2,PINx_RSW13_A2);
}
uint8_t rsw_readSwPositionRSW2(void)
{
	return PinRead(PORTRxRSW13_A3,PINx_RSW13_A3);
}
/////////////////////////////////////////////////
PTRFX_retVOID_arg1_UINT8_T rsw_setInternalSwitchRSWx[RSW_INTERNAL_SWITCHES_NUMAX]=
{	rsw_setInternalSwitch0,
	rsw_setInternalSwitch1,
	rsw_setInternalSwitch2,
	rsw_setInternalSwitch3,
	rsw_setInternalSwitch4,
	rsw_setInternalSwitch5,
	rsw_setInternalSwitch6,
	rsw_setInternalSwitch7,
	rsw_setInternalSwitch8,
	rsw_setInternalSwitch9,
	rsw_setInternalSwitch10,
	rsw_setInternalSwitch11
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
void setPumpPairRSW0(uint8_t level)
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
void setPumpPairRSW1(uint8_t level)
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
void setPumpPairRSW2(uint8_t level)
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
void pumpStartRSW0(uint8_t tick)
{
	rsw[RSW0].pump.ticks = tick;
}
void pumpStartRSW1(uint8_t tick)
{
	rsw[RSW1].pump.ticks = tick;
}
void pumpStartRSW2(uint8_t tick)
{
	rsw[RSW2].pump.ticks = tick;
}

//////////////////////////////////////////////
void pumpStopRSW0(void)
{
	rsw[RSW0].pump.ticks = 0;
	rsw[RSW0].pump.sm0 = 0;
	rsw[RSW0].setPumpPair(0);
	//
	rsw[RSW0].setLED(0);
}
void pumpStopRSW1(void)
{
	rsw[RSW1].pump.ticks = 0;
	rsw[RSW1].pump.sm0 = 0;
	rsw[RSW1].setPumpPair(0);
	//
	rsw[RSW1].setLED(0);
}
void pumpStopRSW2(void)
{
	rsw[RSW2].pump.ticks = 0;
	rsw[RSW2].pump.sm0 = 0;
	rsw[RSW2].setPumpPair(0);
	//
	rsw[RSW2].setLED(0);
}

struct _rsw rsw[RSW_NUM_ROTARYSW_IN_PCB];

void rsw_getSwPositions(struct _rsw *rsw)
{
	for (int8_t sw=0; sw<RSW_INTERNAL_SWITCHES_NUMAX; sw++)//muxing
	{
		if (sw == 0)
		{
			rsw_setInternalSwitchRSWx[RSW_INTERNAL_SWITCHES_NUMAX-1](1);//restore the 11th to 1
		}
		else
		{
			rsw_setInternalSwitchRSWx[sw-1](1);						//restore the previous sw-line to 1
		}
		rsw_setInternalSwitchRSWx[sw](0);								//Put to 0 sw-line
		//
		__delay_us(10);//settle time
		//
		for (int8_t A=0; A<RSW_NUM_ROTARYSW_IN_PCB; A++)
		{
			if (rsw[A].readSwPosition() == 0)
			{
				rsw[A].swposition = sw;					//save position
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
	rsw[RSW0].readSwPosition =rsw_readSwPositionRSW0;
	rsw[RSW1].readSwPosition =rsw_readSwPositionRSW1;
	rsw[RSW2].readSwPosition =rsw_readSwPositionRSW2;
	//
	rsw[RSW0].setLED = setLED1;
	rsw[RSW1].setLED = setLED2;
	rsw[RSW2].setLED = setLED3;

	rsw[RSW0].setPumpPair = setPumpPairRSW0;
	rsw[RSW1].setPumpPair = setPumpPairRSW1;
	rsw[RSW2].setPumpPair = setPumpPairRSW2;

	rsw[RSW0].pumpStart = pumpStartRSW0;
	rsw[RSW1].pumpStart = pumpStartRSW1;
	rsw[RSW2].pumpStart = pumpStartRSW2;

	rsw[RSW0].pumpStop = pumpStopRSW0;
	rsw[RSW1].pumpStop = pumpStopRSW1;
	rsw[RSW2].pumpStop = pumpStopRSW2;

	for (int8_t i=0; i<RSW_INTERNAL_SWITCHES_NUMAX; i++)
	{
		rsw_setInternalSwitchRSWx[i](1);				//all sw-lines to 1
	}
	//
	rsw_getSwPositions(rsw);
	for (int8_t i=0; i<RSW_NUM_ROTARYSW_IN_PCB; i++)
	{
		rsw[i].swposition_old = rsw[i].swposition;
	}
	//
}

/////////////////////////////////////////////////////////
static
int8_t pinGetLevel_swFlush(void)
{
	return PinRead(PORTRxSWFLUSH, PINx_SWFLUSH);
}
static
int8_t pinGetLevel_oilLevel(void)
{
	return PinRead(PORTRxOIL_LEVEL, PINx_OIL_LEVEL);
}
static
int8_t pinGetLevel_start(void)
{
	return PinRead(PORTRxSTART, PINx_START);
}

/////////////////////////////////////////////////////////
#define PINGETLEVEL_NUMMAX 3
PTRFX_retINT8_T pinReadLevel[PINGETLEVEL_NUMMAX]=
{
	pinGetLevel_swFlush,
	pinGetLevel_oilLevel,
	pinGetLevel_start
};
enum _PINGETLEVEL_FX_INDEX
{
	PGLIDX_SWFLUSH,
	PGLIDX_OILLEVEL,
	PGLIDX_START,
};
static
struct _pinGetLevel pinGetLevel[PINGETLEVEL_NUMMAX];
//struct _pinGetLevel pinGetLevel[PINGETLEVEL_NUMMAX] = { {.readPinLevel = pinGetLevel_0},  {.readPinLevel = pinGetLevel_1}};

/////////////////////////////////////////////////////////
void pulsonic_deliverOil_reset(void);
void pulsonic_deliverOil(void);
struct _flush
{
	int8_t sm0;
	int8_t R;

}flush;

void pulsonic_flush_reset(void);
void pulsonic_flush(void);
//
	enum _MACHINE_MODE
	{
		MODE_EMPTY_OIL = -1,
		MODE_IDLE,
		MODE_DELIVER_OIL,
		MODE_FLUSH,
	};

int main(void)
{
	int8_t counter0=0;

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
	ConfigOutputPin(CONFIGIOxPUMP1, PINx_PUMP1);
	ConfigOutputPin(CONFIGIOxPUMP2, PINx_PUMP2);
	ConfigOutputPin(CONFIGIOxPUMP3, PINx_PUMP3);
	ConfigOutputPin(CONFIGIOxPUMP4, PINx_PUMP4);
	ConfigOutputPin(CONFIGIOxPUMP5, PINx_PUMP5);
	ConfigOutputPin(CONFIGIOxPUMP6, PINx_PUMP6);
	//
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
	__delay_ms(10);
	pinGetLevel_init(pinGetLevel, pinReadLevel, PINGETLEVEL_NUMMAX, PGL_START_WITH_CHANGED_FLAG_ON);

	//Config to 10ms
	TCNT0 = 0x00;
	TCCR0 = (1 << WGM01) | (1 << CS02) | (0 << CS01) | (1 << CS00); //CTC, PRES=1024
	OCR0 = CTC_SET_OCR_BYTIME(10e-3, 1024); //TMR8-BIT @16MHz @PRES=1024-> BYTIME maximum = 16ms
	TIMSK |= (1 << OCIE0);
	//
	sei();

	int8_t mode = MODE_IDLE;
	//int8_t mode = MODE_DELIVER_OIL;

	PinTo1(PORTWxRELAY, PINx_RELAY);

	while (1)
	{
		if (isr_flag.sysTickMs)
		{
			isr_flag.sysTickMs = 0;
			mainflag.sysTickMs = 1;
		}
		//----------------------------------
		rsw_getSwPositions(rsw);


		if (mainflag.sysTickMs)
		{
			if (++counter0 >= (20/SYSTICK_MS) )
			{
				counter0 = 0;
				//
				pinGetLevel_job(pinGetLevel, pinReadLevel, PINGETLEVEL_NUMMAX);
				//

				//-------------------------------------------------
				if (pinGetLevel[PGLIDX_OILLEVEL].bf.changed)
				{
					pinGetLevel[PGLIDX_OILLEVEL].bf.changed = 0;

					if (pinGetLevel[PGLIDX_OILLEVEL].bf.level == 0)
					{
						mode = MODE_EMPTY_OIL;

						PinTo0(PORTWxRELAY, PINx_RELAY);

						pulsonic_deliverOil_reset();
						//
						PinTo1(PORTWxLED_OIL, PINx_LED_OIL);
					}
					else
					{
						mode = MODE_IDLE;//REPONE
						//
						PinTo0(PORTWxLED_OIL, PINx_LED_OIL);
						PinTo1(PORTWxRELAY, PINx_RELAY);
						//forzar a revisar los otros switches
						pinGetLevel[PGLIDX_START].bf.changed = 1;	//force
						pinGetLevel[PGLIDX_SWFLUSH].bf.changed = 1;	//force
					}
				}
				//-------------------------------------------------
				if (pinGetLevel[PGLIDX_SWFLUSH].bf.changed)
				{
					pinGetLevel[PGLIDX_SWFLUSH].bf.changed = 0;
					//
					if (mode != MODE_EMPTY_OIL)
					{
						if (pinGetLevel[PGLIDX_SWFLUSH].bf.level == 0)
						{
							pulsonic_flush_reset();
							mode = MODE_FLUSH;
						}
						else
						{
							mode = MODE_IDLE;
							pulsonic_deliverOil_reset();
							pinGetLevel[PGLIDX_START].bf.changed = 1;//force
						}
					}
				}
				//-------------------------------------------------
			if (pinGetLevel[PGLIDX_START].bf.changed)
				{
					pinGetLevel[PGLIDX_START].bf.changed = 0;
					//

					if ( (mode != MODE_FLUSH) && (mode != MODE_EMPTY_OIL))
					{
						if (pinGetLevel[PGLIDX_START].bf.level == 0)
						{
							pulsonic_deliverOil_reset();

							PinTo1(PORTWxRELAY, PINx_RELAY);

							mode = MODE_DELIVER_OIL;
						}
						else
						{
							mode = MODE_IDLE;

							//PinTo0(PORTWxRELAY, PINx_RELAY);	//Bug... no deberia de deshabilitar.. dejar q las otras condiciones lo hagan.. START no limita el RELAY

							pulsonic_deliverOil_reset();
						}
					}
				}
			}
		}
		//
		if (mode == MODE_DELIVER_OIL)
		{
			pulsonic_deliverOil();
		}
		else if (mode == MODE_FLUSH)
		{

			pulsonic_flush();
		}
		//

		pump_job();

		//
		mainflag.sysTickMs = 0;

	}//End while
	return 0;
}


void pulsonic_flush_reset(void)
{
	flush.sm0 = 0;
	flush.R = 0;
}
void pulsonic_flush(void)
{
	if (flush.sm0 == 0)
	{
		//add
		if (rsw[flush.R].swposition != RSW_POS0)
		{
			rsw[flush.R].pumpStart(1);
		}

		flush.sm0 ++;

	}
	else
	{
		if (pump_getTick(flush.R) <= 0)
		{
			flush.sm0 = 0;
			if (++flush.R >= RSW_NUM_ROTARYSW_IN_PCB)
			{
				flush.R = 0;
			}
		}
	}

}

void pulsonic_deliverOil_reset(void)
{
	for (int R=0; R<RSW_NUM_ROTARYSW_IN_PCB; R++)
	{
		rsw[R].sm0 = 0x00;
	}
}
#define NUM_OF_TICKS 2
void pulsonic_deliverOil(void)
{
	///////////////////////////////////////////////////////////////
	for (int R=0; R<RSW_NUM_ROTARYSW_IN_PCB; R++)
	{
		if (rsw[R].swposition_old != rsw[R].swposition)
		{
			rsw[R].swposition_old = rsw[R].swposition;
			//
			rsw[R].sm0 = 0x00;								//ante cualquier cambio, reiniciar el contador
		}
		//
		if (rsw[R].sm0 >= 0)
		{
			if (rsw[R].sm0 == 0)
			{
				rsw[R].counter_sec = 0x00;
				//
				//
				if (rsw[R].swposition ==  RSW_POS0)
				{
					//off all
					rsw[R].pumpStop();
					rsw[R].sm0 = -1;	//inhabilita
				}
				else
				{
					rsw[R].sm0++;

										//arrancar de una vez con ticks
					rsw[R].pumpStart(NUM_OF_TICKS);//1 tick
				}
			}
			else if (rsw[R].sm0 == 1)
			{
				if (mainflag.sysTickMs)
				{
					//counter_sec es ahora de UINT32_T
					if (++rsw[R].counter_sec >= ( (KTIME_SEC[rsw[R].swposition]*1*1000.0)/SYSTICK_MS ) ) // x1 add 1 dec
					{
						rsw[R].counter_sec = 0;
						//
						rsw[R].pumpStart(NUM_OF_TICKS);//1 tick
					}
				}
			}
		}
	}
	////////////////////////////////////////////////////////////////

}

ISR(TIMER0_COMP_vect)
{
	isr_flag.sysTickMs = 1;
}
