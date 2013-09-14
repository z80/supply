
#ifndef __CONV_CTRL_H_
#define __CONV_CTRL_H_

#include "ch.h"

void convStart( void );
void convStop( void );

void convSetBoostEn( uint8_t en )
void convSetBuckEn( uint8_t en );

void convSetBuck( int mv );
void convSetBoost( int mv );

void convSetMinBoostVolt( int vmin );
void convSetMaxBoostFill( int percentOverTen );

void convSetMaxBoostCurr( int ma );
void convSetMaxBuckCurr( int ma );

void convSetBuckGain( int val );
void convSetBoostGain( int val );

int adcCurrent( void );
int adcTemperature( void );
int adcBatteryVolt( void );
int adcBuckVolt( void );
int adcSolarVolt( void );




#endif




