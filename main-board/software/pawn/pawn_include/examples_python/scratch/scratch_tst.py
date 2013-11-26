#first.py
from scratra import *

@start
def whenstart(scratch):
  print 'Started!'

@broadcast('bbbbbb')
def hi( scratch ):
  print 'Hi, Scratch!'

@update( 'b' )
def update_b( scratch, value ):
    print 'b = ', value
    scratch.sensor[ "sss" ] = value + 8
    scratch.sensor[ "A" ] = value + 8
    
    
run( console=False )

