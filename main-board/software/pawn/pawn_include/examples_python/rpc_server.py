#!/bin/python

import xmlrpclib
from SimpleXMLRPCServer import SimpleXMLRPCServer

# Alternatively either USB module or I2C module.
import supplyctrlusb
#import supplyctrli2c

io = supplyctrlusb.Supply()

def setCamPos( x, y ):
    global io
    if not io:
        io = supplyctrlusb.Supply()
    if ( x < 0 ):
        x = 0
    elif ( x > 255 ):
        x = 255
    
    if ( y < 0 ):
        y = 0
    elif ( y > 255 ):
        y = 255
        
    res = io.setIo( 0, x )
    if not res:
        return 1
    res = io.setIo( 1, y )
    if ( not res ):
        return 2
    return 0
    
server = SimpleXMLRPCServer( ( "localhost", 8765 ) )
print "Expecting commands"
server.register_function( setCamPos, "setCamPos" )
server.serve_forever()


    

