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
        msleep( 3000 );

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



