
#ifndef __MOTO_CTRL_H_
#define __MOTO_CTRL_H_

#include "ch.h"
#include "shell.h"

void initMoto( void );
void setMoto( int en );


int  trigger( void );
void setAddonTrigger( int arg );
void setAddonEn( int arg );
void setRpiEn( int arg );


// This one is for internal use only and called automatically.
void setMotoEn( int en );
// To check if moto should be disabled from the outside.
int motoActive( void );



#endif



