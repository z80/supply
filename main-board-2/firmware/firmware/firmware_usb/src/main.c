
#include "ch.h"
#include "hal.h"

#include "hdw_cfg.h"
#include "dfu_ctrl.h"
#include "led_ctrl.h"
#include "light_ctrl.h"
#include "moto_ctrl.h"
#include "conv_ctrl.h"
#include "i2c_ctrl.h"
#include "usb_ctrl.h"
#include "pawn_ctrl.h"
#include "misc.h"

//*
//* Application entry point.
//*
int main(void)
{
    //NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x2800 );

    halInit();
    chSysInit();

    checkDfu();

    initLed();
    initLight();
    initMoto();
    initI2c();
    initConv();

    pawnInit();
    initUsb();

    // Call it here once to be able to communicate.
    // Informative countdown before running machine.
    int i;
    for ( i=0; i<PAWN_START_DELAY; i+=PAWN_START_STEP )
    {
        setLed( 3 );
        processShell();
        chThdSleepMilliseconds( PAWN_START_STEP/2 );

        setLed( 0 );
        chThdSleepMilliseconds( PAWN_START_STEP/2 );
    }

    if ( !pawnDontRun() )
        pawnRun();
    while ( 1 )
    {
        processShell();
        chThdSleepMilliseconds( 250 );
    }

    /*
    while ( 1 )
    {
    	setLed( 1 );
    	setLight( 1 );
    	chThdSleepMilliseconds( 500 );

    	setLed( 2 );
    	setLight( 0 );
    	chThdSleepMilliseconds( 500 );
    }
    */
    return 0;
}






