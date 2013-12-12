
#ifndef __PAWN_CTRL_H_
#define __PAWN_CTRL_H_

#include <ch.h>
#include <shell.h>

void     pawnInit( void );
void     pawnSetIo( int ind, uint8_t value );
uint8_t  pawnIo( int ind );
void     pawnSetMem( int at, uint8_t value );
//void     pawnSetMem( int at, int cnt );
uint8_t  pawnMem( int at );
uint16_t pawnWriteFlash( uint8_t page );
void     pawnRun( void );
uint8_t  pawnIsRunning( void );
void     pawnStop( void );
int      pawnResult( void );
int      pawnError( void );

// This functio is run only at main() and only to check whether
// it should run Pawn or not.
uint8_t  pawnDontRun( void );

#endif

