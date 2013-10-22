#!/usr/bin/python

import sys
from time import sleep
from supplyctrlusb import *

class A:
    pwm = 0

    def __init__( self ):
        self.pwm = 0
	self.io = Supply()

    def read( self ):
    	inp = self.io.io( 0 )
	adc = self.io.io( 1 ) + self.io.io( 2 ) * 255
	print "inp = " + str(inp) + ", adc = ", str(adc)


a = A()
t = 1

while 1:
	a.read()


