
#ifndef __CONV_CTRL_H_
#define __CONV_CTRL_H_

#include "ch.h"

void convInit( void );

void convStart( void );
void convStop( void );

void convSetBuck( int mv );
void convSetBoost( int mv );

void convSetMinBoostVolt( int vmin );
void convSetMaxBoostFill( int percentOverTen );

void convSetBoostCurr( int ma );
void convSetBuckCurr( int ma );

void convSetBuckGain( int val );
void convSetBoostGain( int val );

int adcTemp( void );
int adcBatteryVolt( void );
int adcBuckVolt( void );
int adcSolarVolt( void );
int adcBuckCurr( void );
int adcBoostCurr( void );



#endif




