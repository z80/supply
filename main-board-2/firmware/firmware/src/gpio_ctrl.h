
#ifndef __GPIO_CTRL_H_
#define __GPIO_CTRL_H_

void gpioInit( void );
int  gpioSetMode( int mask, int mode );
int  gpios( int mask );
int  gpio( int ind );
void gpioSetPeriod( int us );
void gpioSetPwm( int mask, int us );

int gpioPwmActive( void );

#endif





