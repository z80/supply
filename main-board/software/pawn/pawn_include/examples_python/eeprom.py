#!/bin/python

import xmlrpclib
from Tkinter import *
from time import sleep
#from supplyctrlusb import *

#proxy = xmlrpclib.ServerProxy( "http://localhost:8000/" )
#print "3 is even: %s" % str(proxy.is_even(3))
#print "100 is even: %s" % str(proxy.is_even(100))



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
        io.setIo( 0, 1 )
        # Waiting for completion
        for t in range( self.TRIES ):
            finished = io.io( 0 )
            if ( finished == 0 ):
                res = io.io( 1 )
                print "res = " + str( res )
                if res != 0:
                    return (res, [])
                d = []
                for i in range(cnt):
                    v = io.io( 2+i )
                    d.append( v )
                print "data", data
                return ( res, d )
            sleep( self )
        print "Read timeout"
            
    def write( self, i2cAddr, devAddr, data ):
        print "write " + str(i2cAddr) + ", " + str(devAddr) + ", " + str(cnt)
        io = self.io
        io.setIo( 1, i2cAddr )
        io.setIo( 2, devAddr )
        cnt = len( data )
        io.setIo( 3, cnt )
        for i in range( cnt ):
            io.setIo( 4+i, data[i] )
        # Start writing data.
        io.setIo( 0, 2 )
        # Waiting for completion
        for t in range( self.TRIES ):
            finished = io.io( 0 )
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
        return
        
        for i in range( 0, cnt, self.FRAME ):
            res, data = self.read( i2cAddr, devAddr, cnt )
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
        return

        for i in range( 0, cnt, self.FRAME ):
            d = []
            for k in range( self.FRAME ):
                d.append( data[i+k] )
            res, data = self.write( i2cAddr, devAddr, d )
            if res > 0:
                print "res = " + str( res )
                return
            print "Ready"

    def createWidgets(self):
        self.lblI2cAddr = Label( self, text='I2C addr:' )
        self.lblI2cAddr.grid( row=0, column=0, rowspan=1, columnspan=1 )
        
        self.i2cAddr = Entry( self )
        self.i2cAddr.insert( 0, "1010000" )
        self.i2cAddr.grid( row=0, column=1, rowspan=1, columnspan=1 )

        self.lblDevAddr = Label( self, text='Dev addr:' )
        self.lblDevAddr.grid( row=0, column=2, rowspan=1, columnspan=1 )

        self.devAddr = Entry( self )
        self.devAddr.insert( 0, "0" )
        self.devAddr.grid( row=0, column=3, rowspan=1, columnspan=1 )

        self.lblCnt = Label( self, text='Bytes cnt:' )
        self.lblCnt.grid( row=0, column=4, rowspan=1, columnspan=1 )

        self.bytesCnt = Entry( self )
        self.bytesCnt.insert( 0, "8" )
        self.bytesCnt.grid( row=0, column=5, rowspan=1, columnspan=1 )


        self.i2cReadBtn = Button( self, text='Read I2C' )
        self.i2cReadBtn["command"] = self.readI2c
        self.i2cReadBtn.grid( row=1, column=0, rowspan=1, columnspan=1 )
        
        self.i2cWriteBtn = Button( self, text='Write I2C' )
        self.i2cWriteBtn["command"] = self.writeI2c
        self.i2cWriteBtn.grid( row=1, column=5, rowspan=1, columnspan=1 )
        
        self.text = Text( self )
        self.text.grid( row=2, column=0, rowspan=5, columnspan=6 )
        
        

    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()
        self.createWidgets()
        #self.io = Supply()


root = Tk()
app = Application( master=root )
app.mainloop()




