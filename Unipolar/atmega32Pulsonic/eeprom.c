//#include <xc.h>
#include <stdint.h>
#include "eeprom.h"
//uint8_t eepromRefresh();
uint8_t eepromRead(uint8_t addr)
{
/*    while (EECON1bits.WR)
        {;}

    EEADR = addr;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    while (EECON1bits.RD){;}
    NOP();
    NOP();
    NOP();
    return EEDATA;
    */
return 0;
}
void eepromWrite(uint8_t addr, uint8_t data)//256 bytes...
{
/*    uint8_t GIE_temp;

    while (EECON1bits.WR){;}

    EEADR = addr;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    //Required sequence
    GIE_temp = GIE;
    //
    GIE=0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    while (EECON1bits.WR){;}
    //
    NOP();
    NOP();
    NOP();
    GIE = GIE_temp;
    EECON1bits.WREN = 0;

 */
    //if(EECON1bits.WRERR){
     //   printf("ERROR: writing to EEPROM failed!n")
    //while(PIR2bits.EEIF==0);/* Wait for write operation complete */
    //PIR2bits.EEIF=0;	/* Reset EEIF for further write operation */
}

#define DOUBLE_SIZE sizeof(double)

void eepromWrite_double(uint8_t *pEaddr, double data)
{/*
    int8_t i;
    uint8_t *pfDATA;
    pfDATA = (uint8_t*)&data;
    for (i=0; i<DOUBLE_SIZE; i++)
        {eepromWrite(pEaddr++, *(pfDATA++));}
        */
}

double eepromRead_double(uint8_t *pEaddr)
{
    /*
    int8_t i;
    uint8_t buff[DOUBLE_SIZE];
    for (i = 0; i < DOUBLE_SIZE; i++)
        {buff[i]= eepromRead(pEaddr++);}
    return  *((double*)buff);
    */
}

//double f = 15.6;
//uint8_t *pf;
//double e = 0;
//double *pe;
//uint8_t rambuf[5];
//void test01(void)
//{
//    pf = (uint8_t*)&f;
//
//    eepromWrite(0x00 , *pf);
//    eepromWrite(0x01, *(pf+1));
//    eepromWrite(0x02, *(pf+2));
//
//    rambuf[0]= eepromRead(0);
//    rambuf[1]= eepromRead(1);
//    rambuf[2]= eepromRead(2);
//
//    pe = (double *) rambuf;
//    e = *pe;
//    PORTA = PORTB * e;
//
//}

/*
 *
#define DOUBLE_SIZE sizeof(double)
static double *pfBASE = (double *)EEPROM_BLOCK_ADDR;           //EEPROM addr block
void eepromWrite_double(uint8_t reg, double data)
{
    int8_t i;
    uint8_t *pEaddr;
    uint8_t *pfDATA;
    //
    pEaddr = (uint8_t*)(&pfBASE[reg]);//base
    pfDATA = (uint8_t*)&data;
    //
    for (i=0; i<DOUBLE_SIZE; i++)
        {eepromWrite(pEaddr++, *(pfDATA++));}
}



double eepromRead_double(uint8_t reg)
{
    int8_t i;
    uint8_t *pEaddr;
    uint8_t buff[DOUBLE_SIZE];

    pEaddr = (uint8_t*)(&pfBASE[reg]);

    for (i = 0; i < DOUBLE_SIZE; i++)
        {buff[i]= eepromRead(pEaddr++);}

    return  *((double*)buff);
}
 */


//#include <p18cxxx.h>
//#include <EEP.h>
/********************************************************************
*     Function Name:    Write_b_eep                                 *
*     Return Value:     None										*
*     Parameters:       unsigned int add, unsigned char data        *
*     Description:      Write single byte to Internal EEP           *
********************************************************************/
#if defined (EEP_V1)		//	128 byte EEP
void Write_b_eep( unsigned int badd,unsigned char bdat )
{
	char GIE_BIT_VAL = 0;
	EEADR = (badd & 0x07f);
	EEDATA = bdat;
  	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	GIE_BIT_VAL = INTCONbits.GIE;
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	while(EECON1bits.WR);				//Wait till the write completion
	INTCONbits.GIE = GIE_BIT_VAL;
	EECON1bits.WREN = 0;
}

#elif defined (EEP_V2)	//	256 byte EEP
void Write_b_eep( unsigned int badd,unsigned char bdat )
{
	char GIE_BIT_VAL = 0;
	EEADR = (badd & 0x0ff);
  	EEDATA = bdat;
  	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	GIE_BIT_VAL = INTCONbits.GIE;
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	while(EECON1bits.WR);				//Wait till the write completion
	INTCONbits.GIE = GIE_BIT_VAL;
	EECON1bits.WREN = 0;
}

#elif defined (EEP_V3)				// 1024 byte EEP
void Write_b_eep( unsigned int badd,unsigned char bdat )
{
	char GIE_BIT_VAL = 0;
	EEADRH = (badd >> 8) & 0x03;
	EEADR = (badd & 0x0ff);
	EEDATA = bdat;
  	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1;
	GIE_BIT_VAL = INTCONbits.GIE;
	INTCONbits.GIE = 0;
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	while(EECON1bits.WR);				//Wait till the write completion
	INTCONbits.GIE = GIE_BIT_VAL;
	EECON1bits.WREN = 0;
}
#endif

 #if defined (EEP_V1)		//	128 byte EEP
unsigned char Read_b_eep( unsigned int badd )
{
	EEADR = (badd & 0x07f);
	EECON1bits.CFGS = 0;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;
	Nop();							//Nop may be required for latency at high frequencies
	Nop();							//Nop may be required for latency at high frequencies
	return ( EEDATA );              // return with read byte
}

#elif defined (EEP_V2)	//	256 byte EEP
unsigned char Read_b_eep( unsigned int badd )
{
	EEADR = (badd & 0x0ff);
  	EECON1bits.CFGS = 0;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;
	Nop();							//Nop may be required for latency at high frequencies
	Nop();							//Nop may be required for latency at high frequencies
	return ( EEDATA );              // return with read byte
}

#elif defined (EEP_V3)				// 1024 byte EEP
unsigned char Read_b_eep( unsigned int badd )
{
	EEADRH = (badd >> 8) & 0x03;
	EEADR = (badd & 0x0ff);
  	EECON1bits.CFGS = 0;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;
	Nop();							//Nop may be required for latency at high frequencies
	Nop();							//Nop may be required for latency at high frequencies
	return ( EEDATA );              // return with read byte
}
#endif
/********************************************************************
*     Function Name:    Busy_eep                                    *
*     Return Value:     None										*
*     Parameters:       None										*
*     Description:      Checks & waits the status of ER bit in 		*
						EECON1 register     						*
********************************************************************/
#if defined (EEP_V1) || defined (EEP_V2) || defined (EEP_V3)
void Busy_eep ( void )
{
	while(EECON1bits.WR);
}
#endif
