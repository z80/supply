#first.py
from scratch.scratra import *
# Alternatively either USB module or I2C module.
import supplyctrlusb
#import supplyctrli2c

io = supplyctrlusb.Supply()

def setCamPos( x ):
    global io
    if not io:
        io = supplyctrlusb.Supply()
    if ( x < 0 ):
        x = 0
    elif ( x > 255 ):
        x = 255
        
    res = io.setIo( 0, x )
    return 0

@start
def whenstart(scratch):
  print 'Started!'

@broadcast('bbbbbb')
def hi( scratch ):
  print 'Hi, Scratch!'

@update( 'servo7' )
def update_b( scratch, value ):
    print 'servo7 = ', value
    setCamPos( value )
    
    
run( console=False )

