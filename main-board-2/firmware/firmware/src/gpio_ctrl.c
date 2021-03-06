
#include "gpio_ctrl.h"
#include "ch.h"
#include "hal.h"
#include "hdw_cfg.h"
#include "moto_ctrl.h"

static int period;

typedef struct 
{
    int mask;
    int time;
} TStop;

#define PWM_CNT 9
#define TIMER   GPTD1

static int   pwm[PWM_CNT];
static int   modes[PWM_CNT];
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

    adcStart( &ADCD1, NULL );
}

int  gpioSetMode( int mask, int mode )
{
    int i;
    for ( i=0; i<PWM_CNT; i++ )
    {
        if ( mask & (1<<i) )
            modes[i] = mode;
    }
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
        break;

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
        break;

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
        break;
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
        res = ( ( (resA & (1<<GPIO_3_PAD)) ? 1 : 0 ) << 2 ) | 
              ( ( (resA & (1<<GPIO_4_PAD)) ? 1 : 0 ) << 3 ) | 
              ( ( (resA & (1<<GPIO_6_PAD)) ? 1 : 0 ) << 5 ) | 
              ( ( (resA & (1<<GPIO_7_PAD)) ? 1 : 0 ) << 6 ) | 
              ( ( (resA & (1<<GPIO_8_PAD)) ? 1 : 0 ) << 7 ) | 
              ( ( (resA & (1<<GPIO_9_PAD)) ? 1 : 0 ) << 8 );
    }

    if ( mask & ( (1<<GPIO_1_PAD) | 
                  (1<<GPIO_2_PAD) | 
                  (1<<GPIO_5_PAD) ) )
    {
        int resB = palReadPort( GPIOB );
        res |=   ( (resB & (1<<GPIO_1_PAD)) ? 1 : 0 ) | 
               ( ( (resB & (1<<GPIO_2_PAD)) ? 1 : 0 ) << 1 ) | 
               ( ( (resB & (1<<GPIO_5_PAD)) ? 1 : 0 ) << 4 );
    }

    return res;
}

static int gpioDig( int ind );
static int gpioAn( int ind );

int  gpio( int ind )
{
    if ( ( ind > 0 ) && ( ind < PWM_CNT ) )
    {
        if ( modes[ ind ] == GPIO_IN )
            return gpioDig( ind );
        else if ( modes[ ind ] == GPIO_AIN )
            return gpioAn( ind );
        else
            return -1;
    }
    return -1;
}

static int gpioDig( int ind )
{
    GPIO_TypeDef * port;
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

// ADC_SAMPLE_1P5
// ADC_SAMPLE_7P5
// ADC_SAMPLE_13P5
// ADC_SAMPLE_28P5
// ADC_SAMPLE_41P5
// ADC_SAMPLE_55P5
// ADC_SAMPLE_71P5
// ADC_SAMPLE_239P5

// At 16MHz 3 signals would be measured with frequency 16000 / ( 28.5 * 3 ) = 187kHz.
// But ADC definitely shouldn't be faster then PWM.
#define ADC_SAMPLING  ADC_SAMPLE_7P5

static int adcSingle( uint32_t mask1, uint32_t mask2 );

static int gpioAn( int ind )
{
    int res;
    switch ( ind )
    {
        case 1:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN8 ) );
        break;

        case 2:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN5 ) );
        break;

        case 3:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN3 ) );
        break;

        case 5:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN7 ) );
        break;

        case 6:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN6 ) );
        break;

        case 7:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN4 ) );
        break;

        case 8:
            res = adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN2 ) );
        break;

        default:
            res = -1;
        break;
    }

    return res;
}

static int adcSingle( uint32_t mask1, uint32_t mask2 )
{

    const ADCConversionGroup adcMeasureCfg =
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        mask1, //ADC_SMPR2_SMP_AN8( ADC_SAMPLING ),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        mask2 //ADC_SQR3_SQ1_N( ADC_CHANNEL_IN8 )
    };

    adcsample_t adcRes;

    adcConvert( &ADCD1, &adcMeasureCfg, &adcRes, 1 );

    //adcStop( &ADCD1 );
    return adcRes;
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

    updateTimer();
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
    stopsCnt = PWM_CNT;
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
            // Merge
            stops[i].mask |= stops[j].mask;
            if ( stops[i].time == stops[j].time )
            {
                // Shift down
                int k;
                for ( k=j; k<lastStops-1; k++ )
                {
                    stops[j].mask = stops[j+1].mask;
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
static void turnOnByMask( int mask );
static void turnOffByMask( int mask );

static const GPTConfig gptCfg = 
{
  10000,    // 10kHz timer clock
  gptCb     // Timer callback
};

static void updateTimer( void )
{
    gptStopTimer( &TIMER );

    updateStops();

    if ( stopsCnt > 0 )
    {
        setMotoEn( 1 );
        stopInd = 0;
        turnOffByMask( stops[0].mask );
        gptStart( &TIMER,  &gptCfg );
        gptStartOneShot( &TIMER, stops[0].time );
    }
    else
    {
        if ( !motoActive() )
            setMotoEn( 0 );
    }
}

static void gptCb( GPTDriver * gptp )
{
    (void)gptp;

    int mask, t;
    // 1) If loop should be made.
    if ( stopInd == 0 )
    {
        t    = stops[0].time;
        chSysLockFromIsr();
            gptStartOneShotI( &TIMER, t );
        chSysUnlockFromIsr();

        mask = stops[0].mask;
        turnOnByMask( mask );
        stopInd = 1;
    }
    else if ( stopInd < stopsCnt )
    {
        // First of all calc and run next duration.
        t = stops[stopInd].time - stops[stopInd-1].time;
        chSysLockFromIsr();
            gptStartOneShotI( &TIMER, t );
        chSysUnlockFromIsr();

        mask = stops[stopInd].mask ^ stops[stopInd-1].mask;
        // Turn off all.
        turnOffByMask( mask );

        stopInd += 1;
    }
    else
    {
        // First of all calc and run next duration.
        t = period - stops[stopInd-1].time;
        chSysLockFromIsr();
            gptStartOneShotI( &TIMER, t );
        chSysUnlockFromIsr();

        turnOffByMask( stops[stopInd].mask );
        stopInd = 0;
    }
}

static void turnOnByMask( int mask )
{
    if ( mask & (1<<0) )
        palSetPad( GPIO_1_PORT, GPIO_1_PAD );
    if ( mask & (1<<1) )
        palSetPad( GPIO_2_PORT, GPIO_2_PAD );
    if ( mask & (1<<2) )
        palSetPad( GPIO_3_PORT, GPIO_3_PAD );
    if ( mask & (1<<3) )
        palSetPad( GPIO_4_PORT, GPIO_4_PAD );
    if ( mask & (1<<4) )
        palSetPad( GPIO_5_PORT, GPIO_5_PAD );
    if ( mask & (1<<5) )
        palSetPad( GPIO_6_PORT, GPIO_6_PAD );
    if ( mask & (1<<6) )
        palSetPad( GPIO_7_PORT, GPIO_7_PAD );
    if ( mask & (1<<7) )
        palSetPad( GPIO_8_PORT, GPIO_8_PAD );
    if ( mask & (1<<8) )
        palSetPad( GPIO_9_PORT, GPIO_9_PAD );
}

static void turnOffByMask( int mask )
{
    if ( mask & (1<<0) )
        palClearPad( GPIO_1_PORT, GPIO_1_PAD );
    if ( mask & (1<<1) )
        palClearPad( GPIO_2_PORT, GPIO_2_PAD );
    if ( mask & (1<<2) )
        palClearPad( GPIO_3_PORT, GPIO_3_PAD );
    if ( mask & (1<<3) )
        palClearPad( GPIO_4_PORT, GPIO_4_PAD );
    if ( mask & (1<<4) )
        palClearPad( GPIO_5_PORT, GPIO_5_PAD );
    if ( mask & (1<<5) )
        palClearPad( GPIO_6_PORT, GPIO_6_PAD );
    if ( mask & (1<<6) )
        palClearPad( GPIO_7_PORT, GPIO_7_PAD );
    if ( mask & (1<<7) )
        palClearPad( GPIO_8_PORT, GPIO_8_PAD );
    if ( mask & (1<<8) )
        palClearPad( GPIO_9_PORT, GPIO_9_PAD );
}

int gpioPwmActive( void )
{
    return stopsCnt ? 1 : 0;
}


