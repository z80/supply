
#include <supply>

#define LED_T 250

new V = 0;
new I = 0;
//~ new ledT = 0;

updateIv()
{
    msleep( 10 );
    V = adcBuckVolt();
    msleep( 10 );
    I = adcBuckCurr();
    setIo( 4, V >> 8 );
    setIo( 5, V & 255 );
    setIo( 6, I >> 8 );
    setIo( 7, I & 255 );

    new vv = ( io( 0 ) << 8 ) + io( 1 );
    new ii = ( io( 2 ) << 8 ) + io( 3 );
    convSetBuck( vv );
    convSetBuckCurr( ii );
}

main()
{
    setIo( 0, 0 );
    setIo( 1, 0 );
    setIo( 2, 0 );
    setIo( 3, 0 );
    // Zero voltage and current.
    convSetBuck( 0 );
    convSetBuckCurr( 0 );
    // Minimal gain.
    convSetBuckGain( 1 );
    
    new led = 0;
    for ( ;; )
    {
        msleep( 10 );
        updateIv(); 
        led = (led + 1) % 4;
        setLed( led );
        msleep( 130 );
    }
}




