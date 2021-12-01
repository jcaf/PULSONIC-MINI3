/*
 * pump.h
 *
 *  Created on: Sep 2, 2021
 *      Author: jcaf
 */

#ifndef PUMP_H_
#define PUMP_H_


	#include "main.h"

    #define PUMP_TICK_TIME_ON   (40/SYSTICK_MS) //in ms
    #define PUMP_TICK_TIME_OFF  (90/SYSTICK_MS)//in ms de 60 a 120 21/07/2021

    void pump_job(void);
    int8_t pump_getTick(int8_t A);

#endif /* PUMP_H_ */
