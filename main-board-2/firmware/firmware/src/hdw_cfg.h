
#ifndef __HDW_CFG_H_
#define __HDW_CFG_H_

// *****************************************************************
//                        Power pads.
// *****************************************************************
#define ADDON_PWR_PAD   13
#define ADDON_PWR_PORT  GPIOB

#define RPI_PWR_PAD     5
#define RPI_PWR_PORT    GPIOB


 
// *****************************************************************
//          Boost and Buck coverter parameters.
// *****************************************************************
#define PWM_CLOCK_FREQ     8000000  // 8MHz clock
#define PWM_PERIOD         40       // 200kHz
#define BOOST_MAX_PWM      7000




// *****************************************************************
//                        LED parameters.
// *****************************************************************
#define LED_PORT   GPIOB
#define LED1_PIN   9
#define LED2_PIN   8






// *****************************************************************
//                        Motor parameters.
// *****************************************************************
#define MOTO_EN_PIN    13
#define MOTO_EN_PORT   GPIOC

#define MOTO_1_PIN   1
#define MOTO_1_PORT  GPIOA
#define MOTO_2_PIN   0
#define MOTO_2_PORT  GPIOA
#define MOTO_3_PIN   14
#define MOTO_3_PORT  GPIOC
#define MOTO_4_PIN   15
#define MOTO_4_PORT  GPIOC


// *****************************************************************
//                        Trigger button
// *****************************************************************

#define TRIGGER_PAD   8
#define TRIGGER_PORT  GPIOA


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

#define ADDON_TRIGGER_PAD        1
#define ADDON_TRIGGER_PORT       GPIOB


#define FIRMWARE_VERSION         1

#define PAWN_START_DELAY         5000
#define PAWN_START_STEP          250

#endif



