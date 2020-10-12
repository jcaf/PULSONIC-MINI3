/* 
 * File:   eeprom.h
 * Author: jcaf
 *
 * Created on July 18, 2019, 7:26 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

    void eepromWrite(uint8_t addr, uint8_t data);
    uint8_t eepromRead(uint8_t addr);

    void eepromWrite_double(uint8_t *pEaddr, double data);
    double eepromRead_double(uint8_t *pEaddr);

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

