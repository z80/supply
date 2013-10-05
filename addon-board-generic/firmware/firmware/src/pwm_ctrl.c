
#include "pwm_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"

// PWM_8 -> TIM2_CH1
// PWM_1 -> TIM2_CH2

// PWM_2 -> TIM3_CH1
// PWM_3 -> TIM3_CH2
// PWM_7 -> TIM3_CH3
// PWM_6 -> TIM3_CH4

// PWM_4 -> TIM4_CH3
// PWM_5 -> TIM4_CH4




void initPwm( void )
{
	// Better to just not use SWD_1 and SWD_2 :) Because getting SWD_1 and SWD_2 causes loose of SWD_8 and
	// Release unused JTAG pins.
	//AFIO->MAPR = (AFIO->MAPR & ~((1<<26) | (1<<25) | (1<<24))) | (1<<25);
	// Remapping TIM2 bit getting PWM1 causes loose of PWM8.
	// Anyway have to resolder either PWM1 or remap and resolder PWM8.
	// It looks like the last option is preferrable.
	//AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_TIM2_REMAP ) | AFIO_MAPR_TIM2_REMAP_0; // Activated PB3 but deactivated
	// Remapping TIM3 ch1 and ch2.
	//AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_TIM3_REMAP ) | AFIO_MAPR_TIM3_REMAP_1; // Activated PB3 but deactivated

	palSetPadMode( PORT_PWM_1, PAD_PWM_1, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_2, PAD_PWM_2, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_3, PAD_PWM_3, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_4, PAD_PWM_4, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_5, PAD_PWM_5, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_6, PAD_PWM_6, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_7, PAD_PWM_7, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
	palSetPadMode( PORT_PWM_8, PAD_PWM_8, PAL_MODE_STM32_ALTERNATE_PUSHPULL );
}

void finitPwm( void )
{
	pwmStop( &PWMD2 );
	pwmStop( &PWMD3 );
	pwmStop( &PWMD4 );
}

void setPwmPeriod( int period_us )
{
    // PWM_CLOCK_FREQ / 1000000 * period_us;
    int cnt = PWM_CLOCK_FREQ / 1000000 * period_us;

    PWMConfig pwmCfg2 =
    {
        PWM_CLOCK_FREQ, // 1000kHz PWM clock frequency.
        cnt,            // Initial PWM period 10us.
        NULL,
        {
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_DISABLED, NULL },
            { PWM_OUTPUT_DISABLED, NULL }
        },
        0,
	#if STM32_PWM_USE_ADVANCED
        0
	#endif
    };
	pwmStart( &PWMD2, &pwmCfg2 );

    PWMConfig pwmCfg3 =
    {
        PWM_CLOCK_FREQ, // 1000kHz PWM clock frequency.
        cnt,            // Initial PWM period 10us.
        NULL,
        {
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL }
        },
        0,
	#if STM32_PWM_USE_ADVANCED
        0
	#endif
    };
	pwmStart( &PWMD3, &pwmCfg3 );

    PWMConfig pwmCfg4 =
    {
        PWM_CLOCK_FREQ, // 1000kHz PWM clock frequency.
        cnt,            // Initial PWM period 10us.
        NULL,
        {
            { PWM_OUTPUT_DISABLED,    NULL },
            { PWM_OUTPUT_DISABLED,    NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL },
            { PWM_OUTPUT_ACTIVE_HIGH, NULL }
        },
        0,
	#if STM32_PWM_USE_ADVANCED
        0
	#endif
    };
	pwmStart( &PWMD4, &pwmCfg4 );

}

void setPwm( uint32_t mask, int value )
{

	//if ( mask & (1<<0) )
	//	pwmEnableChannel( &PWMD2, 2, PWM_PERCENTAGE_TO_WIDTH( &PWMD2, value ) );
	//if ( mask & (1<<1) )
	//	pwmEnableChannel( &PWMD3, 1, PWM_PERCENTAGE_TO_WIDTH( &PWMD3, value ) );
	//if ( mask & (1<<2) )
	//	pwmEnableChannel( &PWMD3, 2, PWM_PERCENTAGE_TO_WIDTH( &PWMD3, value ) );
	//if ( mask & (1<<3) )
	//	pwmEnableChannel( &PWMD4, 3, PWM_PERCENTAGE_TO_WIDTH( &PWMD4, value ) );
	//if ( mask & (1<<4) )
	//	pwmEnableChannel( &PWMD4, 4, PWM_PERCENTAGE_TO_WIDTH( &PWMD4, value ) );
	if ( mask & (1<<5) )
		pwmEnableChannel( &PWMD3, 4, PWM_PERCENTAGE_TO_WIDTH( &PWMD3, value ) );
	if ( mask & (1<<6) )
		pwmEnableChannel( &PWMD3, 3, PWM_PERCENTAGE_TO_WIDTH( &PWMD3, value ) );
	//if ( mask & (1<<7) )
	//	pwmEnableChannel( &PWMD2, 1, PWM_PERCENTAGE_TO_WIDTH( &PWMD2, value ) );
}


