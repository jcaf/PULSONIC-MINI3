/*
 * Si
 *
 *  double Qmhl_measured = 5.0;//ml
    double nTicks_measured = 268;//#ticks //esto fue comprobado con el medidor de jeringa
 *
 *  pulsonic.distTotalTime_min = 60;//=60min
    pulsonic.dist_access_time = 1;//c/2min

 * pulsonic.nozzle[0].Q_mlh = 12;//ml

 *  #define PUMP_TICK_TIME_ON   50//in ms
    #define PUMP_TICK_TIME_OFF  75//in ms
 * -> Cada tick es = 50+75 = 125ms
 * -> Max time ticks 12 * 125ms = 1.5 s
 * -> 18 nozzles max * 1.5 = 27 s

 * ->18*200*2ms = 7.2s
 *
 * TOTAL = 34.2s de consumo al maximo
 *
 *
 */
#include "main.h"
#include "pulsonic.h"
#include "mpap.h"
#include "pump.h"
#include "autoMode.h"
#include "visMode.h"
#include "ikb/ikb.h"
#include "flushAllMode.h"

/*Medida oficial en jeringa*/
double Qmhl_measured = 5.0; //ml
double nTicks_measured = 268; //#ticks

//#define AUTOMODE_VER_0
#define AUTOMODE_VER_1

static int8_t numNozzle;

void autoMode_setup(void)
{
    int i;
    double nticksReq_xTotalTimeInMin;

    //pulsonic.ml_x1tick = 5.0/268;
    pulsonic.ml_x1tick = Qmhl_measured / nTicks_measured;

    //expresed in minutes (min)
    pulsonic.distTotalTime_min = 60; //=60min
    pulsonic.distAccessTime_min = 1; //c x min
    pulsonic.timeslice_min = pulsonic.distTotalTime_min / pulsonic.distAccessTime_min;
    //
    pulsonic.distAccessTime_ms = pulsonic.distAccessTime_min*60*1000;

    //
    for (i = 0; i < NOZZLE_NUMMAX; i++)
    {
        if (nozzle_isEnabled(i))
        {
            //pulsonic.nozzle[i].Q_mlh = 12;//ml
            nticksReq_xTotalTimeInMin = pulsonic.nozzle[i].Q_mlh / pulsonic.ml_x1tick;
            pulsonic.nozzle[i].nticks_xtimeslice_min = nticksReq_xTotalTimeInMin / pulsonic.timeslice_min;

            if (pulsonic.nozzle[i].nticks_xtimeslice_min >= 1)
            {
                pulsonic.nozzle[i].kmax_ticks_xtimeslice = (uint16_t) pulsonic.nozzle[i].nticks_xtimeslice_min;
            }

            //added:
            pulsonic.nozzle[i].accError = 0x00;
        }
    }

    pulsonic.num_timeslice = 0x00;

#ifdef AUTOMODE_VER_0
    //added for firmware:
    //pulsonic.kTimeBetweenNozzleAvailable = (uint32_t) ((pulsonic.distAccessTime_min * 60 * 1000) / numNozzleAvailable); //en ms
    pulsonic.kTimeBetweenNozzleAvailable = (uint32_t) ((pulsonic.distAccessTime_ms) / numNozzleAvailable); //en ms
    pulsonic.countNozzleAvailable = 0x00;
#endif
}

static struct _autoMode
{
    int8_t sm0;
} autoMode;

void autoMode_disp7s_writeSumTotal(void)
{
    if (disp_owner == DISPOWNER_AUTOMODE)
    {
        //disp7s_modeDisp_off();
        disp7s_modeDisp_writeInt(20);
        disp7s_qtyDisp_writeFloat(pulsonic_getTotalSum_mlh());
    }
}

void autoMode_cmd(int8_t cmd)
{
    if (cmd == JOB_RESTART)
    {
        //numNozzle = 0x0;
        mpap_homming_job_reset();
        autoMode.sm0 = 0x1;
        //
        autoMode_setup();
    }
    else if (cmd == JOB_STOP)
    {
        autoMode.sm0 = 0x00;
    }
    pump_stop();
    mpap_stall();
}

/* This version is for latest firmware to Bryan Poma */
void autoMode1_job(void)
{
    static uint32_t timeEllapsed;
    //
    double e = 0;

    if (autoMode.sm0 > 0)
    {
        if (autoMode.sm0 == 1)
        {
            if (mpap_isIdle())
            {
                numNozzle = 0x0;

                if (mpap.numSteps_current == 0x000)//origin
                    {autoMode.sm0 = 3;} //direct
                else
                    {autoMode.sm0++;} //mpap->homing
                //
                timeEllapsed = 0x0000;
            }
        }
        else if (autoMode.sm0 == 2)
        {
            if (mpap_homming_job()) //cod_ret = 1 o 2
                autoMode.sm0++;
        }
        else
        {
            if (smain.f.f1ms == 1)
                {timeEllapsed++;}

            //Distribute oil
            if (autoMode.sm0 == 3)
            {
                while ( numNozzle < (NOZZLE_NUMMAX) )//termina con  numNozzle = NOZZLE_NUMMAX
                {
                    if (nozzle_isEnabled(numNozzle))
                        break;
                    else
                        numNozzle++;
                }

                if (numNozzle == NOZZLE_NUMMAX)
                {
                    if (nozzle_getPosition() == (NOZZLE_NUMMAX-1))
                    {
                        #ifdef HOME_POSC_0
                        mpap_doMovement(1 * MPAP_NUMSTEP_1NOZZLE, MPAP_CROSSING_HOMESENSOR_MODE);
                        #else
                        mpap_doMovement(1 * MPAP_NUMSTEP_1NOZZLE, MPAP_NORMAL_MODE);
                        #endif
                        autoMode.sm0 = 7;
                    }
                    else
                    {
                        //mpap_movetoNozzle(numNozzle-1);
                        mpap_movetoNozzle(NOZZLE_NUMMAX-1);
                        autoMode.sm0 = 6;
                    }
                }
                else
                {
                    mpap_movetoNozzle(numNozzle);
                    //numNozzle++;
                    //
                    autoMode.sm0 = 4;
                }
            }
            else if (autoMode.sm0 == 4)
            {
                if (mpap_isIdle())
                {
                    //+-
                    pulsonic.nozzle[numNozzle].nticks_delivered_inThisTimeSlice = 0;
                    pulsonic.nozzle[numNozzle].accError += pulsonic.nozzle[numNozzle].nticks_xtimeslice_min;
                    if (pulsonic.nozzle[numNozzle].accError >= pulsonic.nozzle[numNozzle].kmax_ticks_xtimeslice)
                    {
                        e = pulsonic.nozzle[numNozzle].accError - pulsonic.nozzle[numNozzle].kmax_ticks_xtimeslice;
                        if (e >= 1)
                        {
                            e = e - 1;
                            pulsonic.nozzle[numNozzle].nticks_delivered_inThisTimeSlice += 1;
                        }
                        pulsonic.nozzle[numNozzle].accError = e;
                    }
                    if (pulsonic.num_timeslice == ((int) pulsonic.timeslice_min) - 1)
                    {
                        if (e > 0)
                            pulsonic.nozzle[numNozzle].nticks_delivered_inThisTimeSlice += 1;
                    }
                    pulsonic.nozzle[numNozzle].nticks_delivered_inThisTimeSlice += (uint16_t) pulsonic.nozzle[numNozzle].kmax_ticks_xtimeslice;
                    pulsonic.nozzle[numNozzle].counterTicks_xTotalTime += pulsonic.nozzle[numNozzle].nticks_delivered_inThisTimeSlice;
                    //-+

                    pump_setTick(pulsonic.nozzle[numNozzle].nticks_delivered_inThisTimeSlice);
                    autoMode.sm0++;
                }
            }
            else if (autoMode.sm0 == 5)
            {
                if (pump_isIdle())
                {
                    numNozzle++;
                    autoMode.sm0 = 3; //back to test the next enabled nozzle
                }
            }

            /* this stage is when the nozzle return to home */
            else if (autoMode.sm0 == 6)
            {
               if (mpap_isIdle())
                {
                    #ifdef HOME_POSC_0
                    mpap_doMovement(1 * MPAP_NUMSTEP_1NOZZLE, MPAP_CROSSING_HOMESENSOR_MODE);
                    #else
                    mpap_doMovement(1 * MPAP_NUMSTEP_1NOZZLE, MPAP_NORMAL_MODE);
                    #endif
                    autoMode.sm0++;
               }
            }
            else if (autoMode.sm0 == 7)
            {
                if (mpap_isIdle())
                {
                    if (timeEllapsed >= pulsonic.distAccessTime_ms)
                    {
                        timeEllapsed = 0x00;
                        numNozzle = 0x00; //aqui da por hecho que se completo la vuelta...
                        autoMode.sm0 = 3;
                        //
                        if (++pulsonic.num_timeslice == ((int) pulsonic.timeslice_min))
                        {
                            pulsonic.num_timeslice = 0;
                        }
                    }
                }
            }
        }
    }
}
