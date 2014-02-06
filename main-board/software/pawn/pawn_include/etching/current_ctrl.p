
#include <supply>

new V = 0;
new I = 0;

updateIv()
{
    new vv = adcBuckVolt();
    new ii = adcBuckCurr();
    new b;
    
    b = V * 999 + vv;
    V = b / 1000;
    setIo( 5, V >> 8 );
    setIo( 6, V & 255 );
    
    b = I * 999 + ii;
    I = b / 1000;
    setIo( 7, I >> 8 );
    setIo( 8, I & 255 );

    if ( io( 0 ) )
    {
        setIo( 0, 0 );
        vv = io( 1 ) + ( io( 2 ) << 8 );
        ii = io( 3 ) + ( io( 3 ) << 8 );
        convSetBuck( vv );
        convSetBuckCurr( ii );
    }
}

main()
{
    // Reset values apply.
    setIo( 0, 0 );
    // Zero voltage and current.
    convSetBuck( 0 );
    convSetBuckCurr( 0 );
    // Minimal gain.
    convSetBuckGain( 1 );
    for ( ;; )
    {
        msleep( 1 );
        updateIv(); 
    }
}




