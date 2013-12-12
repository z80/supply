
#include "i2c_ctrl.h"
#include "hal.h"

#include "hdw_cfg.h"
#include "pawn_ctrl.h"

static uint8_t outBuffer[ I2C_OUT_BUFFER_SZ ];
static uint8_t inBuffer[ I2C_IN_BUFFER_SZ ];
//static Mutex   mutex;

static InputQueue inputQueue;
#define QUEUE_SZ (I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE)
static uint8_t queue[ I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE ];

static const I2CConfig i2cfg1 =
{
    OPMODE_I2C,
    100000,
    STD_DUTY_CYCLE,
};

static void i2cRxCb( I2CDriver * i2cp );
static void i2cTxCb( I2CDriver * i2cp );

static WORKING_AREA( waExec, 1024 );
static msg_t execThread( void *arg );



void initI2c( void )
{
    // Initialize mailbox.
    chIQInit( &inputQueue, queue, I2C_IN_BUFFER_SZ * EXEC_QUEUE_SIZE, NULL );
    // Creating thread.
    chThdCreateStatic( waExec, sizeof(waExec), NORMALPRIO, execThread, NULL );
}

int setI2cSlaveEn( uint8_t en, uint8_t addr )
{
	if ( en )
	{
		static msg_t status;
		static systime_t tmo;
		tmo = MS2ST( I2C_TIMEOUT );

		palSetPadMode( GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
		palSetPadMode( GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
		while ( 1 )
		{
			i2cStart( &I2CD1, &i2cfg1 );

			addr = ( addr != 0 ) ? addr : I2C_ADDRESS;
			status = i2cSlaveIoTimeout( &I2CD1,    addr,
										inBuffer,  I2C_IN_BUFFER_SZ,
										outBuffer, I2C_OUT_BUFFER_SZ,
										i2cRxCb,
										i2cTxCb,
										tmo );
			if ( status )
			{
				i2cStop( &I2CD1 );
				return status;
			}
			return 0;
		}
	}
	else
	{
	    i2cStop( &I2CD1 );
	    palSetPadMode( GPIOB, 6, PAL_MODE_INPUT );
	    palSetPadMode( GPIOB, 7, PAL_MODE_INPUT );
	    return 0;
	}
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

static msg_t execThread( void *arg )
{
    (void)arg;
    chRegSetThreadName( "e" );
    while ( 1 )
    {
        static size_t sz;
        static uint8_t buffer[ I2C_IN_BUFFER_SZ ];
        sz = chIQReadTimeout( &inputQueue, buffer, I2C_IN_BUFFER_SZ, TIME_INFINITE );

        static uint16_t uvalue16Out;
        static uint8_t  uvalue8Out;

        static uint16_t * puvalue16In;
        static int i;


        puvalue16In = (uint16_t *)(&buffer[1]);
        // Parse inBuffer
        switch ( buffer[0] )
        {
        case I2C_CMD_PAWN_SET_IO:
            pawnSetIo( buffer[1], buffer[2] );
            outBuffer[0] = I2C_CMD_PAWN_SET_IO;
            break;
        case I2C_CMD_PAWN_IO:
        	uvalue16Out = (uint16_t)buffer[1] + ( ((uint16_t)buffer[2]) << 8 );
        	outBuffer[1] = pawnIo( uvalue16Out );
        	outBuffer[0] = I2C_CMD_PAWN_IO;
        	break;
        case I2C_CMD_PAWN_SET_MEM:
        	uvalue16Out = (uint16_t)buffer[1] + ( ((uint16_t)buffer[2]) << 8 );
        	pawnSetMem( uvalue16Out, buffer[3] );
        	outBuffer[0] = I2C_CMD_PAWN_SET_MEM;
        	break;
        case I2C_CMD_PAWN_WRITE_FLASH:
        	puvalue16In = (uint16_t *)(&buffer[1]);
        	uvalue16Out = pawnWriteFlash( puvalue16In[0] );
        	outBuffer[1] = (uint8_t)(uvalue16Out & 0xFF);
        	outBuffer[2] = (uint8_t)(uvalue16Out >> 8);
        	outBuffer[0] = I2C_CMD_PAWN_WRITE_FLASH;
        	break;
        case I2C_CMD_PAWN_RUN:
        	pawnRun();
        	outBuffer[0] = I2C_CMD_PAWN_RUN;
        	break;
        case I2C_CMD_PAWN_IS_RUNNING:
        	uvalue8Out = pawnIsRunning();
        	outBuffer[1] = uvalue8Out;
        	outBuffer[0] = I2C_CMD_PAWN_IS_RUNNING;
        	break;
        case I2C_CMD_PAWN_STOP:
        	pawnStop();
        	outBuffer[0] = I2C_CMD_PAWN_STOP;
        	break;
        case I2C_CMD_PAWN_RESULT:
        	i = pawnResult();
        	outBuffer[1] = (uint8_t)( i & 0xFF );
        	outBuffer[2] = (uint8_t)( (i >> 8) & 0xFF );
        	outBuffer[3] = (uint8_t)( (i >> 16) & 0xFF );
        	outBuffer[4] = (uint8_t)( (i >> 24) & 0xFF );
        	outBuffer[0] = I2C_CMD_PAWN_RESULT;
        case I2C_CMD_PAWN_ERROR:
        	i = pawnError();
        	outBuffer[1] = (uint8_t)( i & 0xFF );
        	outBuffer[2] = (uint8_t)( (i >> 8) & 0xFF );
        	outBuffer[3] = (uint8_t)( (i >> 16) & 0xFF );
        	outBuffer[4] = (uint8_t)( (i >> 24) & 0xFF );
        	outBuffer[0] = I2C_CMD_PAWN_ERROR;
            break;

        }
    }
    return 0;
}




void setI2cEn( uint8_t en )
{
	if ( en )
	{
        palSetPadMode( GPIOB, 10, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );
        palSetPadMode( GPIOB, 11, PAL_MODE_STM32_ALTERNATE_OPENDRAIN );

        i2cStart( &I2CD2, &i2cfg1 );
	}
	else
	{
        i2cStop( &I2CD2 );

        palSetPadMode( GPIOB, 10, PAL_MODE_INPUT );
        palSetPadMode( GPIOB, 11, PAL_MODE_INPUT );
	}
}

int i2cIo( uint8_t addr,
		   uint8_t * outBuffer, int outSz,
		   uint8_t * inBuffer,  int inSz, int timeoutMs )
{
	msg_t status;
	systime_t tmo;
	tmo = MS2ST( timeoutMs );

	if ( outSz > 0 )
	{
        status = i2cMasterTransmitTimeout( &I2CD2,    addr,
                                           outBuffer, outSz,
                                           inBuffer,  inSz,
                                           tmo );
	}
	else
	{
        status = i2cMasterReceiveTimeout( &I2CD2,   addr,
                                          inBuffer, inSz,
                                          tmo );
	}
	return status;
}

void setWakeup( int arg )
{
	if ( arg )
	    palSetPad( PORT_WAKEUP, PAD_WAKEUP );
	else
		palClearPad( PORT_WAKEUP, PAD_WAKEUP );
	palSetPadMode( PORT_WAKEUP, PAD_WAKEUP, PAL_MODE_OUTPUT_PUSHPULL );
}






