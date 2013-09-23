
#include "pawn_binding.h"
#include "ch.h"
#include "hal.h"

#include "led_ctrl.h"
#include "moto_ctrl.h"
#include "conv_ctrl.h"
#include "serial_ctrl.h"

cell pawn_setRtc( AMX * amx, const cell * params )
{
    RTCTime rtc;
    rtc.tv_sec  = params[1];
    rtc.tv_msec = params[2];
    rtcSetTime( &RTCD1, &rtc );
    return 0;
}

cell pawn_rtc( AMX * amx, const cell * params )
{
    RTCTime rtc;
    rtcGetTime( &RTCD1, &rtc );
    cell * msec;
    msec = amx_Address( amx, params[1] );
    if ( msec )
    	*msec = rtc.tv_msec;
    return rtc.tv_sec;
}

cell pawn_setSerialEn( AMX * amx, const cell * params )
{
    setSerialEn( params[1] );
    return 0;
}

cell pawn_setSerialBaud( AMX * amx, const cell * params )
{
    setSerialBaud( params[1] );
    return 0;
}

cell pawn_serialSend( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_serialReceive( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_setI2cSlaveAddr( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_setI2cSlaveEn( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_setI2CSlaveOut( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_i2cSlaveIn( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_setI2cEn( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_i2cIo( AMX * amx, const cell * params )
{
    return 0;
}

cell pawn_usbWrite( AMX * amx, const cell * params )
{
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

cell pawn_convSetBuck( AMX * amx, const cell * params )
{
    (void)amx;
    convSetBuck( (int)params[1] );
    return 0;
}

cell pawn_convSetBoost( AMX * amx, const cell * params )
{
    (void)amx;
    convSetBoost( (int)params[1] );
    return 0;
}

cell pawn_convSetMinBoostVolt( AMX * amx, const cell * params )
{
    (void)amx;
    convSetMinBoostVolt( (int)params[1] );
    return 0;
}

cell pawn_convSetMaxBoostFill( AMX * amx, const cell * params )
{
    (void)amx;
    convSetMaxBoostFill( (int)params[1] );
    return 0;
}

cell pawn_convSetBoostCurr( AMX * amx, const cell * params )
{
    (void)amx;
    convSetBoostCurr( (int)params[1] );
    return 0;
}

cell pawn_convSetBuckCurr( AMX * amx, const cell * params )
{
    (void)amx;
    convSetBuckCurr( (int)params[1] );
    return 0;
}

cell pawn_convSetBuckGain( AMX * amx, const cell * params )
{
    (void)amx;
    convSetBuckGain( (int)params[1] );
    return 0;
}

cell pawn_convSetBoostGain( AMX * amx, const cell * params )
{
    (void)amx;
    convSetBoostGain( (int)params[1] );
    return 0;
}

cell pawn_adcTemp( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    int t = adcTemp();
    return (cell)t;
}

cell pawn_adcBatteryVolt( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    int v = adcBatteryVolt();
    return (cell)v;
}

cell pawn_adcBuckVolt( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    int v = adcBuckVolt();
    return (cell)v;
}

cell pawn_adcSolarVolt( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    int v = adcSolarVolt();
    return (cell)v;
}

cell pawn_adcBuckCurr( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    int i = adcBuckCurr();
    return (cell)i;
}

cell pawn_adcBoostCurr( AMX * amx, const cell * params )
{
    (void)amx;
    (void)params;
    int i = adcBoostCurr();
    return (cell)i;
}



