
#include <supply>

new ioBuffer[32]

read( i2cAddr, chipAddr, cnt )
{
	new wr[2]
	wr[0] = chipAddr

    // IO operation at I2C bus.
	setLed( 3 )
	new res = i2cIo( i2cAddr, wr, 1, ioBuffer, cnt, 500 )
	setLed( 0 )

    // Operation result.
	setIo( 1, res )
	new i
	for ( i=0; i<cnt; i++ )
	    setIo( i+2, ioBuffer[i] )

    return res
}

write( i2cAddr, chipAddr, cnt )
{
    ioBuffer[0] = chipAddr
    new i
    for ( i=0; i<cnt; i++ )
        ioBuffer[i+1] = io( i+4 )

    // IO operation at I2C bus.
    setLed( 3 )
    new res = i2cIo( i2cAddr, ioBuffer, cnt+1, ioBuffer, 0, 500 )
    setLed( 0 )

    return res
}

main()
{
    new led = 0
    // Reset command at the very beginning.
    setIo( 0, 0 )
    setI2cEn( 1 )
    for ( ;; )
    {
        new i2cAddr
        new devAddr
        new cnt
        new res
        // Check if read operation?
        if ( io( 0 ) == 1 )
        {
            i2cAddr = io( 1 )
            devAddr = io( 2 )
            cnt     = io( 3 )
            res     = read( i2cAddr, devAddr, cnt )
            setIo( 1, res )
            setIo( 0, 0 )
        }
        // Else check if write operation?
        else if ( io( 0 ) == 2 )
        {
            i2cAddr = io( 1 )
            devAddr = io( 2 )
            cnt     = io( 3 )
            res     = write( i2cAddr, devAddr, cnt )
            setIo( 1, res )
            // Report operation is completed
            setIo( 0, 0 )
        }
        // Else it is unrecognized and just reset!
        else
            setIo( 0, 0 )
        // Some delay.
        msleep( 50 )

        // Blinking LED number 1.
        setLed( led )
        if ( led == 0 )
            led = 1
        else
            led = 0
        // When IO takes place both LEDs should blink.
    }
}


