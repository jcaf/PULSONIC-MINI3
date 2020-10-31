#include "main.h"
#include "pulsonic.h"
#include "mpap.h"
#include "pump.h"
#include "autoMode.h"
#include "flushAllMode.h"
#include "ikb/ikb.h"

static int8_t numNozzle;

static struct _flushAllMode
{
    int8_t sm0;
} flushAllMode;

void flushAllMode_cmd(int8_t cmd)
{
    int16_t numSteps_current;

    if (cmd == JOB_RESTART)
    {
        disp7s_modeDisp_off();
        disp7s_qtyDisp_writeText_FLU();
        //
        /*get current position*/
        //numNozzle = nozzle_getPosition();

        //++++++++++++++++++++++++++++------------------
        numSteps_current = mpap_get_numSteps_current() ;

        uint8_t pos = numSteps_current / MPAP_NUMSTEP_1NOZZLE;

        if ( (numSteps_current % MPAP_NUMSTEP_1NOZZLE) == 0)
        {
            //aqui se deberia de analizar directamente si esta habilitado el numero
            numNozzle = pos;
        }
        else
        {
            //ya que esta en progreso de ir a la sgte, entonces tomar la sgte decision
            numNozzle = pos+1;
            if (numNozzle >= NOZZLE_NUMMAX)
            {
                numNozzle = 0x00;
            }
        }
        //++++++++++++++++++++++++++++------------------

        flushAllMode.sm0 = 2;//0x1;
    }
    if (cmd == JOB_STOP)
    {
        flushAllMode.sm0 = 0;
    }

    //parar antes de iniciar
    pump_stop();
    mpap_stall();
}

void flushAllMode_job(void)
{
    if ( (flushAllMode.sm0 > 0) && mpap_isIdle() )//esperar que se haya efectuado la orden de parada
    {
        if (flushAllMode.sm0 == 1)
        {
                if (++numNozzle >= NOZZLE_NUMMAX)
                    numNozzle = 0x00;

                flushAllMode.sm0++;
        }
        else if (flushAllMode.sm0 == 2)
        {
            if (nozzle_setPosition(numNozzle))
            {
                flushAllMode.sm0++;
            }
        }

        else if (flushAllMode.sm0 == 3)
        {
            if (mpap_isIdle())
            {
                if (nozzle_isEnabled(numNozzle))
                {
                    flushAllMode.sm0++;
                }
                else
                {
                    flushAllMode.sm0 -= 2;//-> corre a otro nozzle
                }
            }
        }
        else if (flushAllMode.sm0 == 4)
        {
            if (mpap_isIdle())
            {
                //pump_setTick(6);//buen bombeo segun Bryan
                pump_setTick(1);//buen bombeo segun Bryan
                flushAllMode.sm0++;
            }
        }
        else if (flushAllMode.sm0 == 5)
        {
            if (pump_isIdle())
            {
                flushAllMode.sm0 = 0x1;
            }
        }
    }
}
