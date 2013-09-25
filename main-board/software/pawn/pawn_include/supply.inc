

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
native usbWrite( stri[] ) = -11;

native io( at ) = -12;
native setIo( at, value ) = -13;

native setLed( mask ) = -14;
native setMoto( mask ) = -15;

native convSetBuck( mv ) = -16;
native convSetBoost( mv ) = -17;
native convSetMinBoostVolt( mv ) = -18;
native convSetMaxBoostFill( percentOverTen ) = -19;
native convSetBoostCurr( ma ) = -20;
native convSetBuckCurr( ma ) = -21;
native convSetBuckGain( percentOverTen ) = -22;
native convSetBoostGain( percentOverTen ) = -23;

native adcTemp() = -24;
native adcBatteryVolt() = -25;
native adcBuckVolt() = -26;
native adcSolarVolt() = -27;
native adcBuckCurr() = -28;
native adcBoostCurr() = -29;





