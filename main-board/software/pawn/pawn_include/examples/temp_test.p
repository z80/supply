#include <supply>

main()
{
    setLed( 1 );
    msleep( 3000 );

    convSetBoost( 7000 );
    setLed( 2 );
    msleep( 3000 );
    
    new t;
    new tHigh;
    new tLow;
    for ( ;; )
    {
        t = adcTemp();
        tHigh = t / 256;
        tLow = t - tHigh * 256;
        setIo( 0, tHigh );
        setIo( 1, tLow );
        setLed( 1 );
        msleep( 200 );

        setLed( 2 );
        msleep( 200 );
    }
}


