
#include "ch.h"
#include "hal.h"


static void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;
  //palSetPad(IOPORT3, GPIOC_LED);
}

static void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  //palClearPad(IOPORT3, GPIOC_LED);
}

static PWMConfig pwmcfg = {
  10000,                                    /* 10kHz PWM clock frequency.   */
  10000,                                    /* Initial PWM period 1S.       */
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

/*
icucnt_t last_width, last_period;

static void icuwidthcb(ICUDriver *icup) {

  last_width = icuGetWidthI(icup);
}

static void icuperiodcb(ICUDriver *icup) {

  last_period = icuGetPeriodI(icup);
}

static ICUConfig icucfg = {
  ICU_INPUT_ACTIVE_HIGH,
  10000,                                    // 10kHz ICU clock frequency.
  icuwidthcb,
  icuperiodcb
};
*/
/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * LED initially off.
   */
  //palSetPad(IOPORT3, GPIOC_LED);

  /*
   * Initializes the PWM driver 1 and ICU driver 4.
   */
  pwmStart(&PWMD3, &pwmcfg);
  palSetPadMode(GPIOA, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  /*icuStart(&ICUD4, &icucfg);
  icuEnable(&ICUD4);*/
  chThdSleepMilliseconds(2000);

  /*
   * Starts the PWM channel 0 using 75% duty cycle.
   */
  pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 7500));
  chThdSleepMilliseconds(5000);

  /*
   * Changes the PWM channel 0 to 50% duty cycle.
   */
  pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 5000));
  chThdSleepMilliseconds(5000);

  /*
   * Changes the PWM channel 0 to 25% duty cycle.
   */
  pwmEnableChannel(&PWMD3, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD3, 2500));
  chThdSleepMilliseconds(5000);

  /*
   * Changes PWM period to half second the duty cycle becomes 50%
   * implicitly.
   */
  pwmChangePeriod(&PWMD3, 5000);
  chThdSleepMilliseconds(5000);

  /*
   * Disables channel 0 and stops the drivers.
   */
  pwmDisableChannel(&PWMD3, 0);
  pwmStop(&PWMD3);
  //icuDisable(&ICUD4);
  //icuStop(&ICUD4);
  //palSetPad(IOPORT3, GPIOC_LED);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (TRUE) {
    chThdSleepMilliseconds(500);
  }
  return 0;
}


/*
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

    //init165();
    init595();
    //initAdc();
    initPwm();
    //initPwr();
    //initI2c();

    //processI2c();

    setPwmPeriod( 1000000 );
    setPwm( 255, 1000 );

    while ( 1 )
    {
    	setLed( 1 );
    	//setMoto( 1 );
    	chThdSleepMilliseconds( 200 );

    	setLed( 2 );
    	//setMoto( 2 );
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
*/







