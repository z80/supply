
#include <supply>
#include <addon>

waitTrigger()
{
    msleep( 500 );
    while( !trigger() )
    {
        setLed( 0 );
        msleep( 100 );
        setLed( 1 );
        msleep( 100 );
    }

    setLed( 3 );
    msleep( 100 );
    setLed( 0 );
}

main()
{
    //waitTrigger()
    setI2cEn( 1 );
    
    for ( ;; )
    {
        //waitTrigger()
        new val = addInput( 0 ) //addAdc( 0, 0 )
        setIo( 0, val )
	val = addAdc( 0, 0 )
        setIo( 1, val & 255 )
	setIo( 2, val >> 8 )
	msleep( 500 )
    }
}



