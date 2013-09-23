
#ifndef __PAWN_BINDING_H_
#define __PAWN_BINDING_H_

#include "amx.h"

// RTC control.
cell pawn_setRtc( AMX * amx, const cell * params );
cell pawn_rtc( AMX * amx, const cell * params );

// UART control.
cell pawn_setSerialEn( AMX * amx, const cell * params );
cell pawn_setSerialBaud( AMX * amx, const cell * params );
cell pawn_serialSend( AMX * amx, const cell * params );
cell pawn_serialReceive( AMX * amx, const cell * params );

// I2C slave control.
cell pawn_setI2cSlaveEn( AMX * amx, const cell * params );

// I2C master control.
cell pawn_setI2cEn( AMX * amx, const cell * params );
cell pawn_i2cIo( AMX * amx, const cell * params );

// USB control.
cell pawn_usbWrite( AMX * amx, const cell * params );

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





