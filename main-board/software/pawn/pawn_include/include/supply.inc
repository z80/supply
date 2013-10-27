

#if !defined __SUPPLY_INC_
#define __SUPPLY_INC_


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
native setWakeup( arg ) = -11;
native usbWrite( stri[] ) = -12;

native io( at ) = -13;
native setIo( at, value ) = -14;

native setLed( mask ) = -15;
native setLight( en ) = -16;
native setMoto( mask ) = -17;

native convSetBuck( mv ) = -18;
native convSetBoost( mv ) = -19;
native convSetMinBoostVolt( mv ) = -20;
native convSetMaxBoostFill( percentOverTen ) = -21;
native convSetBoostCurr( ma ) = -22;
native convSetBuckCurr( ma ) = -23;
native convSetBuckGain( percentOverTen ) = -24;
native convSetBoostGain( percentOverTen ) = -25;

native adcTemp() = -26;
native adcBatteryVolt() = -27;
native adcBuckVolt() = -28;
native adcSolarVolt() = -29;
native adcBuckCurr() = -30;
native adcBoostCurr() = -31;

#endif



