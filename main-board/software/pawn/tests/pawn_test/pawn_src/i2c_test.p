#include <supply>

main()
{
    setLed( 1 );
    msleep( 3000 );

    setI2cEn( 1 );
    setLed( 2 );
    msleep( 3000 );

    new addr  = 25;
    new wr[ 6 ];
    new rd[ 6 ];
    new timeout = 500;

    wr[0] = 0x20;
    wr[1] = 0x27;
    wr[2] = 0;
    wr[3] = 0;

    new res = i2cIo( addr, 
                     wr, 2, 
                     rd, 0, 
                     timeout );
    setIo( 0, res );

    wr[0] = 0x23;
    wr[1] = 0;
    res = i2cIo( addr, 
                 wr, 2, 
                 rd, 0, 
                 timeout );

    addr = 30;
    wr[0] = 0;
    wr[1] = 0x90
    res = i2cIo( addr, wr, 2, rd, 0, timeout );

    wr[0] = 0x02;
    wr[1] = 0x00;
    res = i2cIo( addr, wr, 2, rd, 0, timeout );
 
    for ( ;; )
    {
        addr = 30;
        wr[0] = 0x03;
        res = i2cIo( addr, wr, 1, 
                           rd, 6, timeout );
        setIo( 0, res );
        setIo( 1, rd[0] );
        setIo( 2, rd[1] );
        setIo( 3, rd[2] );
        setIo( 4, rd[3] );
        setIo( 5, rd[4] );
        setIo( 6, rd[5] );

        setLed( 1 );
        msleep( 200 );

        setLed( 2 );
        msleep( 200 );
    }
}


