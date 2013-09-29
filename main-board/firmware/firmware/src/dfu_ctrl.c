
#include "dfu_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"

typedef  void (*pFunction)(void);

int  trigger( void )
{
	palSetPadMode( TRIGGER_PORT, TRIGGER_PAD, PAL_MODE_INPUT );
	// Check if it is pulled down.
	if ( palReadPad( TRIGGER_PORT, TRIGGER_PAD ) )
		// If not pulled down no need to try DFU.
		return 0;
	return 1;
}

void checkDfu( void )
{
	// First of all little delay. Otherwise pad value is measured to be zero.
	// And it causes always DFU mode.
	chThdSleepMilliseconds( 500 );
	// Check if it is pulled down.
	if ( !trigger() )
		// If not pulled down no need to try DFU.
		return;
	// Invoke DFU only if there seems to be a valid firmware.
	// And it is determined using the very first word of firmware at that address.
	if ( ((*(__IO uint32_t*)DFU_ADDRESS) & 0x2FFE0000 ) == 0x20000000 )
	{
	    uint32_t JumpAddress;
	    pFunction Jump_To_Application;
	    
	    JumpAddress = *(__IO uint32_t*) (DFU_ADDRESS + 4);
	    Jump_To_Application = (pFunction) JumpAddress;
	    // Initialize user application's Stack Pointer
	    __set_MSP(*(__IO uint32_t*) DFU_ADDRESS);
	    Jump_To_Application();
	}
}





