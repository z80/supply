

#if !defined __MAIN2_INC_
#define __MAIN2_INC_


native trigger() = -1;

native setRtc( msec ) = -2;
native rtc() = -3;
native msleep( ms ) = -4;

native setSerialEn( en, baud ) = -5;
native serialSend( data[], cnt = sizeof data ) = -6;
native serialReceive( data[], maxCnt = sizeof data ) = -7;

native setI2cSlaveEn( en = 1, addr = 1 ) = -8;

native setI2cEn( en = 1 ) = -9;
native i2cIo( addr, dataSend[], sendCnt = sizeof dataSend, dataReceive[], receiveCnt = sizeof dataReceive, timeoutMs = 1000 ) = -10;
native setAddTrigger( arg ) = -11;
native setAddEn( en ) = -12;
native setRpiEn( en ) = -13;

native usbSetEn( en ) = -14;
native usbWrite( stri[] ) = -15;

native io( at ) = -16;
native setIo( at, value ) = -17;

native setLed( mask ) = -18;
native setMoto( mask ) = -19;

native gpioSetMode( mask, mode ) = -20;
native gpios( mask ) = -21;
native gpio( ind ) = -22;
native gpioSetPeriod( us ) = -23;
native gpioSetPwm( mask, us ) = -24;

#endif



