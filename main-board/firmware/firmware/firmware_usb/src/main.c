
#include "ch.h"
#include "hal.h"

#include "led_ctrl.h"
#include "light_ctrl.h"
#include "moto_ctrl.h"
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

    initLed();
    //initLight();
    //initMoto();


    /*
    pawnInit();
    initUsb();

    pawnRun();
    while ( 1 )
    {
        processShell();
        chThdSleepMilliseconds( 250 );
    }
    */

    while ( 1 )
    {
    	setLed( 1 );
    	//chThdSleepMilliseconds( 500 );
    	setLed( 2 );
    	//chThdSleepMilliseconds( 500 );
    }

    return 0;
}






