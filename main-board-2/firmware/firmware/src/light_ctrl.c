
#include "light_ctrl.h"
#include "ch.h"
#include "hal.h"

#include "hdw_cfg.h"

void initLight( void )
{
    setLight( 0 );
}

void setLight( bool_t en )
{
    if ( en )
        palSetPad( LIGHT_PORT, LIGHT_PIN );
    else
        palClearPad( LIGHT_PORT, LIGHT_PIN );
    // Configure pin to be output.
    palSetPadMode( LIGHT_PORT, LIGHT_PIN, PAL_MODE_OUTPUT_PUSHPULL );
}




