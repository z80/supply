
#include <supply>
#include <addon>

main()
{
    convSetBuckCurr( 50 )
    convSetBuck( 2000 )

    new i
    for ( ;; )
    {
        setLed( 1 )
        msleep( 250 )

        setLed( 2 )
        msleep( 250 )
    }
}
