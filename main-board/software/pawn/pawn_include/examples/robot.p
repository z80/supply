
#include <supply>
#include <addon>

main()
{
    new period = 20000
    setI2cEn( 1 )
    addSetPwmPeriod( 0, period )
    setIo( 0, 0 )
    setIo( 1, 0 )
    setIo( 2, 0 )
    setIo( 3, 127 )
    setIo( 4, 127 )

    new led = 0

    for ( ;; )
    {
        //waitTrigger();
        //convSetBuckCurr( 1500 )
        //convSetBuck( 5000 )
        //msleep( 15000 )
        //setI2cSlaveEn( 1 )
    
        while ( trigger() == 0 )
        {
            setLed( led )
            led = led + 1
            if ( led > 3 )
                led = 0
            msleep( 100 )

            if ( io( 0 ) > 0 )
            {
                setIo( 0, 0 )
                new moto   = io( 1 )
                new light  = io( 2 )
                new servoX = io( 3 )
                new servoY = io( 4 )
                setMoto( moto )
                setLight( light )
                
                servoX = 500 + 1000 * servoX / 255
                servoX = servoX * 10000 / period
                addSetPwm( 0, 32, servoX )
                
                servoY = 500 + 1000 * servoY / 255
                servoY = servoY * 10000 / period
                addSetPwm( 0, 64, servoY )
            }
        }
        //setI2cSlaveEn( 0 )
        //convSetBuck( 0 )
    }    
}



