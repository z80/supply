
#ifndef __GPIO_CTRL_H_
#define __GPIO_CTRL_H_

void gpioInit( void );
void gpioSetMode( int ind, int mode );
int  gpio( int ind );
void gpioSetPeriod( int us );
void gpioSetPwm( int ind, int us );

#endif





