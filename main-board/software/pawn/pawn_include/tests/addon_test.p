
#include <supply>
#include <addon>

main()
{
    new i
    for ( i=0; i<30; i++ )
    {
        setLed( 3 )
        msleep( 50 )

        setLed( 0 )
        msleep( 50 )
    }

    setI2cEn( 1 );
    setLed( 0 );
    msleep( 500 );

    for ( ;; )
    {
        setLed( 1 );
        addSetLed( 0, 0 );
        addSetLed( 1, 0 );
        msleep( 200 );

        setLed( 0 );
        addSetLed( 0, 1 );
        addSetLed( 1, 0 );
        msleep( 200 );

        setLed( 0 );
        addSetLed( 0, 0 );
        addSetLed( 1, 1 );
        msleep( 200 );

        setLed( 0 );
        addSetLed( 0, 0 );
        addSetLed( 1, 2 );
        msleep( 200 );

        setLed( 0 );
        addSetLed( 0, 2 );
        addSetLed( 1, 0 );
        msleep( 200 );

        setLed( 2 );
        addSetLed( 0, 0 );
        addSetLed( 1, 0 );
        msleep( 200 );
    }
}
