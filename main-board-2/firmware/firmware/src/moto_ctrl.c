
#include "moto_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "hdw_cfg.h"




void initMoto( void )
{
}

void setMoto( int en )
{
    // If motor is on the nfirst turn power and outEn on.
    if ( en )
    {
        palSetPad( MOTO_EN_PORT, MOTO_EN_PIN );
        palSetPadMode( MOTO_EN_PORT, MOTO_EN_PIN, PAL_MODE_OUTPUT_PUSHPULL );
    }
    // When motor output is off power to the motor control chip is also off.
    // To prevent powering through MCU pins turn pins on only if power is on.
    uint16_t pwr = palReadPad( MOTO_EN_PORT, MOTO_EN_PIN );
    if ( ( en & 0x01 ) && ( pwr ) )
	    palSetPad( MOTO_1_PORT, MOTO_1_PIN );
	else
	    palClearPad( MOTO_1_PORT, MOTO_1_PIN );
    palSetPadMode( MOTO_1_PORT, MOTO_1_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( ( en & 0x02 ) && ( pwr ) )
	    palSetPad( MOTO_2_PORT, MOTO_2_PIN );
	else
	    palClearPad( MOTO_2_PORT, MOTO_2_PIN );
    palSetPadMode( MOTO_2_PORT, MOTO_2_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( ( en & 0x04 ) && ( pwr ) )
	    palSetPad( MOTO_3_PORT, MOTO_3_PIN );
	else
	    palClearPad( MOTO_3_PORT, MOTO_3_PIN );
    palSetPadMode( MOTO_3_PORT, MOTO_3_PIN, PAL_MODE_OUTPUT_PUSHPULL );

    if ( ( en & 0x08 ) && ( pwr ) )
	    palSetPad( MOTO_4_PORT, MOTO_4_PIN );
	else
	    palClearPad( MOTO_4_PORT, MOTO_4_PIN );
    palSetPadMode( MOTO_4_PORT, MOTO_4_PIN, PAL_MODE_OUTPUT_PUSHPULL );
    
    // If no outs are enabled then turn power off.
    if ( !en )
    {
        palClearPad( MOTO_EN_PORT, MOTO_EN_PIN );
        palSetPadMode( MOTO_EN_PORT, MOTO_EN_PIN, PAL_MODE_OUTPUT_PUSHPULL );
    }
}

int  trigger( void )
{
    palSetPadMode( TRIGGER_PORT, TRIGGER_PAD, PAL_MODE_INPUT );
    // Check if it is pulled down.
    if ( palReadPad( TRIGGER_PORT, TRIGGER_PAD ) )
        // If not pulled down no need to try DFU.
        return 0;
    return 1;
}

void setAddonTrigger( int arg )
{
    if ( arg )
        palSetPad( ADDON_TRIGGER_PORT, ADDON_TRIGGER_PAD );
    else
        palClearPad( ADDON_TRIGGER_PORT, ADDON_TRIGGER_PAD );
    palSetPadMode( ADDON_TRIGGER_PORT, ADDON_TRIGGER_PAD, PAL_MODE_OUTPUT_PUSHPULL );
}

void setAddonEn( int arg )
{
    if ( arg )
        palSetPad( ADDON_PWR_PORT, ADDON_PWR_PAD );
    else
        palClearPad( ADDON_PWR_PORT, ADDON_PWR_PAD );
    palSetPadMode( ADDON_PWR_PORT, ADDON_PWR_PAD, PAL_MODE_OUTPUT_PUSHPULL );    
}

void setRpiEn( int arg )
{
    if ( arg )
        palSetPad( RPI_PWR_PORT, RPI_PWR_PAD );
    else
        palClearPad( RPI_PWR_PORT, RPI_PWR_PAD );
    palSetPadMode( RPI_PWR_PORT, RPI_PWR_PAD, PAL_MODE_OUTPUT_PUSHPULL );
}







