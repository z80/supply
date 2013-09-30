#include <supply>

main()
{
    setLed( 1 );
    msleep( 3000 );

    setI2cEn( 1 );
    setLed( 2 );
    msleep( 3000 );

    new addr  = 25;
    new wrCnt = 2;
    new rdCnt = 0;
    new wr[ 4 ];
    new rd[ 4 ];
    new timeout = 500;

    wr[0] = 32;
    wr[1] = 39;
    wr[2] = 0;
    wr[3] = 0;

    new res = i2cIo( addr, 
                     wr, wrCnt, 
                     rd, rdCnt, 
                     timeout );
    setIo( 0, res );

    for ( ;; )
    {
        setLed( 1 );
        msleep( 200 );

        setLed( 2 );
        msleep( 200 );
    }
}


