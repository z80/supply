

#include "conv_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"

static uint8_t convRunning = 0;

static int buckPwm   = 0;
static int buckGain  = 1000; // Gain is 10%
static int buckVolt  = 0;
static int buckCurr  = 65535;

static int boostMaxPwm = BOOST_MAX_PWM;
static int boostPwm    = 0;
static int boostVolt   = 0;
static int boostCurr   = 65535;
static int boostGain   = 100; // Gain is 1%

// Was 4.9V but with diode decreased on voltage drop on diode which is 0.65V.
// So now solar setpoint is 4.2V.
static int solarVolt  = 0;
//static int buckVoltSave = 0;


static Mutex mutex;

static void convStart( void );
static void convStop( void );

static void convAdcReadyCb( ADCDriver * adcp, adcsample_t * buffer, size_t n )
{
    (void)adcp;
    //(void)buffer;
    (void)n;
    // Buck
    if ( buffer[ BUCK_CURR_IND ] > buckCurr )
    {
        buckPwm -= buckGain;
	if ( buckPwm < 0 )
	    buckPwm = 0;
	pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
    }
    else
    {
        if ( buffer[ BUCK_VOLT_IND ] < buckVolt )
        {
    	    buckPwm += buckGain;
	    if ( buckPwm > 10000 )
    	        buckPwm = 10000;
            pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
        }
        else if ( buffer[ BUCK_VOLT_IND ] > buckVolt )
        {
    	    buckPwm -= buckGain;
	    if ( buckPwm < 0 )
	        buckPwm = 0;
    	    pwmEnableChannelI(&CONV_PWM, PWM_BUCK_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, buckPwm ) );
        }
    }
    // Boost
    if ( buffer[ BOOST_CURR_IND ] > boostCurr )
    {
        boostPwm -= boostGain;
        if ( boostPwm < 0 )
	    boostPwm = 0;
        pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
    }
    else
    {
        if ( buffer[ SOLAR_VOLT_IND ] >= solarVolt )
        {
            if ( buffer[ BOOST_VOLT_IND ] < boostVolt )
            {
                boostPwm += boostGain;
                if ( boostPwm > boostMaxPwm )
                    boostPwm = boostMaxPwm;
                pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
            }
            else if ( buffer[ BOOST_VOLT_IND ] > boostVolt )
            {
                boostPwm -= boostGain;
                if ( boostPwm < 0 )
                    boostPwm = 0;
                pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, boostPwm ) );
            }
        }
        else
        {
            boostPwm = 0;
    	    pwmEnableChannelI(&CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0 ) );
        }
    }
}

static adcsample_t adcSamples[ ADC_NUM_CHANNELS * ADC_BUF_DEPTH ];

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
#define ADC_SAMPLING  ADC_SAMPLE_28P5

static const ADCConversionGroup adcGroup =
{
    TRUE,
    ADC_NUM_CHANNELS,
    convAdcReadyCb,
    NULL,
    0, 0,           /* CR1, CR2 */
    0,
    ADC_SMPR2_SMP_AN3( ADC_SAMPLING ) |
    ADC_SMPR2_SMP_AN4( ADC_SAMPLING ) |
    ADC_SMPR2_SMP_AN5( ADC_SAMPLING ) | 
    ADC_SMPR2_SMP_AN6( ADC_SAMPLING ) | 
    ADC_SMPR2_SMP_AN7( ADC_SAMPLING ),
    ADC_SQR1_NUM_CH( ADC_NUM_CHANNELS ),
    0,
    ADC_SQR3_SQ1_N( ADC_CHANNEL_IN3 ) | 
    ADC_SQR3_SQ2_N( ADC_CHANNEL_IN4 ) | 
    ADC_SQR3_SQ3_N( ADC_CHANNEL_IN5 ) | 
    ADC_SQR3_SQ4_N( ADC_CHANNEL_IN6 ) | 
    ADC_SQR3_SQ5_N( ADC_CHANNEL_IN7 )
};

static PWMConfig pwmCfg =
{
    PWM_CLOCK_FREQ, // 1000kHz PWM clock frequency.
    PWM_PERIOD,     // Initial PWM period 10us.
    NULL,
    {
        { PWM_OUTPUT_DISABLED, NULL },
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_ACTIVE_HIGH, NULL },
        { PWM_OUTPUT_DISABLED, NULL }
    },
    0,
#if STM32_PWM_USE_ADVANCED
    0
#endif
};


static void convRunStop( void )
{
    if ( convRunning )
    {
        if ( ( buckVolt <= 0 ) && ( boostVolt <= 0 ) )
	    convStop();

    }
    else
    {
        if ( ( buckVolt >= 0 ) || ( boostVolt >= 0 ) )
	    convStart();
    }
}

void initConv( void )
{
    chMtxInit( &mutex );

    // Init PWM pins.
    palSetPadMode( CONV_PORT, CONV_BUCK_PIN,  PAL_MODE_STM32_ALTERNATE_PUSHPULL );
    palSetPadMode( CONV_PORT, CONV_BOOST_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL );

    // Init ADC pins.
    palSetGroupMode( CONV_ADC_PORT, PAL_PORT_BIT( CONV_ADC_BUCK_VOLT_PIN )  | 
    	                            PAL_PORT_BIT( CONV_ADC_BOOST_VOLT_PIN ) | 
    	                            PAL_PORT_BIT( CONV_ADC_SOLAR_VOLT_PIN ) | 
    	                            PAL_PORT_BIT( CONV_ADC_BOOST_CURR_PIN ) | 
				                    PAL_PORT_BIT( CONV_ADC_BUCK_CURR_PIN ),
                                    0, PAL_MODE_INPUT_ANALOG );

    palSetGroupMode( CONV_ADC_PORT_TEMP, PAL_PORT_BIT( CONV_ADC_TEMP_PIN ),
                                    0, PAL_MODE_INPUT_ANALOG );
}

static void convStart( void )
{
    chMtxLock( &mutex );
        // Start PWM peripherial.
        pwmStart( &CONV_PWM, &pwmCfg );
        // Set zero active period.
        pwmEnableChannel( &CONV_PWM, PWM_BOOST_CHAN, PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0000 ) );
        pwmEnableChannel( &CONV_PWM, PWM_BUCK_CHAN,  PWM_PERCENTAGE_TO_WIDTH( &CONV_PWM, 0000 ) );

        // Init ADC.
        adcStart( &ADCD1, NULL );
        adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );

        convRunning = 1;
    chMtxUnlock();
}

static void convStop( void )
{
    chMtxLock( &mutex );
        pwmStop( &CONV_PWM );
        adcStopConversion( &ADCD1 );
        adcStop( &ADCD1 );

        convRunning = 0;
    chMtxUnlock();
}

void convSetBuck( int mv )
{
    chSysLock();
        buckVolt = mV2Adc( mv );
    chSysUnlock();

    convRunStop();
}

void convSetBoost( int mv )
{
    chSysLock();
        boostVolt = mV2Adc( mv );
    chSysUnlock();

    convRunStop();
}

void convSetMinBoostVolt( int vmin )
{
    chSysLock();
        solarVolt = mV2Adc( vmin );
    chSysUnlock();
}

void convSetMaxBoostFill( int percentOverTen )
{
    chSysLock();
        boostMaxPwm = percentOverTen;
    chSysUnlock();
}

void convSetBoostCurr( int ma )
{
    chSysLock();
        boostCurr = mA2Adc( ma );
    chSysUnlock();
}

void convSetBuckCurr( int ma )
{
    chSysLock();
        buckCurr = mA2Adc( ma );
    chSysUnlock();
}

void convSetBuckGain( int val )
{
    chSysLock();
        buckGain = val;
    chSysUnlock();
}

void convSetBoostGain( int val )
{
    chSysLock();
        boostGain = val;
    chSysUnlock();
}

static int adcSingle( uint32_t mask1, uint32_t mask2 )
{
    chMtxLock( &mutex );
        uint8_t en = convRunning;
    chMtxUnlock();
    if ( !en )
        adcStart( &ADCD1, NULL );
    else
        adcStopConversion( &ADCD1 );

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
    if ( en )
        adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
    else
        adcStop( &ADCD1 );
    return Adc2T( adcRes );
}

int adcTemp( void )
{
    return adcSingle( ADC_SMPR2_SMP_AN8( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN8 ) );
}

int adcBatteryVolt( void )
{
	return adcSingle( ADC_SMPR2_SMP_AN3( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN3 ) );
}

int adcBuckVolt( void )
{
	return adcSingle( ADC_SMPR2_SMP_AN4( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN4 ) );
}

int adcSolarVolt( void )
{
	return adcSingle( ADC_SMPR2_SMP_AN5( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN5 ) );
}

int adcBuckCurr( void )
{
	return adcSingle( ADC_SMPR2_SMP_AN7( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN7 ) );
}


int adcBoostCurr( void )
{
	return adcSingle( ADC_SMPR2_SMP_AN6( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN6 ) );
}













/*
static const ADCConversionGroup grpCurrent =
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        ADC_SMPR2_SMP_AN6( ADC_SAMPLING ),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        ADC_SQR3_SQ1_N( ADC_CHANNEL_IN6 )
    };

static const ADCConversionGroup grpTemperature =
    {
        FALSE,
        1,
        NULL,
        NULL,
        0, 0,
        0,
        ADC_SMPR2_SMP_AN7( ADC_SAMPLING ),
        ADC_SQR1_NUM_CH( 1 ),
        0,
        ADC_SQR3_SQ1_N( ADC_CHANNEL_IN7 )
    };

static adcsample_t valCurrect,
                   valTemperature;


uint16_t adcCurrent( void )
{
    uint8_t en =  ( ADCD1.state != ADC_STOP ) ? 1 : 0;
    if ( !en )
        adcStart( &ADCD1, NULL );
    else
        adcStopConversion( &ADCD1 );
    adcConvert( &ADCD1, &grpCurrent, &valCurrect, 1 );
    if ( en )
        adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
    else
        adcStop( &ADCD1 );
    return (uint16_t)valCurrect;
}

uint16_t adcTemperature( void )
{
    uint8_t en =  ( ADCD1.state != ADC_STOP ) ? 1 : 0;
    if ( !en )
        adcStart( &ADCD1, NULL );
    else
        adcStopConversion( &ADCD1 );
    adcConvert( &ADCD1, &grpTemperature, &valTemperature, 1 );
    if ( en )
        adcStartConversion( &ADCD1, &adcGroup, adcSamples, ADC_BUF_DEPTH );
    else
        adcStop( &ADCD1 );
    return (uint16_t)valTemperature;
}

uint16_t adcBoostFb( void )
{
    chSysLock();
        uint16_t res = adcSamples[BOOST_IND];
    chSysUnlock();
    return res;
}

uint16_t adcBuckFb( void )
{
    chSysLock();
        uint16_t res = adcSamples[BUCK_IND];
    chSysUnlock();
    return res;
}

uint16_t adcSolarFb( void )
{
    chSysLock();
        uint16_t res = adcSamples[SOLAR_IND];
    chSysUnlock();
    return res;
}
*/







