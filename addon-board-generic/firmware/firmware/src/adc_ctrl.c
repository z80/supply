
#include "adc_ctrl.h"
#include "hal.h"
#include "hdw_cfg.h"

void initAdc( void )
{
    palSetPadMode( PORT_ADC, PAD_ADC_1, PAL_MODE_INPUT_ANALOG );
    palSetPadMode( PORT_ADC, PAD_ADC_2, PAL_MODE_INPUT_ANALOG );
    palSetPadMode( PORT_ADC, PAD_ADC_3, PAL_MODE_INPUT_ANALOG );
    palSetPadMode( PORT_ADC, PAD_ADC_4, PAL_MODE_INPUT_ANALOG );
    palSetPadMode( PORT_ADC, PAD_ADC_5, PAL_MODE_INPUT_ANALOG );
    palSetPadMode( PORT_ADC, PAD_ADC_6, PAL_MODE_INPUT_ANALOG );
    palSetPadMode( PORT_ADC, PAD_ADC_7, PAL_MODE_INPUT_ANALOG );

    adcStart( &ADCD1, NULL );
}

void finitAdc( void )
{
    adcStop( &ADCD1 );
}

static int adcSingle( uint32_t mask1, uint32_t mask2 );

// ADC_SAMPLE_1P5
// ADC_SAMPLE_7P5
// ADC_SAMPLE_13P5
// ADC_SAMPLE_28P5
// ADC_SAMPLE_41P5
// ADC_SAMPLE_55P5
// ADC_SAMPLE_71P5
// ADC_SAMPLE_239P5

#define ADC_SAMPLING ADC_SAMPLE_28P5

int  measureAdc( int index )
{
	int res;
	switch ( index )
	{
	case 1:
		res = adcSingle( ADC_SMPR2_SMP_AN2( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN2 ) );
	case 2:
		res = adcSingle( ADC_SMPR2_SMP_AN3( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN3 ) );
	case 3:
		res = adcSingle( ADC_SMPR2_SMP_AN4( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN4 ) );
	case 4:
		res = adcSingle( ADC_SMPR2_SMP_AN5( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN5 ) );
	case 5:
		res = adcSingle( ADC_SMPR2_SMP_AN6( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN6 ) );
	case 6:
		res = adcSingle( ADC_SMPR2_SMP_AN7( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN7 ) );
	default:
		res = adcSingle( ADC_SMPR2_SMP_AN1( ADC_SAMPLING ), ADC_SQR3_SQ1_N( ADC_CHANNEL_IN1 ) );
	}
	return res;
}

// At 16MHz 3 signals would be measured with frequency 16000 / ( 28.5 * 3 ) = 187kHz.
// But ADC definitely shouldn't be faster then PWM.
#define ADC_SAMPLING  ADC_SAMPLE_28P5

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
    return adcRes;
}





