
#include <supply>

blink()
{
    setLed( 1 )
    msleep( 250 )

    setLed( 2 )
    msleep( 250 )

    setLed( 1 )
    msleep( 250 )

    setLed( 2 )
    msleep( 250 )
}

main()
{
    convSetBuckCurr( 50 )
    convSetBuck( 2000 )

    for ( ;; )
    {
        setMoto( 0 )
        blink()
        blink()
        blink()

        setMoto( 5 )
        blink()
        blink()
        blink()

        setMoto( 10 )
        blink()
        blink()
        blink()

        setMoto( 1 )
        blink()
        blink()
        blink()

        setMoto( 4 )
        blink()
        blink()
        blink()
    }
}



