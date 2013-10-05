
#include "595_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"

static void delay( void )
{
	volatile int i;
	for ( i=0; i<DELAY_165; i++ )
		;
}


void init595( void )
{
    palSetPad(   PORT_MR,   PAD_MR );
    palClearPad( PORT_SHCP, PAD_SHCP );
    palClearPad( PORT_STCP, PAD_STCP );
    palSetPad(   PORT_DS,   PAD_DS );
    palSetPad(   PORT_OE,   PAD_OE );
    palSetPadMode( PORT_MR,   PAD_MR,   PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( PORT_SHCP, PAD_SHCP, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( PORT_STCP, PAD_STCP, PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( PORT_DS,   PAD_DS,   PAL_MODE_OUTPUT_PUSHPULL );
    palSetPadMode( PORT_OE,   PAD_OE,   PAL_MODE_OUTPUT_PUSHPULL );
}

void set595( uint32_t arg )
{
	int i;
	for ( i=0; i<16; i++ )
	{
		// Set data to serial output.
		int v = ( arg & ( 1 << (15-i) ) );
		if ( v )
			palSetPad( PORT_DS, PAD_DS );
		else
			palClearPad( PORT_DS, PAD_DS );
		delay();

		// Set shift clock.
		palSetPad( PORT_SHCP, PAD_SHCP );
		delay();

		// Clear shift clock.
		palClearPad( PORT_SHCP, PAD_SHCP );
		delay();
	}

	// Set clock at storage register.
	// New data should appear at output (if OE LOW).
	// If not it will appear just after OE negative edge.
	palSetPad( PORT_STCP, PAD_STCP );
	delay();

	// Clear clock at storage register.
	palClearPad( PORT_STCP, PAD_STCP );

	// Output enable (active LOW).
	palClearPad( PORT_OE, PAD_OE );
}

static uint32_t shiftReg = 0;

void setLed( int arg )
{
	shiftReg &= ~(LED_1 | LED_2);
	if ( arg & 1 )
		shiftReg |= LED_1;
	if ( arg & 2 )
		shiftReg |= LED_2;
	set595( shiftReg );
}

void setMoto( int arg )
{
	shiftReg &= ~(MOTO_1 | MOTO_2 | MOTO_3 | MOTO_4 | MOTO_5 | MOTO_6 | MOTO_7 | MOTO_8 | MOTO_EN_1 | MOTO_EN_2);
	if ( arg & 1 )
		shiftReg |= MOTO_1;
	if ( arg & 2 )
		shiftReg |= MOTO_2;
	if ( arg & 4 )
		shiftReg |= MOTO_3;
	if ( arg & 8 )
		shiftReg |= MOTO_4;
	if ( arg & 16 )
		shiftReg |= MOTO_5;
	if ( arg & 32 )
		shiftReg |= MOTO_6;
	if ( arg & 64 )
		shiftReg |= MOTO_7;
	if ( arg & 128 )
		shiftReg |= MOTO_8;
	if ( shiftReg & ( MOTO_1 | MOTO_2 | MOTO_3 | MOTO_4 ) )
		shiftReg |= MOTO_EN_1;
	if ( shiftReg & ( MOTO_5 | MOTO_6 | MOTO_7 | MOTO_8 ) )
		shiftReg |= MOTO_EN_2;
	set595( shiftReg );
}

void setServoEn( int en )
{
	if ( en )
		shiftReg |= SERVO_EN;
	else
		shiftReg &= (~SERVO_EN);
	set595( shiftReg );
}











