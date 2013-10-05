
#include "ch.h"
#include "hal.h"

/*
static void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;
  //palSetPad(IOPORT3, GPIOC_LED);
}

static void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  //palClearPad(IOPORT3, GPIOC_LED);
}

static PWMConfig pwmcfg = {
  10000,                                    // 10kHz PWM clock frequency.
  10000,                                    // Initial PWM period 1S.
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, NULL },
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL},
   {PWM_OUTPUT_DISABLED, NULL}
  },
  0,
#if STM32_PWM_USE_ADVANCED
  0
#endif
};

int main(void) {


  halInit();
  chSysInit();


  pwmStart(&PWMD3, &pwmcfg);
  palSetPadMode(GPIOA, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

  chThdSleepMilliseconds(2000);


  pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 7500));
  chThdSleepMilliseconds(5000);


  pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 5000));
  chThdSleepMilliseconds(5000);


  pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 2500));
  chThdSleepMilliseconds(5000);


  pwmChangePeriod(&PWMD3, 5000);
  chThdSleepMilliseconds(5000);


  pwmDisableChannel(&PWMD3, 0);
  pwmStop(&PWMD3);
  //icuDisable(&ICUD4);
  //icuStop(&ICUD4);
  //palSetPad(IOPORT3, GPIOC_LED);


  while (TRUE) {
    chThdSleepMilliseconds(500);
  }
  return 0;
}
*/


#include "165_ctrl.h"
#include "595_ctrl.h"
#include "pwm_ctrl.h"
#include "pwr_ctrl.h"
#include "adc_ctrl.h"
#include "i2c_ctrl.h"

static void delay( void );


int main(void)
{
    halInit();
    chSysInit();

    init165();
    init595();
    initAdc();
    initPwm();
    initPwr();
    //initI2c();

    //processI2c();

    setPwmPeriod( 1000000 );
    setPwm( 255, 1000 );

    while ( 1 )
    {
    	int a = measureAdc( 0 );
    	setLed( a & 3 );
    	//setMoto( 1 );
    	chThdSleepMilliseconds( 200 );
    }
    return 0;
}

static void delay( void )
{
    #define CNT 10000
	volatile int i;
	for ( i=0; i<CNT; i++ )
		;
}








