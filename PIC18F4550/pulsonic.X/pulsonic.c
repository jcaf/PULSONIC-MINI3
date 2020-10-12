#include "main.h"
#include "pulsonic.h"
#include "myeeprom.h"
#include "PIC/eeprom/eeprom.h"

volatile struct _pulsonic pulsonic;

const int8_t OIL_VISCOSITY[OIL_VISCOSITY_NUMMAX]={22, 32, 46, 68};

void pulsonic_init(void)
{
int8_t eeprom_corr = 0;

    int8_t i;
    //pulsonic.distTotalTime_min = 60;  //min
    pulsonic.distTotalTime_min = 60;  //min
    
    
    for (i=0; i< NOZZLE_NUMMAX; i++)
    {
        pulsonic.nozzle[i].Q_mlh = eepromRead_double(&(((double*)EEPROM_BLOCK_ADDR)[i]));
        
        //if EEPROM Corrupted
        if (pulsonic.nozzle[i].Q_mlh > NOZZLE_QMLH_MAX)
        {
            pulsonic.nozzle[i].Q_mlh = NOZZLE_QMLH_MAX;
            eeprom_corr = 1;
        }
        if (pulsonic.nozzle[i].Q_mlh < NOZZLE_OFF)
        {
            if (i == 0)
            {
                pulsonic.nozzle[i].Q_mlh = NOZZLE_QMLH_MIN;//0.3
            }
            else
            {
                pulsonic.nozzle[i].Q_mlh = NOZZLE_OFF;
            }
            eeprom_corr = 1;
        }
    }
    
    
    //next address is for index-of-OIL_VISCOSITY[]
    pulsonic.oil.i = eepromRead( EEPROM_BLOCK_ADDR + (NOZZLE_NUMMAX*sizeof(double)) );
    
    if ( pulsonic.oil.i > OIL_VISCOSITY_NUMMAX-1)
    {
        pulsonic.oil.i = OIL_VISCOSITY_NUMMAX -1;
        
        eeprom_corr = 1;
    }
    if ( pulsonic.oil.i < 0)
    {
        pulsonic.oil.i = 0;
        
        eeprom_corr = 1;
    }
            
    pulsonic.oil.viscosity = OIL_VISCOSITY[pulsonic.oil.i];
    
    pulsonic.numNozzleAvailable = pulsonic_getNumNozzleAvailable();
    
    
    //+++++++++++++++++++++++++
    /* Update EEPROM*/
    uint8_t reg;    
    if (eeprom_corr == 1)
    {
        for (reg=0; reg<NOZZLE_NUMMAX; reg++)
        {
            eepromWrite_double(&(((double*)EEPROM_BLOCK_ADDR)[reg]), pulsonic.nozzle[reg].Q_mlh);
        }
        //next address is for index-of-OIL_VISCOSITY[]
        eepromWrite(EEPROM_BLOCK_ADDR + (NOZZLE_NUMMAX*sizeof(double)), pulsonic.oil.i);
    }
    //+++++++++++++++++++++++        

}

double pulsonic_getTotalSum_mlh(void)
{
    int i;
    double acc = 0;
    
    for (i=0; i<NOZZLE_NUMMAX; i++)
    {
        acc += pulsonic.nozzle[i].Q_mlh;
    }
    return acc;
}

int8_t pulsonic_getNumNozzleAvailable(void)
{
    int8_t i;
    int8_t numNozzleAvailable=0;
    for (i=0; i<NOZZLE_NUMMAX; i++)
    {
        if (nozzle_isEnabled(i))
            {numNozzleAvailable++;}
    }
    return numNozzleAvailable;
}