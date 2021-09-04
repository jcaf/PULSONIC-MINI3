/*
 * pump.c
 *
 *  Created on: Sep 2, 2021
 *      Author: jcaf
 */

#include "system.h"
#include "types.h"

#include "main.h"
#include "pump.h"


void pump_job(void)
{
	for (int A=0; A<RSW_NUM_ROTARYSW_IN_PCB; A++)
	{
		if (rsw[A].pump.ticks > 0)
		{
			if (rsw[A].pump.sm0 == 0)
			{
				//PUMP_ENABLE();
				rsw[A].setPumpPair(1);
				rsw[A].setLED(1);
				//
				rsw[A].pump.counter0 = 0x00;
				rsw[A].pump.sm0++;
			}
			else if (rsw[A].pump.sm0 == 1)
			{
				if (mainflag.sysTickMs)
				{
					if (++rsw[A].pump.counter0 == PUMP_TICK_TIME_ON)
					{
						rsw[A].pump.counter0 = 0x00;
						rsw[A].pump.sm0++;

						//PUMP_DISABLE();
						rsw[A].setPumpPair(0);
						rsw[A].setLED(0);
					}
				}
			}
			else if (rsw[A].pump.sm0 == 2)
			{
				if (mainflag.sysTickMs)
				{
					if (++rsw[A].pump.counter0 == PUMP_TICK_TIME_OFF)
					{
						rsw[A].pump.counter0 = 0x00;
						rsw[A].pump.sm0 = 0x00;
						//
						if (--rsw[A].pump.ticks <= 0)
						{
							//cod_ret = 1;
						}
					}
				}
			}
		}
	}

}
