
#ifndef __HDW_CFG_H_
#define __HDW_CFG_H_

// *****************************************************************
//          74HC165 control pins.
// *****************************************************************
#define PAD_IN_LOAD    13
#define PORT_IN_LOAD   GPIOB

#define PAD_IN_SCL_EN  12
#define PORT_IN_SCL_EN GPIOB

#define PAD_IN_SCL     11
#define PORT_IN_SCL    GPIOB

#define PAD_IN_SDA     10
#define PORT_IN_SDA    GPIOB

#define DELAY_165      100


// *****************************************************************
//          74HC595 control pins.
// *****************************************************************
#define PAD_DS         8
#define PORT_DS        GPIOA

#define PAD_OE         9
#define PORT_OE        GPIOA

#define PAD_STCP       10
#define PORT_STCP      GPIOA

#define PAD_SHCP       11
#define PORT_SHCP      GPIOA

#define PAD_MR         12
#define PORT_MR        GPIOA

#define DELAY_595      100

#define LED_1          (1<<0)
#define LED_2          (1<<1)
#define MOTO_EN_1      (1<<2)
#define MOTO_EN_2      (1<<3)
#define MOTO_1         (1<<4)
#define MOTO_2         (1<<5)
#define MOTO_3         (1<<6)
#define MOTO_4         (1<<7)
#define MOTO_5         (1<<8)
#define MOTO_6         (1<<9)
#define MOTO_7         (1<<10)
#define MOTO_8         (1<<11)
#define SERVO_EN       (1<<12)


// *****************************************************************
//          ADC control pins.
// *****************************************************************
#define PORT_ADC       GPIOA
#define PIN_ADC_1      1
#define PIN_ADC_2      2
#define PIN_ADC_3      3
#define PIN_ADC_4      4
#define PIN_ADC_5      5
#define PIN_ADC_6      6
#define PIN_ADC_7      7


// *****************************************************************
//          PWM control pins.
// *****************************************************************
#define PORT_PWM_1    GPIOB
#define PAD_PWM_1     3

#define PORT_PWM_2    GPIOB
#define PAD_PWM_2     4

#define PORT_PWM_3    GPIOB
#define PAD_PWM_3     5

#define PORT_PWM_4   GPIOB
#define PAD_PWM_4    8

#define PORT_PWM_5   GPIOB
#define PAD_PWM_5    9

#define PORT_PWM_6  GPIOB
#define PAD_PWM_6   1

#define PORT_PWM_7  GPIOB
#define PAD_PWM_7   0

#define PORT_PWM_8  GPIOA
#define PAD_PWM_8   0


// *****************************************************************
//          Firmware version.
// *****************************************************************

#define FIRMWARE_VERSION         1

#endif



