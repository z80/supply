#!/bin/python

import xmlrpclib
from SimpleXMLRPCServer import SimpleXMLRPCServer

# Alternatively either USB module or I2C module.
#~ import supplyctrlusb
#import supplyctrli2c
import supplyctrlusb

io = supplyctrlusb.Supply()

def setMoto( v1, v2, v3, v4 ):
    print "setMoto", v1, v2, v3, v4
    v = 0
    if ( v1 ):
        v += 1
    if ( v2 ):
        v += 2
    if ( v3 ):
        v += 4
    if ( v4 ):
        v += 8
    io.setIo( 1, v )
    io.setIo( 0, 1 )
    return 0
    
def setLight( en ):
    print "setLight", en
    v = 0
    if ( en ):
        v = 1
    io.setIo( 2, v )
    io.setIo( 0, 1 )
    return 0

def setCamPos( x, y ):
    print "setCamPos", x, y
    if ( x < 0 ):
        x = 0
    elif ( x > 255 ):
        x = 255
    
    if ( y < 0 ):
        y = 0
    elif ( y > 255 ):
        y = 255
        
    res = io.setIo( 3, x )
    #if not res:
    #    return 1
    res = io.setIo( 4, y )
    #if ( not res ):
    #    return 2
    io.setIo( 0, 1 )
    return 0
    
server = SimpleXMLRPCServer( ( "localhost", 8765 ) )
print "Expecting commands"
server.register_function( setMoto,   "setMoto" )
server.register_function( setLight,  "setLight" )
server.register_function( setCamPos, "setCamPos" )
server.serve_forever()

