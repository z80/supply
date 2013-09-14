
#ifndef __HDW_CFG_H_
#define __HDW_CFG_H_

 
// *****************************************************************
//          Boost and Buck coverter parameters.
// *****************************************************************
#define PWM_CLOCK_FREQ     8000000  // 8MHz clock
#define PWM_PERIOD         40       // 200kHz
#define BOOST_MAX_FILL_DEF 7000

#define CONV_PORT          GPIOA
#define CONV_BOOST_PIN     1
#define CONV_BUCK_PIN      2

#define CONV_PWM           PWMD2
#define PWM_BOOST_CHAN     1
#define PWM_BUCK_CHAN      2

#define CONV_ADC_PORT      GPIOA
 #define CONV_ADC_BATT_VOLT     3
#define CONV_ADC_BUCK_VOLT     4
#define CONV_ADC_SOLAR_VOLT    5
#define CONV_ADC_BOOST_CURR    6
#define CONV_ADC_BUCK_CURR     7
#define CONV_ADC_BOOST_CURR    8

#define CONV_ADC_PORT_TEMP     GPIOB
#define CONV_ADC_TEMPERATURE   0

#define ADC_NUM_CHANNELS   6
#define ADC_BUF_DEPTH      2
#define SOLAR_IND          0
#define BOOST_IND          1
#define BUCK_IND           2

#define mV2Adc(mV)         ( (int)mV * 10 * 4095 / ( 3300 * 78 ) )
#define Adc2mV(adc)        ( (int)adc * 3300 * 78 / ( 10 * 4095 ) )








#define LED_CMD       "led"
#define LED_PIN       11
#define LED_PORT      GPIOB

#define PWR_RST_CMD   "pwrrst"
#define PWR_CFG_CMD   "pwrcfg"
#define PWR_PIN       10
#define PWR_PORT      GPIOB

#define MOTO_RST_CMD   "motorst"
#define MOTO_CFG_CMD   "motocfg"
#define MOTO_SET_CMD   "motoset"
#define MOTO_EN_PIN    2
#define MOTO_EN_PORT   GPIOB

#define MOTO_1_PIN   1
#define MOTO_1_PORT  GPIOB
#define MOTO_2_PIN   0
#define MOTO_2_PORT  GPIOB
#define MOTO_3_PIN   7
#define MOTO_3_PORT  GPIOA
#define MOTO_4_PIN   6
#define MOTO_4_PORT  GPIOA

#define ADC_CFG_CMD  "adccfg"
#define ADC_CMD      "adc"
#define ADC_SOL_PORT GPIOA
#define ADC_SOL_PIN  3
#define ADC_BAT_PORT GPIOA
#define ADC_BAT_PIN  2


#endif



