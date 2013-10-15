
#include <supply>
#include <addon>

waitTrigger()
{
    msleep( 2000 );
    while( !trigger() )
    {
        setLed( 0 );
        msleep( 100 );
        setLed( 1 );
        msleep( 100 );
    }

    setLed( 3 );
    msleep( 2000 );
    setLed( 0 );
}

main()
{
    new led = 0;
    setI2cEn( 1 );
    for ( ;; )
    {
        waitTrigger();
        addSetLed( 0, led );
        led = ( led + 1 ) % 4;
    }

    /*
    new i
    for ( i=0; i<300; i++ )
    {
        setLed( 3 )
        msleep( 50 )

        setLed( 0 )
        msleep( 50 )
    }

    setI2cEn( 1 );
    setLed( 2 );
    msleep( 10000 );
    
    addSetPwmPeriod( 0, 50000 );

    for ( ;; )
    {
	addSetPwm( 0, 255, 1000 );
	setLed( 1 );
        msleep( 5000 );

	addSetPwm( 0, 255, 1500 );
        setLed( 2 );
        msleep( 500 );
    }
    */
}
