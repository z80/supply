
#include <supply>
#include <addon>

main()
{
    new i
    for ( i=0; i<10; i++ )
    {
        setLed( 3 )
        msleep( 50 )

        setLed( 0 )
        msleep( 50 )
    }

    setI2cEn( 1 );
    setLed( 2 );
    msleep( 1000 );
    
    addSetPwmPeriod( 0, 50000 );

    for ( ;; )
    {
	addSetPwm( 0, 255, 1000 );
	addSetLed( 0, 1 );
	setLed( 1 );
        msleep( 500 );

	addSetPwm( 0, 255, 1500 );
        setLed( 2 );
        addSetLed( 0, 2 );
        msleep( 500 );
    }
}
