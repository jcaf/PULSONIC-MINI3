/*
 * File:   bipolar1.c
 * Author: jcaf
 *
 * Created on September 27, 2019, 2:30 PM
 */

#include <xc.h>
#include <stdint.h>

#define F_CPU 48000000UL	//16000000UL		//AVR-GCC
#define _XTAL_FREQ F_CPU	//C PIC

//#define _XTAL_FREQ 20E6

#pragma config "PLLDIV=5", "CPUDIV=OSC1_PLL2", "USBDIV=2", "FOSC=HSPLL_HS", "FCMEN=OFF", "IESO=OFF", "PWRT=ON", , "BORV=3", "VREGEN=ON", "WDT=OFF", "PBADEN=OFF", "LVP=OFF"
#pragma config "MCLRE=ON","BOR=OFF", 
#pragma config "CP0=ON", "CP1=ON", "CP2=ON", "CP3=ON", "CPD=OFF"

static void _mpap_step1(void)
{
    LATD = 0B00000110;
}
static void _mpap_step2(void)
{
    LATD = 0B00000010;
}
static void _mpap_step3(void)
{
    LATD = 0B00000000;
}
static void _mpap_step4(void)
{
    LATD = 0B00000100;
}
typedef void (*PTRFX_retVOID)(void);
PTRFX_retVOID mpap_step[4] = {_mpap_step1, _mpap_step2, _mpap_step3, _mpap_step4};

void mpap_do1step(int8_t KI)
{
    static int8_t i = -1;

    i = i + KI;
    if (i > 3)
    {
        i = 0;
    }
    if (i < 0)
    {
        i = 3;
    }
    mpap_step[i]();
}
#define TMR8B_OVF(T_DESIRED, PREESCALER) (uint16_t) ((1UL<<8) - (T_DESIRED*F_CPU/(PREESCALER*Q_CYCLE)) )
#define TMR16B_OVF(T_DESIRED, PREESCALER) (uint16_t)((1UL<<16) - ( T_DESIRED *F_CPU / (PREESCALER*Q_CYCLE)) )
#define Q_CYCLE 4   //PIC ARCH.

#define T 1000
void halpstep(void)
{
    int d,i;
    while (1)
    {
        for (i=0; i<200; i++)
        {
            LATD = 0B00001110;//h 8
            __delay_us(T);
            
            LATD = 0B00000010;//f 7
            __delay_us(T);
            
            LATD = 0B00000011;//h 6
            __delay_us(T);
            
            LATD = 0B00000000;//f 5
            __delay_us(T); 

            LATD = 0B00001000;//h 4
            __delay_us(T);
            
            LATD = 0B00000100;//f 3
            __delay_us(T);

            LATD = 0B00000101;//h 2
            __delay_us(T);

            LATD = 0B00000110;//f 1
            __delay_us(T);
            
        }
        LATD = 0B00001111;//f 1
        
        for (d=0; d<200; d++)
            __delay_ms(10);
    }
}

#define TT 1050
void fullstep(void)
{
     int d,i;
    while (1)
    {
        for (i=0; i<200; i++)
        {
            LATD = 0B00000110;
            __delay_us(TT);
            LATD = 0B00000010;
            __delay_us(TT);
            LATD = 0B00000000;
            __delay_us(TT);
            LATD = 0B00000100;
            __delay_us(TT);
        }
        
        //LATD = 0B00001101;
        //
        LATC1 = 0;
        for (d=0; d<200; d++)
            {__delay_ms(10);}
        LATC1 = 1;
        //
    }

}
void main(void)
{
    TRISC1 = 0;
    LATC1 = 1;
    //
    //PORTD = 0B00001001;
    TRISD = 0;
    //
    halpstep();
    //fullstep();
    
    T0CON = 0B10000100; //16BITS
    TMR0H = (uint8_t)(TMR16B_OVF(1e-3, 32) >> 8);
    TMR0L = (uint8_t)(TMR16B_OVF(1e-3, 32));
    TMR0IE = 1;
    
    PEIE = 1;
    GIE = 1;
    while(1);
 

    
    
    return;
}

void interrupt INTERRUPCION(void)
{
    static int8_t cticks;

    //TMMR0:
    //octave:34> (65536) - (1e-3*48e6/(32*4)) 
    //ans =  65161    
    if (TMR0IF)
    {
//        isr_flag.f1ms = 1;
        
        if (++cticks >= 2)
        {
            //mpap_job();
            mpap_do1step(1);
            cticks = 0x00;
        }
        
        TMR0IF = 0;
        TMR0H = (uint8_t)(TMR16B_OVF(1e-3, 32) >> 8);
        TMR0L = (uint8_t)(TMR16B_OVF(1e-3, 32));
    }

}