
#from supplyctrlusb import *

class CurrentCtrl:
    def __init__( self ):
#        self.io = Supply()
        pass
        
    def setVi( self, v=0, i=0 ):
#        self.io.setIo( 1, v >> 8 )
#        self.io.setIo( 2, v & 255 )
#        self.io.setIo( 3, i >> 8 )
#        self.io.setIo( 4, i & 255 )
#        self.io.setIo( 0, 1 )
        pass
        
    def vi( self ):
#        v = ( self.io.io( 5 ) << 8 ) \\
#        self.io.io( 6 )
#        i = ( self.io.io( 7 ) << 8 ) \\
#        self.io.io( 8 )
        v = 345
        i = 432
        return (v, i)

