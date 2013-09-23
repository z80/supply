
#include "serial_ctrl.h"
#include "conv_ctrl.h"
#include "light_ctrl.h"
#include "moto_ctrl.h"

#include "hal.h"

static int baud = SERIAL_BAUD;

void setSerialBaud( int newBaud )
{
    baud = newBaud;
}

void setSerialEn( uint8_t en )
{
	if ( en )
	{
        palSetPadMode( GPIOB, 10, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
        palSetPadMode( GPIOB, 11, PAL_MODE_INPUT );

        static SerialConfig config =
        {
            baud,
            0,
            0,
            0
        };
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

void serialSend( uint8_t * data, int sz )
{
	int cnt = sdWrite( &SERIAL_UART, (const uint8_t *)data, sz );
	return cnt;
}

int  serialReceive( uint8_t * data, int maxSz )
{
    int cnt = sdRead( &SERIAL_UART, data, maxSz );
    return cnt;
}



