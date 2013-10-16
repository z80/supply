
import sys
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

    def setByArgv( self, argv ):
        if ( len( argv ) > 1 ):
	    val = int( argv[1] )
	    res = self.setPwm( val )
	    print "Result is: " + str( res )
	else:
	    print "ERROR: Not valid command line."

#print "\n".join( [sys.argv] )

a = A()
a.setByArgv( sys.argv )


