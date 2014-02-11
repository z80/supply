
from supplyctrlusb import *

class CurrentCtrl:
    def __init__( self ):
        self.io = Supply()
        
    def setVi( self, v, i ):
        print "sending {0}, {1}".format( v, i )
        self.io.setIo( 0, v >> 8 )
        self.io.setIo( 1, v & 255 )
        self.io.setIo( 2, i >> 8 )
        self.io.setIo( 3, i & 255 )
        
    def vi( self ):
        v = ( self.io.io( 4 ) << 8 ) + self.io.io( 5 )
        if ( v & 0x8000 ):
            v = v - 65536
        i = ( self.io.io( 6 ) << 8 ) + self.io.io( 7 )
        if ( i & 0x8000 ):
            i = i - 65536
        return (v, i)

