
#include "165_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"

static void delay( void )
{
	volatile int i;
	for ( i=0; i<DELAY_165; i++ )
		;
}

void init165( void )
{
    palSetPadMode( PORT_IN_SDA,    PAD_IN_SDA,    PAL_MODE_INPUT );
	palSetPad( PORT_IN_LOAD,   PAD_IN_LOAD );
	palSetPad( PORT_IN_SCL_EN, PAD_IN_SCL_EN );
	palSetPad( PORT_IN_SCL,    PAD_IN_SCL );
    palSetPadMode( PORT_IN_LOAD,   PAD_IN_LOAD,   PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( PORT_IN_SCL_EN, PAD_IN_SCL_EN, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( PORT_IN_SCL,    PAD_IN_SCL,    PAL_MODE_OUTPUT_PUSHPULL );
}


int  read165( void )
{
	palClearPad( PORT_IN_LOAD, PAD_IN_LOAD );
	delay();

	palSetPad( PORT_IN_LOAD, PAD_IN_LOAD );
	delay();

	palClearPad( PORT_IN_SCL_EN, PAD_IN_SCL_EN );
	delay();

	int res = 0;

	int i;
	for ( i=0; i<8; i++ )
	{
		palSetPad( PORT_IN_SCL, PAD_IN_SCL );
		delay();

		int b = palReadPad( PORT_IN_SDA, PAD_IN_SDA ) ? (1<<i) : 0;
		res += b;

		palClearPad( PORT_IN_SCL, PAD_IN_SCL );
		delay();
	}

	palSetPad( PORT_IN_SCL, PAD_IN_SCL );
	delay();

	palSetPad( PORT_IN_SCL_EN, PAD_IN_SCL_EN );
	//delay();
	return res;
}



