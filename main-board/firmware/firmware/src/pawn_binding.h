
#ifndef __PAWN_BINDING_H_
#define __PAWN_BINDING_H_

#include "amx.h"

// RTC control.

// LED control.
cell pawn_setLed( AMX * amx, const cell * params );

// Motor control.
cell pawn_setMoto( AMX * amx, const cell * params );

// Converter control.
cell pawn_convSetBuck( AMX * amx, const cell * params );
cell pawn_convSetBoost( AMX * amx, const cell * params );

cell pawn_convSetMinBoostVolt( AMX * amx, const cell * params );
cell pawn_convSetMaxBoostFill( AMX * amx, const cell * params );

cell pawn_convSetBoostCurr( AMX * amx, const cell * params );
cell pawn_convSetBuckCurr( AMX * amx, const cell * params );

cell pawn_convSetBuckGain( AMX * amx, const cell * params );
cell pawn_convSetBoostGain( AMX * amx, const cell * params );

cell pawn_adcTemp( AMX * amx, const cell * params );
cell pawn_adcBatteryVolt( AMX * amx, const cell * params );
cell pawn_adcBuckVolt( AMX * amx, const cell * params );
cell pawn_adcSolarVolt( AMX * amx, const cell * params );
cell pawn_adcBuckCurr( AMX * amx, const cell * params );
cell pawn_adcBoostCurr( AMX * amx, const cell * params );

#endif





