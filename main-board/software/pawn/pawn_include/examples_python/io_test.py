
import sys
from time import sleep
from supplyctrlusb import *

class A:
    pwm = 0

    def __init__( self ):
        self.pwm = 0
	self.io = Supply()

    def setPwm( self, arg ):
        if ( arg < 0 ):
	    arg = 0;
	if ( arg > 255 ):
	    arg = 255
    	res = self.io.setIo( 0, arg )
	return res


a = A()
t = 0.1

for k in range( 5 ):
    for i in range( 50, 200, 10 ):
        a.setPwm( i )
        sleep( t )



