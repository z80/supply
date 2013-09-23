
#ifndef __SERIAL_CTRL_H_
#define __SERIAL_CTRL_H_

#include "ch.h"

void setSerialBaud( int newBaud );
void setSerialEn( uint8_t en );
int  serialSend( uint8_t * data, int sz );
int  serialReceive( uint8_t * data, int maxSz );


#endif



