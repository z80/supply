
#include "ch.h"
#include "hal.h"

#include "165_ctrl.h"
#include "595_ctrl.h"
#include "pwm_ctrl.h"
#include "pwr_ctrl.h"
#include "adc_ctrl.h"
#include "i2c_ctrl.h"

static void delay( void );


int main(void)
{
    halInit();
    chSysInit();

    //init165();
    init595();
    //initAdc();
    //initPwm();
    //initPwr();
    //initI2c();

    //processI2c();

    while ( 1 )
    {
    	setLed( 1 );
    	chThdSleepMilliseconds( 200 );

    	setLed( 2 );
    	chThdSleepMilliseconds( 200 );
    }
    return 0;
}

static void delay( void )
{
    #define CNT 10000
	volatile int i;
	for ( i=0; i<CNT; i++ )
		;
}








