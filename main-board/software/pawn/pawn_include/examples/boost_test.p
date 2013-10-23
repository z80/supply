#include <supply>

main()
{
    setLed( 1 );
    msleep( 3000 );

    convSetBoost( 7000 );
    setLed( 2 );
    msleep( 3000 );

    for ( ;; )
    {
        setLed( 1 );
        msleep( 200 );

        setLed( 2 );
        msleep( 200 );
    }
}


