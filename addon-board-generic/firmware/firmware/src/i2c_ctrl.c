
#include "i2c_ctrl.h"
#include "hal.h"

#include "hdw_cfg.h"
#include "165_ctrl.h"
#include "595_ctrl.h"
#include "adc_ctrl.h"
#include "pwm_ctrl.h"
#include "pwr_ctrl.h"

static uint8_t outBuffer[ I2C_OUT_BUFFER_SZ ];
static uint8_t inBuffer[ I2C_IN_BUFFER_SZ ];

static InputQueue inputQueue;
#define QUEUE_SZ (I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE)
static uint8_t queue[ I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE ];

static const I2CConfig i2cfg =
{
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

static void i2cRxCb( I2CDriver * i2cp );
static void i2cTxCb( I2CDriver * i2cp );

//static WORKING_AREA( waExec, 1024 );
//static msg_t execThread( void *arg );



void initI2c( void )
{
    // Initialize mailbox.
    chIQInit( &inputQueue, queue, I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE, NULL );

    static msg_t status;
	static systime_t tmo;
	tmo = MS2ST( I2C_TIMEOUT );

	palSetPadMode( PORT_I2C, PAD_SCL, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
	palSetPadMode( PORT_I2C, PAD_SDA, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );

	palSetPadMode( PORT_ADDR, PAD_ADDR_0, PAL_MODE_INPUT );
	palSetPadMode( PORT_ADDR, PAD_ADDR_1, PAL_MODE_INPUT );

	// Here reversly high level corresponds to 0 and low level to digit.
	uint8_t addr = I2C_BASE_ADDR +
			       ( ( palReadPad( PORT_ADDR, PAD_ADDR_0 ) ) ? 0 : 1 ) +
			       ( ( palReadPad( PORT_ADDR, PAD_ADDR_1 ) ) ? 0 : 2 );

	while ( 1 )
	{
		i2cStart( &I2CD1, &i2cfg );

		status = i2cSlaveIoTimeout( &I2CD1,    addr,
									inBuffer,  I2C_IN_BUFFER_SZ,
									outBuffer, I2C_OUT_BUFFER_SZ,
									i2cRxCb,
									i2cTxCb,
									tmo );
		if ( !status )
		    break;;
	}
    // Creating thread.
    //chThdCreateStatic( waExec, sizeof(waExec), NORMALPRIO, execThread, NULL );
}

static void i2cRxCb( I2CDriver * i2cp )
{
    (void)i2cp;
    // Command processing.
    chSysLockFromIsr();
        // Make CPU know command is not processed yet.
        outBuffer[0] = 0;
        // Send command to processing thread.
        static uint32_t i;
        static msg_t res;
        for ( i=0; i<I2C_IN_BUFFER_SZ; i++ )
        {
            res = chIQPutI( &inputQueue, inBuffer[i] );
            if ( res != Q_OK )
                break;
        }
    chSysUnlockFromIsr();
}

static void i2cTxCb( I2CDriver * i2cp )
{
    (void)i2cp;
    // Refresh buffer if necessary.
    //palTogglePad( GPIOB, 11 );
}

//static msg_t execThread( void *arg )
void processI2c( void )
{
    //(void)arg;
    //chRegSetThreadName( "e" );
    while ( 1 )
    {
        static size_t sz;
        static uint8_t buffer[ I2C_IN_BUFFER_SZ ];
        sz = chIQReadTimeout( &inputQueue, buffer, I2C_IN_BUFFER_SZ, TIME_INFINITE );

        static uint16_t uvalue16Out;
        //static uint8_t  uvalue8Out;

        static uint16_t * puvalue16In;
        //static int i;


        puvalue16In = (uint16_t *)(&buffer[1]);
        // Parse inBuffer
        switch ( buffer[0] )
        {
        case I2C_CMD_VERSION:
        	outBuffer[0] = I2C_CMD_VERSION;
        	outBuffer[1] = FIRMWARE_VERSION;
        	break;

        case I2C_CMD_SET_LED:
            setLed( buffer[1] );
            outBuffer[0] = I2C_CMD_SET_LED;
        	break;

        case I2C_CMD_SET_MOTO:
        	setMoto( buffer[1] );
        	outBuffer[0] = I2C_CMD_SET_MOTO;
        	break;

        case I2C_CMD_SET_PWM_PERIOD:
        	setPwmPeriod( buffer[1] +
        			      (buffer[2] << 8) +
        			      (buffer[3] << 16) +
        			      (buffer[4] << 24) );
        	outBuffer[0] = I2C_CMD_SET_PWM_PERIOD;
        	break;

        case I2C_CMD_SET_PWM:
        	setPwm( buffer[1], buffer[2] +
        			           (buffer[3] << 8) +
        			           (buffer[4] << 16) +
        			           (buffer[5] << 24) );
        	outBuffer[0] = I2C_CMD_SET_PWM;
        	break;

        case I2C_CMD_INPUT:
        	outBuffer[1] = (uint8_t)read165();
        	outBuffer[0] = I2C_CMD_INPUT;
        	break;

        case I2C_CMD_ADC:
        	uvalue16Out = measureAdc( buffer[1] );
        	outBuffer[1] = (uint8_t)(uvalue16Out & 0x00FF);
        	outBuffer[2] = (uint8_t)(uvalue16Out >> 8);
        	outBuffer[0] = I2C_CMD_ADC;
        	break;

        case I2C_CMD_SLEEP:
        	sleep();
            break;
        }
    }
    // return 0;
}











