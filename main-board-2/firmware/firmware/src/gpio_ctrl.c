
#include "gpio_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "hdw_cfg.h"

static int period;

typedef struct 
{
    int mask;
    int time;
} TStop;

#define PWM_CNT 9
#define TIMER   GPTD1

static int   pwm[PWM_CNT];
static TStop stops[PWM_CNT];
static int   stopInd;
static int   stopsCnt;

// Recalculate stops[] using pwm[]
static void updateStops( void );
static void updateTimer( void );

void gpioInit( void )
{
    stopInd  = 0;
    stopsCnt = 0;
    period = 20;
    int i;
    for ( i=0; i<PWM_CNT; i++ )
        pwm[ i ] = 0;
}

void gpioSetMode( int mask, int mode )
{
    switch ( mode )
    {
        case GPIO_IN:
            if ( mask & (1<<0) )
                palSetPadMode( GPIO_1_PORT, GPIO_1_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<1) )
                palSetPadMode( GPIO_2_PORT, GPIO_2_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<2) )
                palSetPadMode( GPIO_3_PORT, GPIO_3_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<3) )
                palSetPadMode( GPIO_4_PORT, GPIO_4_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<4) )
                palSetPadMode( GPIO_5_PORT, GPIO_5_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<5) )
                palSetPadMode( GPIO_6_PORT, GPIO_6_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<6) )
                palSetPadMode( GPIO_7_PORT, GPIO_7_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<7) )
                palSetPadMode( GPIO_8_PORT, GPIO_8_PAD, PAL_MODE_INPUT );
            if ( mask & (1<<8) )
                palSetPadMode( GPIO_9_PORT, GPIO_9_PAD, PAL_MODE_INPUT );
            return 0;
        break

        case GPIO_OUT:
            if ( mask & (1<<0) )
                palSetPadMode( GPIO_1_PORT, GPIO_1_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<1) )
                palSetPadMode( GPIO_2_PORT, GPIO_2_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<2) )
                palSetPadMode( GPIO_3_PORT, GPIO_3_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<3) )
                palSetPadMode( GPIO_4_PORT, GPIO_4_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<4) )
                palSetPadMode( GPIO_5_PORT, GPIO_5_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<5) )
                palSetPadMode( GPIO_6_PORT, GPIO_6_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<6) )
                palSetPadMode( GPIO_7_PORT, GPIO_7_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<7) )
                palSetPadMode( GPIO_8_PORT, GPIO_8_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            if ( mask & (1<<8) )
                palSetPadMode( GPIO_9_PORT, GPIO_9_PAD, PAL_MODE_OUTPUT_PUSHPULL );
            return 0;
        break

        case GPIO_AIN:
            if ( mask & (1<<1) )
                palSetPadMode( GPIO_2_PORT, GPIO_2_PAD, PAL_MODE_INPUT_ANALOG );
            if ( mask & (1<<2) )
                palSetPadMode( GPIO_3_PORT, GPIO_3_PAD, PAL_MODE_INPUT_ANALOG );
            if ( mask & (1<<3) )
                palSetPadMode( GPIO_4_PORT, GPIO_4_PAD, PAL_MODE_INPUT_ANALOG );
            if ( mask & (1<<5) )
                palSetPadMode( GPIO_6_PORT, GPIO_6_PAD, PAL_MODE_INPUT_ANALOG );
            if ( mask & (1<<6) )
                palSetPadMode( GPIO_7_PORT, GPIO_7_PAD, PAL_MODE_INPUT_ANALOG );
            if ( mask & (1<<7) )
                palSetPadMode( GPIO_8_PORT, GPIO_8_PAD, PAL_MODE_INPUT_ANALOG );
            if ( mask & (1<<8) )
                palSetPadMode( GPIO_9_PORT, GPIO_9_PAD, PAL_MODE_INPUT_ANALOG );
        break
    }
    return 1;
}

int  gpios( int mask )
{
    int res = 0;

    if ( mask & ( (1<<GPIO_3_PAD) | 
                  (1<<GPIO_4_PAD) | 
                  (1<<GPIO_6_PAD) | 
                  (1<<GPIO_7_PAD) | 
                  (1<<GPIO_8_PAD) |
                  (1<<GPIO_9_PAD) ) )
    {
        int resA = palReadPort( GPIOA );
        res = ( ( (1<<GPIO_3_PAD) ? 1 : 0 ) << 2 ) | 
              ( ( (1<<GPIO_4_PAD) ? 1 : 0 ) << 3 ) | 
              ( ( (1<<GPIO_6_PAD) ? 1 : 0 ) << 5 ) | 
              ( ( (1<<GPIO_7_PAD) ? 1 : 0 ) << 6 ) | 
              ( ( (1<<GPIO_8_PAD) ? 1 : 0 ) << 7 ) | 
              ( ( (1<<GPIO_9_PAD) ? 1 : 0 ) << 8 );
    }

    if ( mask & ( (1<<GPIO_1_PAD) | 
                  (1<<GPIO_2_PAD) | 
                  (1<<GPIO_5_PAD) ) )
    {
        int resB = palReadPort( GPIOB );
        res |=   ( (1<<GPIO_1_PAD) ? 1 : 0 ) | 
               ( ( (1<<GPIO_2_PAD) ? 1 : 0 ) << 1 ) | 
               ( ( (1<<GPIO_5_PAD) ? 1 : 0 ) << 4 );
    }

    return res;
}

int  gpio( int ind )
{
    int port;
    int pad;

    switch ( ind )
    {
        case 0:
            port = GPIO_1_PORT;
            pad  = GPIO_1_PAD;
            break;
        case 1:
            port = GPIO_2_PORT;
            pad  = GPIO_2_PAD;
            break;
        case 2:
            port = GPIO_3_PORT;
            pad  = GPIO_3_PAD;
            break;
        case 3:
            port = GPIO_4_PORT;
            pad  = GPIO_4_PAD;
            break;
        case 4:
            port = GPIO_5_PORT;
            pad  = GPIO_5_PAD;
            break;
        case 5:
            port = GPIO_6_PORT;
            pad  = GPIO_6_PAD;
            break;
        case 6:
            port = GPIO_7_PORT;
            pad  = GPIO_7_PAD;
            break;
        case 7:
            port = GPIO_8_PORT;
            pad  = GPIO_8_PAD;
            break;
        default:
            port = GPIO_9_PORT;
            pad  = GPIO_9_PAD;
            break;
    }

    return palReadPad( port, pad );
}

void gpioSetPeriod( int us )
{
    period = us;
}

void gpioSetPwm( int mask, int us )
{
    int i;
    for ( i=0; i<PWM_CNT; i++ )
    {
        if ( mask & (1<<i) )
            pwm[i] = us;
    }
}

static void updateStops( void )
{
    // Brute fill values.
    int i;
    for ( i=0; i<PWM_CNT; i++ )
    {
        stops[i].mask = (1<<i);
        stops[i].time = pwm[i];
    }

    // Sort by time ascending
    stopsCnt = 9;
    int j;
    for ( i=0; i<PWM_CNT-1; i++ )
    {
        for ( j=i+1; j<PWM_CNT; j++ )
        {
            int t;
            if ( stops[i].time > stops[j].time )
            {
                // Swap places.
                t = stops[i].time;
                stops[i].time = stops[j].time;
                stops[j].time = t;

                t = stops[i].mask;
                stops[i].mask = stops[j].mask;
                stops[j].mask = t;
            }
        }
    }

    // Remove zero time values.
    for ( i=0; i<PWM_CNT; i++ )
    {
        if ( stops[i].time <= 0 )
        {
            stopsCnt -= 1;
            for ( j=i; j<PWM_CNT-1; j++ )
            {
                stops[j].time = stops[j+1].time;
                stops[j].mask = stops[j+1].mask;
                // As values are shifted index shouldn't be increased.
                i -= 1;
            }
        }
    }

    int lastStops = stopsCnt;
    // Merge neighbor stops.
    for ( i=0; i<lastStops-1; i++ )
    {
        for ( j=i+1; j<lastStops; j++ )
        {
            if ( stops[i].time == stops[j].time )
            {
                // Merge
                stops[i].mask |= stops[j].mask;
                // Shift down
                int k;
                for ( k=j; k<lastStops-1; k++ )
                {
                    stops[j].mask |= stops[j+1].mask;
                    stops[j].time = stops[j+1].mask;
                }

                stopsCnt -= 1;
                // As values are shifted current index shouldn't be increased.
                j = j-1;
            }
            else
                // Values are sorted so if not equal break the inner loop.
                break;
        }
    }


}

static void gptCb( GPTDriver * gptp );

static const GPTConfig gptCfg = 
{
  10000,    // 10kHz timer clock
  gptCb     // Timer callback
};

static void updateTimer( void )
{
    gptStopTimer( TIMER );
    updateStops();

    stopInd = stopsCnt;
    gptStartOneShot( TIMER, &gptCfg );
}

static void gptCb( GPTDriver * gptp )
{
    // 1) If loop should be made.
    if ( stopInd >= stopsCnt )
    {

    }
}



