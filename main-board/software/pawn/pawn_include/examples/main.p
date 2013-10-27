#include <supply>

main()
{
    for ( ;; )
    {
        setLed( 1 );
        msleep( 50 );
        setLed( 2 );
        msleep( 50 );
        setLed( 0 );
        msleep( 50 );
        setLed( 3 );
        msleep( 50 );

        setLed( 0 );
        setMoto( 0 );
        msleep( 500 );

        setLight( 1 );
        msleep( 1000 );
        setLight( 0 );

        setMoto( 1 );
        msleep( 500 );

        setMoto( 2 );
        msleep( 500 );

        setMoto( 4 );
        msleep( 500 );

        setMoto( 8 );
        msleep( 500 );
    }
}



