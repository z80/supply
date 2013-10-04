
#include "ch.h"
#include "hal.h"

#include "165_ctrl.h"
#include "595_ctrl.h"
#include "pwm_ctrl.h"
#include "pwr_ctrl.h"
#include "adc_ctrl.h"
#include "i2c_ctrl.h"

int main(void)
{
    halInit();
    chSysInit();

    init165();
    init595();
    initAdc();
    initPwm();
    initPwr();
    initI2c();

    processI2c();
    return 0;
}






