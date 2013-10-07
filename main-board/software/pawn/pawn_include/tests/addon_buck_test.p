
#include <supply>
#include <addon>

main()
{
    convSetBuckCurr( 100 )
    convSetBuck( 2000 )

    new i
    for ( i=0; i<30; i++ )
    {
        setLed( 3 )
        msleep( 50 )

        setLed( 0 )
        msleep( 50 )
    }

    setI2cEn( 1 );
    setLed( 2 );
    msleep( 1000 );

    for ( ;; )
    {
        setLed( 1 );
        addSetLed( 0, 1 );
        msleep( 500 );

        setLed( 2 );
        addSetLed( 0, 2 );
        msleep( 500 );
    }
}
