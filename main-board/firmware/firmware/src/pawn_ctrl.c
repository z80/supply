
#include "pawn_ctrl.h"
#include "amx.h"
#include "pawn_config.h"
#include "pawn_binding.h"

#include "stm32f10x_flash.h"

//#include "i2c_ctrl.h"

typedef struct
{
    AMX amx;
    uint8_t isRunning;
    uint8_t dontRun;
    int result, error;
    uint32_t    memblock[ PAWN_MEM_SIZE ];
    uint8_t     ioblock[ PAWN_IO_SIZE ];
} Pawn;

Pawn g_pawn;

static cell pawn_io( AMX * amx, const cell * params );
static cell pawn_setIo( AMX * amx, const cell * params );

AMX_NATIVE const g_nativetable[] =
{
	pawn_trigger,

    pawn_setRtc,
    pawn_rtc,
    pawn_msleep,

    pawn_setSerialEn,
    pawn_serialSend,
    pawn_serialReceive,

    pawn_setI2cSlaveEn,

    pawn_setI2cEn,
    pawn_i2cIo,

    pawn_setWakeup,

    pawn_usbWrite,

    pawn_io,
    pawn_setIo, 

    pawn_setLed, 
    pawn_setMoto, 
    pawn_convSetBuck, 
    pawn_convSetBoost, 
    pawn_convSetMinBoostVolt, 
    pawn_convSetMaxBoostFill, 
    pawn_convSetBoostCurr, 
    pawn_convSetBuckCurr, 
    pawn_convSetBuckGain, 
    pawn_convSetBoostGain, 
    pawn_adcTemp, 
    pawn_adcBatteryVolt, 
    pawn_adcBuckVolt, 
    pawn_adcSolarVolt, 
    pawn_adcBuckCurr, 
    pawn_adcBoostCurr
};


int AMXAPI aux_Monitor( AMX * amx )
{
    (void)amx;
    return AMX_ERR_EXIT;
}

static void pawnExec( Pawn * pawn )
{
    chSysLock();
        pawn->isRunning = 0;
    chSysUnlock();
    uint32_t i;
    unsigned char * tmp = (unsigned char *)&pawn->amx;
    for ( i=0; i<sizeof( pawn->amx ); i++ )
        tmp[i] = 0;
    pawn->amx.data = (uint8_t *)pawn->memblock;
    uint8_t * rom = (uint8_t *)(PAWN_FLASH_START + PAWN_PAGE_SIZE * PAWN_START_PAGE);
    pawn->result = amx_Init( &pawn->amx, rom );
    if ( pawn->result != AMX_ERR_NONE )
        return;

    static cell ret = 0;
    chSysLock();
        pawn->isRunning = 1;
    chSysUnlock();

    pawn->error = amx_Exec( &pawn->amx, &ret, AMX_EXEC_MAIN );
    pawn->result = ret;
    amx_Cleanup( &pawn->amx );

    chSysLock();
        pawn->isRunning = 0;
    chSysUnlock();
}




static cell pawn_io( AMX * amx, const cell * params )
{
    (void)amx;
    uint32_t index;
    index = (uint32_t)params[1];
    return (cell)( g_pawn.ioblock[ index ] );
}

static cell pawn_setIo( AMX * amx, const cell * params )
{
    (void)amx;
    uint32_t index;
    index = (uint8_t)params[1];
    g_pawn.ioblock[ index ] = params[2];
    return 0;
}



























static WORKING_AREA( waExec, PAWN_THREAD_STACK_DEPTH );
static msg_t execThread( void *arg );
static BinarySemaphore semaphore;

void pawnInit( void )
{
	g_pawn.dontRun = 0;
    // Initialize mailbox.
    chBSemInit( &semaphore, TRUE );
    // Creating thread.
    chThdCreateStatic( waExec, sizeof(waExec), NORMALPRIO, execThread, NULL );
}

void pawnSetIo( int ind, uint8_t value )
{
    g_pawn.ioblock[ ind ] = value;
}

uint8_t pawnIo( int ind )
{
    return g_pawn.ioblock[ ind ];
}

void pawnSetMem( int at, uint8_t value )
{
	uint8_t * mem = (uint8_t *)(g_pawn.memblock);
	mem[ at ] = value;
}
/*
void pawnSetMem( int at, int cnt )
{
    int i;
    uint8_t * mem = (uint8_t *)(g_pawn.memblock);
    for ( i=0; i<cnt; i++ )
        mem[at+i] = g_pawn.ioblock[i];
}
*/

uint8_t pawnMem( int at )
{
    uint8_t * mem = (uint8_t *)(g_pawn.memblock);
    return mem[ at ]; 
}

uint16_t pawnWriteFlash( uint8_t page )
{
	if ( page >= PAWN_PAGES_CNT )
		return 30;
    FLASH_Unlock();
    uint32_t flashD = PAWN_FLASH_START + PAWN_PAGE_SIZE * ( page + PAWN_START_PAGE );
    FLASH_Status st = FLASH_ErasePage( flashD );
    if ( st != FLASH_COMPLETE )
    {
        FLASH_Lock();
        return 50+st;
    }
    uint32_t * memD   = (uint32_t *)( g_pawn.memblock );
    uint32_t   i;
    for ( i=0; i<PAWN_MEM_SIZE; i++ )
    {
        // WORD size is 4 bytes
        st = FLASH_ProgramWord( flashD+i*4, memD[i] );
        if ( st != FLASH_COMPLETE )
        {
	        FLASH_Lock();
	        return 100+st;
	    }
    }
    // to be done.
    FLASH_Lock();
    return 0;
}

void pawnRun( void )
{
    chBSemSignal( &semaphore );
}

uint8_t pawnIsRunning( void )
{
    chSysLock();
        uint8_t res = g_pawn.isRunning;
    chSysUnlock();
    return res;
}

void pawnStop( void )
{
    chSysLock();
        amx_SetDebugHook( &(g_pawn.amx), aux_Monitor );
    chSysUnlock();
    g_pawn.dontRun = 1;
}

int pawnResult( void )
{
    return g_pawn.result;
}

int pawnError( void )
{
    return g_pawn.error;
}

uint8_t  pawnDontRun( void )
{
	return g_pawn.dontRun;
}



static msg_t execThread( void *arg )
{
    (void)arg;
    chRegSetThreadName( "e" );
    while ( 1 )
    {
        chBSemWait( &semaphore );

        // If's come here run Pawn machine.
        pawnExec( &g_pawn );
    }
    return 0;
}




