
#ifndef __595_CTRL_H_
#define __595_CTRL_H_

#include "ch.h"

void init595( void );
void set595( uint32_t arg );

void setLed( int arg );
void setMoto( int arg );
void setServoEn( int en );



#endif




