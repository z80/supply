
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




#endif



