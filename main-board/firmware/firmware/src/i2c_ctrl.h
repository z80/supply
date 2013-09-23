
#ifndef __I2C_SLAVE_CTRL_H_
#define __I2C_SLAVE_CTRL_H_

#include "ch.h"

void initI2c( void );
int  setI2cSlaveEn( uint8_t en, uint8_t addr );

void setI2cEn( uint8_t en );
int  i2cIo( uint8_t addr,
	        uint8_t * outBuffer, int outSz,
            uint8_t * inBuffer,  int inSz, int timeoutMs );

#endif



