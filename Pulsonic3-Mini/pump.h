/*
 * pump.h
 *
 *  Created on: Sep 2, 2021
 *      Author: jcaf
 */

#ifndef PUMP_H_
#define PUMP_H_


	#include "main.h"

    #define PUMP_TICK_TIME_ON   (20/SYSTICK_MS) //in ms
    #define PUMP_TICK_TIME_OFF  (120/SYSTICK_MS)//in ms de 60 a 120 21/07/2021

    void pump_job(void);

#endif /* PUMP_H_ */
