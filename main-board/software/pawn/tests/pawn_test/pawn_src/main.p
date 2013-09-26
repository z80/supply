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

        setMoto( 1 );
        msleep( 500 );

        setMoto( 3 );
        msleep( 500 );

        setMoto( 7 );
        msleep( 500 );

        setMoto( 15 );
        msleep( 500 );
    }
}



