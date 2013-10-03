
#include "pwm_ctrl.h"
#include "hal.h"
#include "hdw_ctrl.h"

void initPwm( void )
{
	palSetPadMode( PORT_PWM_1, PAD_PWM_1, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_2, PAD_PWM_2, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_3, PAD_PWM_3, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_4, PAD_PWM_4, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_5, PAD_PWM_5, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_6, PAD_PWM_6, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_7, PAD_PWM_7, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_8, PAD_PWM_8, PAL_MODE_STM32_ALTERNATE_PUSHPULL );

	pwmStart( &PWMD2, &pwmCfg );
}

void setPwmPeriod( int period )
{

}

void setPwm( uint32_t mask, int value )
{

}


