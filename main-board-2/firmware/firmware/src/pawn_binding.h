
#ifndef __PAWN_BINDING_H_
#define __PAWN_BINDING_H_

#include "amx.h"

cell pawn_trigger( AMX * amx, const cell * params );

// RTC control.
cell pawn_setRtc( AMX * amx, const cell * params );
cell pawn_rtc( AMX * amx, const cell * params );
cell pawn_msleep( AMX * amx, const cell * params );

// UART control.
cell pawn_setSerialEn( AMX * amx, const cell * params );
cell pawn_serialSend( AMX * amx, const cell * params );
cell pawn_serialReceive( AMX * amx, const cell * params );

// I2C slave control.
cell pawn_setI2cSlaveEn( AMX * amx, const cell * params );

// I2C master control.
cell pawn_setI2cEn( AMX * amx, const cell * params );
cell pawn_i2cIo( AMX * amx, const cell * params );

// I2C wakeup pad control.
cell pawn_setAddTrigger( AMX * amx, const cell * params );
cell pawn_setAddEn( AMX * amx, const cell * params );
cell pawn_setRpiEn( AMX * amx, const cell * params );

// USB control.
cell pawn_usbSetEn( AMX * amx, const cell * params );
cell pawn_usbWrite( AMX * amx, const cell * params );

// LED control.
cell pawn_setLed( AMX * amx, const cell * params );

// Motor control.
cell pawn_setMoto( AMX * amx, const cell * params );

// GPIO control.
cell pawn_gpioSetMode( AMX * amx, const cell * params );
cell pawn_gpios( AMX * amx, const cell * params );
cell pawn_gpio( AMX * amx, const cell * params );
cell pawn_gpioSetPeriod( AMX * amx, const cell * params );
cell pawn_gpioSetPwm( AMX * amx, const cell * params );


#endif





