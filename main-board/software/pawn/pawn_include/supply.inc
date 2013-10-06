

#if !defined __SUPPLY_INC_
#define __SUPPLY_INC_


native trigger() = -1;

native setRtc( sec, msec ) = -2;
native rtc( &msec ) = -3;
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
native setMoto( mask ) = -16;

native convSetBuck( mv ) = -17;
native convSetBoost( mv ) = -18;
native convSetMinBoostVolt( mv ) = -19;
native convSetMaxBoostFill( percentOverTen ) = -20;
native convSetBoostCurr( ma ) = -21;
native convSetBuckCurr( ma ) = -22;
native convSetBuckGain( percentOverTen ) = -23;
native convSetBoostGain( percentOverTen ) = -24;

native adcTemp() = -25;
native adcBatteryVolt() = -26;
native adcBuckVolt() = -27;
native adcSolarVolt() = -28;
native adcBuckCurr() = -29;
native adcBoostCurr() = -30;

#endif



