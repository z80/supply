
#if !defined __ADDON_INC_
#define __ADDON_INC_

#include <supply>

const BASE_ADDR    = 1
const BASE_TIMEOUT = 500

const CMD_VERSION        = 1
const CMD_SET_LED        = 2
const CMD_SET_MOTO       = 3
const CMD_SET_PWM_PERIOD = 4
const CMD_SET_PWM        = 5
const CMD_INPUT          = 6
const CMD_ADC            = 7
const CMD_SLEEP          = 8 


addVersion( index )
{
    return 0;
}

addSetLed( index, arg )
{
    new addr = BASE_ADDR + index;
    new res
    new wr[2];
    wr[0] = CMD_SET_LED;
    wr[1] = arg;
    res = i2cIo( addr, wr, 2, wr, 0, BASE_TIMEOUT );
    return res;
}

addSetMoto( index, arg )
{
    new addr = BASE_ADDR + index;
    new res
    new wr[2];
    wr[0] = CMD_SET_MOTO;
    wr[1] = arg;
    res = i2cIo( addr, wr, 2, wr, 0, BASE_TIMEOUT );
    return res;
}

addSetPwmPeriod( index, us )
{
    new addr = BASE_ADDR + index;
    new res;
    new wr[5];
    wr[0] = CMD_SET_PWM_PERIOD;
    wr[1] = (us / 16777216) & 0xFF;
    wr[2] = (us / 65536) & 0xFF;
    wr[3] = (us / 256) & 0xFF;
    wr[4] = us & 0xFF;
    res = i2cIo( addr, wr, 5, wr, 0, BASE_TIMEOUT );
    return res;
}

addSetPwm( index, mask, percentOver100 )
{
    new addr = BASE_ADDR + index;
    new res;
    new wr[6];
    wr[0] = CMD_SET_PWM;
    wr[1] = mask
    wr[2] = (percentOver100 / 16777216) & 0xFF;
    wr[3] = (percentOver100 / 65536) & 0xFF;
    wr[4] = (percentOver100 / 256) & 0xFF;
    wr[5] = percentOver100 & 0xFF;
    res = i2cIo( addr, wr, 6, wr, 0, BASE_TIMEOUT );
    return res;
}

addInput( index )
{
    return 0;
}

addAdc( index, adcIndex )
{
    return 0;
}

addSleep( index )
{
    new addr = BASE_ADDR + index;
    new res
    new wr[2];
    wr[0] = CMD_SLEEP;
    res = i2cIo( addr, wr, 2, wr, 0, BASE_TIMEOUT );
    return res;
}

#endif




