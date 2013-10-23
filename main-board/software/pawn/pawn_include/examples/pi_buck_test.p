
#include <supply>
#include <addon>


// Function which regulary queries if trigger button is pressed .
waitTrigger()
{
    // Wait for a second for the case if previous 
    // trigger event just happened. To give one some time 
    // To unpress the button.
    msleep( 1000 );
    // Infinite loop waiting for a trigger.
    while( !trigger() )
    {
        // Turn LEDs off.
        setLed( 0 );
        // Wait for 1/10 of a second.
        msleep( 100 );

        // Set first LED on.
        setLed( 1 );
        // Wait for 1/10 of a second.
        msleep( 100 );
    }

    // We can be here if one's pressed the button.
    // Set second LED on.
    setLed( 2 );
    // Wait for 1/10 of a second.
    msleep( 100 );
    // Turn all LEDs off.
    setLed( 0 );
}

main()
{
    // Set current limit to 1.5A
    convSetBuckCurr( 1500 );
    for ( ;; )
    {
        // Wait for a button press.
        waitTrigger();
        // Set step down converter voltage to 5V.
        convSetBuck( 5000 );

        // Wait for another button press.
        waitTrigger();
        // Turn voltage off by setting it to be 0V.
        convSetBuck( 0 );

        // Loop ....... :)
    }
}




