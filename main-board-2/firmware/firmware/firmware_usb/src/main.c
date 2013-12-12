
#include "ch.h"
#include "hal.h"

#include "hdw_cfg.h"
#include "led_ctrl.h"
#include "moto_ctrl.h"
#include "i2c_ctrl.h"
#include "usb_ctrl.h"
#include "pawn_ctrl.h"
#include "misc.h"

//*
//* Application entry point.
//*
int main(void)
{
    halInit();
    chSysInit();

    initLed();
    initMoto();
    initI2c();

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






