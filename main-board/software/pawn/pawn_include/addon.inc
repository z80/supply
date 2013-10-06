
#include "supply.inc"

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
    res = i2cIo( addr, CMD_SLEEP, 2, _, 0, BASE_TIMEOUT );
    return res;
}

addSetMoto( index, arg )
{
    new addr = BASE_ADDR + index;
    new res
    new wr[2];
    wr[0] = CMD_SET_MOTO;
    res = i2cIo( addr, CMD_SLEEP, 2, _, 0, BASE_TIMEOUT );
    return res;
}

addSetPwmPeriod( index, us )
{
    return 0;
}

addSetPwm( index, mask, percentOver100 )
{
    return 0;
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
    res = i2cIo( addr, CMD_SLEEP, 2, _, 0, BASE_TIMEOUT );
    return res;
}



