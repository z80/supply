
#include "serial_ctrl.h"
#include "moto_ctrl.h"

#include "hal.h"

#include "hdw_cfg.h"

void setSerialEn( uint8_t en, int newBaud )
{
	if ( en )
	{
        palSetPadMode( GPIOB, 10, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
        palSetPadMode( GPIOB, 11, PAL_MODE_INPUT );

        static SerialConfig config =
        {
        	SERIAL_BAUD,
            0,
            0,
            0
        };
        if ( newBaud > 0 )
        	config.sc_speed = (uint32_t)newBaud;

        sdStart( &SERIAL_UART, &config );
	}
	else
	{
		sdStop( &SERIAL_UART );
	}

    /*
    uint32_t i;
    for ( i=0; i<128; i++ )
    {
        //chprintf( (BaseChannel *)&SERIAL_UART, "Hello!\r\n" );
        sdWrite( &SERIAL_UART, (const uint8_t *)"Hello!\r\n", 8 );
        chThdSleepSeconds( 1 );
    }
    */
}

int serialSend( uint8_t * data, int sz )
{
	int cnt = sdWrite( &SERIAL_UART, (const uint8_t *)data, sz );
	return cnt;
}

int  serialReceive( uint8_t * data, int maxSz )
{
    int cnt = sdRead( &SERIAL_UART, data, maxSz );
    return cnt;
}



