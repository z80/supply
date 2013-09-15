
#include "led_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"



void initLed( void )
{
    palClearPad( LED_PORT, LED1_PIN );
    palClearPad( LED_PORT, LED2_PIN );

    // Configure LED outputs.
    palSetPadMode( LED_PORT, LED1_PIN, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( LED_PORT, LED2_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}

void setLed( int arg )
{
    if ( arg & 1 )
        palSetPad( LED_PORT, LED1_PIN );
    else
        palClearPad( LED_PORT, LED1_PIN );

    if ( arg & 2 )
        palSetPad( LED_PORT, LED2_PIN );
    else
        palClearPad( LED_PORT, LED2_PIN );
}



