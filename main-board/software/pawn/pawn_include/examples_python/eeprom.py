#!/bin/python

import xmlrpclib
from Tkinter import *
from time import sleep
from supplyctrlusb import *

# Data obtained with pages count 580
# 16 32 3 255 <183> 254 <122 0   63>  255 <183> 254 51 16 32 3 0 0 0 0 0 0 0 0 0 0 0 8 37 15 232 16 0 0 0 0 0 0 0 0 16 0 0 0 0 0 0 0 0 0 0 28 133 101 101 0 160 0 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
# Data obtained with pages count 581
# 16 32 3 255 <151> 254 <138 255 201> 255 <151> 254 51 16 32 3 0 0 0 0 0 0 0 0 0 0 0 8 37 15 232 16 0 0 0 0 0 0 0 0 16 0 0 0 0 0 0 0 0 0 0 28 133 101 101 0 160 0 7 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
# After zerowing attempt.
# 16 32 3 255 124 254 35 255 189 255 124 254 51 16 32 3 0 0 0 0 0 0 0 0 0 0 0 8 37 15 232 16 

class Application(Frame):
    
    DELAY = 0.1
    TRIES = 50
    FRAME = 4
    
    def read( self, i2cAddr, devAddr, cnt ):
        print "read " + str(i2cAddr) + ", " + str(devAddr) + ", " + str(cnt)
        io = self.io
        io.setIo( 1, i2cAddr )
        io.setIo( 2, devAddr )
        io.setIo( 3, cnt )
        # Start reading data
        pp = io.io( 0 )
        print "pp = " + str( pp )
        io.setIo( 0, 1 )
        # Waiting for completion
        for t in range( self.TRIES ):
            finished = io.io( 0 )
            print "finished = " + str( finished)
            if ( finished == 0 ):
                res = io.io( 1 )
                print "res = " + str( res )
                if res != 0:
                    return (res, [])
                d = []
                for i in range(cnt):
                    v = io.io( 2+i )
                    d.append( v )
                print "data", d
                return ( res, d )
            sleep( self.DELAY )
        print "Read timeout"
            
    def write( self, i2cAddr, devAddr, data ):
        io = self.io
        io.setIo( 1, i2cAddr )
        io.setIo( 2, devAddr )
        cnt = len( data )
        print "write " + str(i2cAddr) + ", " + str(devAddr) + ", " + str(cnt)
        io.setIo( 3, cnt )
        for i in range( cnt ):
            io.setIo( 4+i, data[i] )
        # Start writing data.
        io.setIo( 0, 2 )
        # Waiting for completion
        for t in range( self.TRIES ):
            finished = io.io( 0 )
            print "finished = " + str( finished)
            if ( finished == 0 ):
                res = io.io( 1 )
                print "res = " + str( res )
                return res
            sleep( self.DELAY )
        print "Write timeout"
        
    def readI2c( self ):
        # Clear output
        self.text.delete( 1.0, END )

        i2cAddr = int( self.i2cAddr.get(), 2 ) # Binary number
        print "i2cAddr = " + str( i2cAddr )
        devAddr = int( self.devAddr.get() )
        print "devAddr = " + str( devAddr )
        cnt = int( self.bytesCnt.get() )
        print "bytesCnt = " + str( cnt )
        
        # Return before real device interaction.
        #~ return
        
        for i in range( 0, cnt, self.FRAME ):
            res, data = self.read( i2cAddr, devAddr+i, self.FRAME )
            if res > 0:
                print "res = " + str( res )
                return
            for k in range( len( data ) ):
                self.text.insert( END, str( data[k] ) + " " )
        
    def writeI2c( self ):
        i2cAddr = int( self.i2cAddr.get(), 2 ) # Binary number
        print "i2cAddr = " + str( i2cAddr )
        devAddr = int( self.devAddr.get() )
        print "devAddr = " + str( devAddr )
        cnt = int( self.bytesCnt.get() )
        print "bytesCnt = " + str( cnt )
        
        data = self.text.get( 1.0, END )
        print "data = ", data
        d = data.split()
        print "data = ", d
        data = []
        for i in range( len(d) ):
            data.append( int(d[i]) )
        print "data = ", data
        
        # Return before executing critical changes.
        #~ return

        for i in range( 0, cnt, self.FRAME ):
            d = []
            for k in range( self.FRAME ):
                d.append( data[i+k] )
            res = self.write( i2cAddr, devAddr+i, d )
            if res > 0:
                print "res = " + str( res )
                return
            print "Ready"
        
    def toString( self ):
        stri = self.text.get( 1.0, END )
        d = stri.split()
        stri = ""
        cnt = len( d )
        print "Characters cnt = " + str( cnt )
        for i in range( cnt ):
            ch = chr( int( d[i] ) )
            print "ch[" + str( i ) + "] = " + str( ch )
            stri += ch
        print stri

    def createWidgets(self):
        self.lblI2cAddr = Label( self, text='I2C addr:' )
        self.lblI2cAddr.grid( row=0, column=0, rowspan=1, columnspan=1 )
        
        self.i2cAddr = Entry( self )
        self.i2cAddr.insert( 0, "11110" )
        self.i2cAddr.grid( row=0, column=1, rowspan=1, columnspan=1 )

        self.lblDevAddr = Label( self, text='Dev addr:' )
        self.lblDevAddr.grid( row=0, column=2, rowspan=1, columnspan=1 )

        self.devAddr = Entry( self )
        self.devAddr.insert( 0, "0" )
        self.devAddr.grid( row=0, column=3, rowspan=1, columnspan=1 )

        self.lblCnt = Label( self, text='Bytes cnt:' )
        self.lblCnt.grid( row=0, column=4, rowspan=1, columnspan=1 )

        self.bytesCnt = Entry( self )
        self.bytesCnt.insert( 0, "128" )
        self.bytesCnt.grid( row=0, column=5, rowspan=1, columnspan=1 )


        self.i2cReadBtn = Button( self, text='Read I2C' )
        self.i2cReadBtn["command"] = self.readI2c
        self.i2cReadBtn.grid( row=1, column=0, rowspan=1, columnspan=1 )
        
        self.i2cWriteBtn = Button( self, text='Write I2C' )
        self.i2cWriteBtn["command"] = self.writeI2c
        self.i2cWriteBtn.grid( row=1, column=5, rowspan=1, columnspan=1 )
        
        self.text = Text( self )
        self.text.grid( row=2, column=0, rowspan=5, columnspan=6 )
    
        self.toTextBtn = Button( self, text = 'To string' )
        self.toTextBtn["command"] = self.toString
        self.toTextBtn.grid( row=8, column = 3 )
        
        

    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()
        self.createWidgets()
        self.io = Supply()
        pp = self.io.io( 0 )
        print "initial pp = " + str( pp )
    
    #~ for a in range( 24, 127 ):
        #~ res, d = self.read( a, 0, 4 )
        #~ print "                                      addr = " + str( a ) + ", res = " + str( res )


root = Tk()
app = Application( master=root )
app.mainloop()




