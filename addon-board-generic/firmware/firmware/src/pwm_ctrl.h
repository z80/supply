
#ifndef __PWM_CTRL_H_
#define __PWM_CTRL_H_

#include "ch.h"

void initPwm( void );
void setPwmPeriod( int period );
void setPwm( uint32_t mask, int value );


#endif



