
#ifndef __HDW_CFG_H_
#define __HDW_CFG_H_

 
// *****************************************************************
//          Boost and Buck coverter parameters.
// *****************************************************************
#define PWM_CLOCK_FREQ     8000000  // 8MHz clock
#define PWM_PERIOD         40       // 200kHz
#define BOOST_MAX_PWM      7000

#define CONV_PORT          GPIOA
#define CONV_BOOST_PIN     1
#define CONV_BUCK_PIN      2

#define CONV_PWM           PWMD2
#define PWM_BOOST_CHAN     1
#define PWM_BUCK_CHAN      2

#define CONV_ADC_PORT      GPIOA
#define CONV_ADC_BOOST_VOLT_PIN    3
#define CONV_ADC_BUCK_VOLT_PIN     4
#define CONV_ADC_SOLAR_VOLT_PIN    5
#define CONV_ADC_BOOST_CURR_PIN    6
#define CONV_ADC_BUCK_CURR_PIN     7

#define CONV_ADC_PORT_TEMP         GPIOB
#define CONV_ADC_TEMP_PIN          0

#define ADC_NUM_CHANNELS   5
#define ADC_BUF_DEPTH      2

#define BOOST_VOLT_IND     0
#define BUCK_VOLT_IND      1
#define SOLAR_VOLT_IND     2
#define BOOST_CURR_IND     3
#define BUCK_CURR_IND      4

// Schematic constants used for convertion back and forth.
#define Vcc                3300  // Vcc voltage in millivolts
#define Rsense             200   // Sensor resistance 200mOhm
#define Ggain              5     // Current amplifier gain, here Ggain = ( 1 + R2 / R1), R2 = 30kOhm, R1 = 10kOhm
#define AMP_R1             10    // Voltage divider R below test point in kOhms
#define AMP_R2             68    // Voltage divider R above test point in kOhms

#define mV2Adc(mV)         ( (int)(mV) * AMP_R1 * 4095 / ( Vcc * (AMP_R1 + AMP_R2) ) )
#define Adc2mV(adc)        ( (int)(adc) * Vcc * (AMP_R1 + AMP_R2) / ( AMP_R1 * 4095 ) )

// I = ( Vcc * ((int)adc - 2047 ) * 1000) / (4095 * Ggain * Rsense)
// ( Vcc * ((int)adc - 2047 ) * 1000) = 4095 * I * Ggain * Rsense
// adc - 2047 = 4095 * I * Gain * Rsense / ( 1000 * Vcc );
// adc = 4095 * I * Gain * Rsense / ( 1000 * Vcc ) + 2047;
#define mA2Adc(mA)         ( (4095 * Ggain * Rsense * (int)(mA)) / ( 1000 * Vcc ) + 2047)
#define Adc2mA(adc)        ( ( Vcc * 1000 * ((int)(adc) - 2047 )) / (4095 * Ggain * Rsense) )

#define Adc2T(adc)         ( ( (Vcc * (int)(adc)) / 4095 - 500 ) )    // This converts Adc to T*10.




// *****************************************************************
//                        LED parameters.
// *****************************************************************
#define LED_PORT   GPIOB
#define LED1_PIN   13
#define LED2_PIN   14





// *****************************************************************
//                        Light parameters.
// *****************************************************************
#define LIGHT_PORT  GPIOB
#define LIGHT_PIN   5






// *****************************************************************
//                        Motor parameters.
// *****************************************************************
#define MOTO_EN_PIN    13
#define MOTO_EN_PORT   GPIOC

#define MOTO_1_PIN   9
#define MOTO_1_PORT  GPIOB
#define MOTO_2_PIN   8
#define MOTO_2_PORT  GPIOB
#define MOTO_3_PIN   15
#define MOTO_3_PORT  GPIOC
#define MOTO_4_PIN   14
#define MOTO_4_PORT  GPIOC


// *****************************************************************
//                        DFU location parameters.
// *****************************************************************
#define DFU_ADDRESS   ( 0x0801D800 )
#define TRIGGER_PORT  GPIOB
#define TRIGGER_PAD   15


// *****************************************************************
//                        Serial parameters.
// *****************************************************************
#define SERIAL_UART       SD1
#define SERIAL_BAUD       9600
#define SERIAL_TX_PAD     1
#define SERIAL_RX_PAD     2
#define SERIAL_BUF_SZ     32

// *****************************************************************
//                        I2C parameters.
// *****************************************************************
#define I2C_OUT_BUFFER_SZ       32
#define I2C_IN_BUFFER_SZ        16  // Command id as 1 byte and up to 2 two byte numbers = 5 bytes.
#define I2C_IO_BUFFER_SZ        32  // I2C master buffer size.
#define EXEC_QUEUE_SIZE         3
#define I2C_ADDRESS             1
#define I2C_TIMEOUT             500


#define I2C_CMD_VERSION          1
#define I2C_CMD_PAWN_SET_IO      2
#define I2C_CMD_PAWN_IO          3
#define I2C_CMD_PAWN_SET_MEM     4
#define I2C_CMD_PAWN_WRITE_FLASH 5
#define I2C_CMD_PAWN_RUN         6
#define I2C_CMD_PAWN_IS_RUNNING  7
#define I2C_CMD_PAWN_STOP        8
#define I2C_CMD_PAWN_RESULT      9
#define I2C_CMD_PAWN_ERROR       10

#define PORT_WAKEUP              GPIOB
#define PAD_WAKEUP               1


#define FIRMWARE_VERSION         1

#define PAWN_START_DELAY         5000
#define PAWN_START_STEP          250

#endif



