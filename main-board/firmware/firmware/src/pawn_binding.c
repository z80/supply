
#include "pawn_binding.h"

#include "led_ctrl.h"
#include "moto_ctrl.h"
#include "conv_ctrl.h"



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



