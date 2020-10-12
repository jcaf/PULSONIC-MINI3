/*
 * File:   myeeprom.h
 * Author: jcaf
 *
 * Created on July 20, 2019, 2:09 PM
 */

#ifndef MYEEPROM_H
#define	MYEEPROM_H

    #define EEPROM_BLOCK_ADDR 0x00
    void myeeprom_init(void);

    extern float EEMEM Q_mlh_EEP[NOZZLE_NUMMAX];
    extern uint8_t EEMEM oilViscosityIdx_EEP;

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef	__cplusplus
}
#endif

#endif	/* MYEEPROM_H */

