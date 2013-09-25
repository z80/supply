#include <supply>

main()
{
    for ( ;; )
    {
        setLed( 1 );
        msleep( 500 );
        setLed( 2 );
        msleep( 500 );
    }
}



