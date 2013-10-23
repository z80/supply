
#include <supply>
#include <addon>

// The simpliest control of 2 servos.
main()
{
    new period = 20000;
    setIo( 0, 127 );
    setI2cEn( 1 );

    addSetPwmPeriod( 0, 20000 );

    new led = 0
    for ( ;; )
    {
        addSetLed( 0, led )
        led = led + 1
        if ( led > 3 )
            led = 0;
        msleep( 50 );

        new v = io( 0 );
        // To microseconds.
        v = 500 + (2500 - 500) * v / 255;
        v = v * 10000 / period;
        addSetPwm( 0, 64, v );
	
	v = io( 1 );
        v = 500 + (2500 - 500) * v / 255;
        v = v * 10000 / period;
        addSetPwm( 0, 32, v );
    }
}


