
#include "pawn_binding.h"
#include "ch.h"
#include "hal.h"

#include "led_ctrl.h"
#include "moto_ctrl.h"
#include "serial_ctrl.h"
#include "i2c_ctrl.h"
#include "usb_ctrl.h"
#include "gpio_ctrl.h"

#include "hdw_cfg.h"

cell pawn_trigger( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    return (cell)trigger();
}

cell pawn_setRtc( AMX * amx, const cell * params )
{
	(void)amx;
    RTCTime rtc;
    rtc.tv_sec  = params[1] / 1000;
    rtc.tv_msec = params[1] - (rtc.tv_sec);
    rtcSetTime( &RTCD1, &rtc );
    return 0;
}

cell pawn_rtc( AMX * amx, const cell * params )
{
	(void)amx;
	(void)params;
    RTCTime rtc;
    rtcGetTime( &RTCD1, &rtc );
    return rtc.tv_sec * 1000 + rtc.tv_msec;
}

cell pawn_msleep( AMX * amx, const cell * params )
{
	(void)amx;
	chThdSleepMilliseconds( (int)( params[1] ) );
	return 0;
}

cell pawn_setSerialEn( AMX * amx, const cell * params )
{
	(void)amx;
    setSerialEn( params[1], params[2] );
    return 0;
}

static uint8_t serialBuffer[SERIAL_BUF_SZ];
cell pawn_serialSend( AMX * amx, const cell * params )
{
	int i = 0;
	int cnt = 0;
	cell * data = amx_Address( amx, params[1] );
	while ( i < params[2] )
	{
		int j;
        for ( j=0; j<SERIAL_BUF_SZ; j++, i++ )
        {
        	if ( i >= params[2] )
        		break;
        	serialBuffer[j] = (uint8_t)data[i];
        }
        cnt += serialSend( serialBuffer, j );
	}
    return cnt;
}

cell pawn_serialReceive( AMX * amx, const cell * params )
{
	int cnt = ( params[2] < SERIAL_BUF_SZ ) ? params[2] : SERIAL_BUF_SZ;
	cnt = serialReceive( serialBuffer, cnt );
	int i;
	cell * data = amx_Address( amx, params[1] );
	if ( !data )
		return 0;
	for ( i=0; i<cnt; i++)
		data[i] = serialBuffer[i];
    return cnt;
}

cell pawn_setI2cSlaveEn( AMX * amx, const cell * params )
{
	(void)amx;
	int status;
	status = setI2cSlaveEn( (uint8_t)params[1], (uint8_t)params[2] );
    return status;
}

cell pawn_setI2cEn( AMX * amx, const cell * params )
{
	(void)amx;
	setI2cEn( (uint8_t)params[1] );
    return 0;
}

static uint8_t i2cWriteBuffer[ I2C_IO_BUFFER_SZ ];
static uint8_t i2cReadBuffer[ I2C_IO_BUFFER_SZ ];
cell pawn_i2cIo( AMX * amx, const cell * params )
{
	(void)amx;
	uint8_t addr = params[1];
	cell * dataIo = amx_Address( amx, params[2] );
	int writeCnt  = params[3];
	int readCnt   = params[5];
	int timeoutMs = params[6];
    int i;
    for ( i=0; i<writeCnt; i++ )
    	i2cWriteBuffer[i] = dataIo[i];
    int status =i2cIo( addr, i2cWriteBuffer, writeCnt,
    		                 i2cReadBuffer,  readCnt,
    		                 timeoutMs );
    if ( readCnt > 0 )
    {
    	dataIo = amx_Address( amx, params[4] );
    	for ( i=0; i<readCnt; i++ )
    		dataIo[i] = (cell)i2cReadBuffer[i];
    }
    return status;
}

cell pawn_setAddTrigger( AMX * amx, const cell * params )
{
	(void)amx;
	setAddonTrigger( params[1] );
	return 0;
}

cell pawn_setAddEn( AMX * amx, const cell * params )
{
    (void)amx;
    setAddonEn( params[1] );
    return 0;
}

cell pawn_setRpiEn( AMX * amx, const cell * params )
{
    (void)amx;
    setRpiEn( params[1] );
    return 0;
}

cell pawn_usbSetEn( AMX * amx, const cell * params )
{
    (void)amx;
    //usbSetEn( params[1] );
    return 0;
}

cell pawn_usbWrite( AMX * amx, const cell * params )
{
	(void)amx;
	int length;
	amx_StrLen( (cell*)params[1], &length );
	#define STR_LEN  32
	static char stri[ STR_LEN ];
	amx_GetString( stri, (cell *)params[1], 0, length );
	stri[ STR_LEN-1 ] = '\0';
	usbWrite( stri );
    return 0;
}

cell pawn_setLed( AMX * amx, const cell * params )
{
    (void)amx;
    setLed( (int)params[1] );
    return 0;
}

cell pawn_setMoto( AMX * amx, const cell * params )
{
    (void)amx;
    setMoto( (int)params[1] );
    return 0;
}

cell pawn_gpioSetMode( AMX * amx, const cell * params )
{
    (void)amx;
    cell res = gpioSetMode( params[1], params[2] );
    return res;
}

cell pawn_gpios( AMX * amx, const cell * params )
{
    (void)amx;
    cell res = gpios( params[1] );
    return res;
}

cell pawn_gpio( AMX * amx, const cell * params )
{
    (void)amx;
    cell res = gpio( params[1] );
    return res;
}

cell pawn_gpioSetPeriod( AMX * amx, const cell * params )
{
    (void)amx;
    gpioSetPeriod( params[1] );
    return 0;
}

cell pawn_gpioSetPwm( AMX * amx, const cell * params )
{
    (void)amx;
    gpioSetPwm( params[1], params[2] );
    return 0;
}







