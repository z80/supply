
#include <supply>
#include <addon>

waitTrigger()
{
    msleep( 1000 );
    while( !trigger() )
    {
        setLed( 0 );
        msleep( 100 );
        setLed( 1 );
        msleep( 100 );
    }

    setLed( 2 );
    msleep( 100 );
    setLed( 0 );
}

main()
{
    convSetBuckCurr( 1500 );
    for ( ;; )
    {
        waitTrigger();
        convSetBuck( 5000 );

        waitTrigger();
        convSetBuck( 0 );
    }
}
