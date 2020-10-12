#ifndef MAIN_H_
#define	MAIN_H_

    #include <stdint.h>
    #define F_CPU 16000000UL//48MHz
    #include "system.h"
    #include "types.h"


    //#define HOME_POSC_18
    #define HOME_POSC_0
//    #pragma warning disable 752
//    #pragma warning disable 356
//    #pragma warning disable 373//implicit signed to unsigned conversion
//    #pragma warning disable 520//function is never called

    struct _smain
    {
        struct _main_flag
        {
            unsigned f1ms:1;
            unsigned __a:7;
        }f;

        struct _main_focus
        {
            int8_t kb;
            int8_t disp;
        }focus;
    };
    extern volatile struct _smain smain;

    //#define myitoa(_integer_, _buffer_, _base_) itoa(_buffer_, _integer_, _base_)//PIC LIBRARY NON-STANDAR
    #define myitoa(_integer_, _buffer_, _base_) itoa(_integer_, _buffer_, _base_)//ATMEL C-STANDARD

    enum _FUNMACH
    {
        FUNCMACH_NORMAL = 0,
        FUNCMACH_CONFIG,
        FUNCMACH_ERROR
    };
    extern int8_t funcMach;

    extern int8_t disp_owner;
    enum _DISPOWNER_MODE
    {
        DISPOWNER_AUTOMODE = 0,
        DISPOWNER_VISMODE,
        DISPOWNER_CONFIGMODE,
    };

    enum _JOB_CMD
    {
        JOB_RESTART = 0,
        JOB_STOP
    };

    ////////////////////////////////////////////////////////////////////////////
    //MOTOR PAP UNIPOLAR

    #define PORTWxSTEPPER_A PORTC
    #define PORTRxSTEPPER_A PINC
    #define CONFIGIOxSTEPPER_A DDRC
    #define PINxSTEPPER_A  2
    //
    #define PORTWxSTEPPER_B PORTC
    #define PORTRxSTEPPER_B PINC
    #define CONFIGIOxSTEPPER_B DDRC
    #define PINxSTEPPER_B  0
    //
    #define PORTWxSTEPPER_C PORTC
    #define PORTRxSTEPPER_C PINC
    #define CONFIGIOxSTEPPER_C DDRC
    #define PINxSTEPPER_C  3
    //
    #define PORTWxSTEPPER_D PORTC
    #define PORTRxSTEPPER_D PINC
    #define CONFIGIOxSTEPPER_D DDRC
    #define PINxSTEPPER_D  1


//    #define PORTWxSTEPPER_A LATD
//    #define PORTRxSTEPPER_A PORTD
//    #define CONFIGIOxSTEPPER_A TRISD
//    #define PINxSTEPPER_A  0
//    //
//    #define PORTWxSTEPPER_B LATD
//    #define PORTRxSTEPPER_B PORTD
//    #define CONFIGIOxSTEPPER_B TRISD
//    #define PINxSTEPPER_B  1
//    //
//    #define PORTWxSTEPPER_C LATD
//    #define PORTRxSTEPPER_C PORTD
//    #define CONFIGIOxSTEPPER_C TRISD
//    #define PINxSTEPPER_C  2
//    //
//    #define PORTWxSTEPPER_D LATD
//    #define PORTRxSTEPPER_D PORTD
//    #define CONFIGIOxSTEPPER_D TRISD
//    #define PINxSTEPPER_D  3


    //Enable
    #define PORTWxSTEPPER_ENABLE PORTD
    #define PORTRxSTEPPER_ENABLE PIND
    #define CONFIGIOxSTEPPER_ENABLE DDRD
    #define PINxSTEPPER_ENABLE  5


    //enable is inverted by hardware
    //#define STEPPER_ENABLE() do{PinTo0(PORTWxSTEPPER_ENABLE, PINxSTEPPER_ENABLE);}while(0)
    //#define STEPPER_DISABLE() do{PinTo1(PORTWxSTEPPER_ENABLE, PINxSTEPPER_ENABLE);}while(0)
    #define STEPPER_ENABLE() do{ConfigOutputPin(CONFIGIOxSTEPPER_ENABLE, PINxSTEPPER_ENABLE);}while(0)
    #define STEPPER_DISABLE() do{ConfigInputPin(CONFIGIOxSTEPPER_ENABLE, PINxSTEPPER_ENABLE);}while(0)

    //
    ////////////////////////////////////////////////////////////////////////////
    //OIL-PUMP MOTOR
    #define PORTWxPUMP PORTD
    #define PORTRxPUMP PIND
    #define CONFIGIOxPUMP DDRD
    #define PINxPUMP  6

    //New design is direct from uC
    #define PUMP_DISABLE()  do{PinTo0(PORTWxPUMP, PINxPUMP);}while(0)
    #define PUMP_ENABLE()   do{PinTo1(PORTWxPUMP, PINxPUMP);}while(0)
    //
    //Added 7 marzo 2020
    //pulsonic.disp7s.mode[0] |= 0x80;//DP= 1
    //pulsonic.disp7s.mode[0] &= 0x7F;//DP= 1

    //#define PUMP_DISABLE()  do{PinTo0(PORTWxPUMP, PINxPUMP); pulsonic.disp7s.mode[0] &= 0x7F;}while(0)
    //#define PUMP_ENABLE()   do{PinTo1(PORTWxPUMP, PINxPUMP); pulsonic.disp7s.mode[0] |= 0x80;}while(0)




    ////////////////////////////////////////////////////////////////////////////
    // INPUTS
    #define PORTWxOILLEVEL PORTB
    #define PORTRxOILLEVEL PINB
    #define CONFIGIOxOILLEVEL DDRB
    #define PINxOILLEVEL  7

    #define PORTWxSTEPPER_SENSOR_HOME PORTD
    #define PORTRxSTEPPER_SENSOR_HOME PIND
    #define CONFIGIOxSTEPPER_SENSOR_HOME DDRD
    #define PINxSTEPPER_SENSOR_HOME 7

    #define PORTWxSTARTSIGNAL PORTD
    #define PORTRxSTARTSIGNAL PIND
    #define CONFIGIOxSTARTSIGNAL DDRD
    #define PINxSTARTSIGNAL  4

    #define PORTWxRELAY PORTD
    #define PORTRxRELAY PIND
    #define CONFIGIOxRELAY DDRD
    #define PINxRELAY  3

    //direct from Atmega UC
    #define RELAY_ENABLE()  do{PinTo1(PORTWxRELAY, PINxRELAY);}while(0)
    #define RELAY_DISABLE() do{PinTo0(PORTWxRELAY, PINxRELAY);}while(0)

    ////////////////////////////////////////////////////////////////////////////
    #define KB_LYOUT_KEY_UP      0
    #define KB_LYOUT_KEY_DOWN    1
    #define KB_LYOUT_KEY_PLUS    2
    #define KB_LYOUT_KEY_MINUS   3
    #define KB_LYOUT_KEY_FLUSHENTER 4

    //x Debug //////////////////////////////////////////////////////////////////////////
    #define PORTWxTXD PORTD
    #define PORTRxTXD PIND
    #define CONFIGIOxTXD DDRD
    #define PINxTXD  1

#ifdef	__cplusplus
    extern "C" {
    #endif
    #ifdef	__cplusplus
    }
    #endif

#endif

