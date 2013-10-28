#!/bin/python

import xmlrpclib
from Tkinter import *

class Application( Frame ):

    def createWidgets(self):
        self.fwdBtn = Button( self,            text='fwd' )
        self.fwdBtn.bind( "<Button-1>",        self.forward )
        self.fwdBtn.bind( "<ButtonRelease-1>", self.stop )	
        self.fwdBtn.grid( row=0, column=1 )
        
        self.bwdBtn = Button( self,            text='bwd' )
        self.bwdBtn.bind( "<Button-1>",        self.backward )
        self.bwdBtn.bind( "<ButtonRelease-1>", self.stop )	
        self.bwdBtn.grid( row=1, column=1 )
        
        self.leftBtn = Button( self,            text='left' )
        self.leftBtn.bind( "<Button-1>",        self.left )
        self.leftBtn.bind( "<ButtonRelease-1>", self.stop )	
        self.leftBtn.grid( row=1, column=0 )
        
        self.rightBtn = Button( self,            text='right' )
        self.rightBtn.bind( "<Button-1>",        self.right )
        self.rightBtn.bind( "<ButtonRelease-1>", self.stop )	
        self.rightBtn.grid( row=1, column=2 )
        
        self.scaleX = Scale( self, orient='horizontal', from_=0, to=255, command=self.camPos )
        self.scaleX.set( 127 )
        self.scaleX.grid( row=2, column=0, rowspan=1, columnspan=3 )

        self.scaleY = Scale( self, orient='vertical', from_=0, to=255, command=self.camPos )
        self.scaleY.grid( row=3, column=1, rowspan=3, columnspan=1 )
        self.scaleY.set( 127 )
        
        self.lightVar = IntVar()
        self.lightBtn = Checkbutton( self, text="light", command=self.light, variable=self.lightVar )
        self.lightBtn.grid( row=6, column=1 )

    def camPos( self, arg ):
        x = self.scaleX.get()
        y = self.scaleY.get()
        print "x=", x, ", y=", y
        self.proxy.setCamPos( x, y )
        
    def forward( self, v ):
        self.proxy.setMoto( 1, 0, 1, 0 )

    def backward( self, v ):
        self.proxy.setMoto( 0, 1, 0, 1 )
        
    def left( self, v ):
        self.proxy.setMoto( 1, 0, 0, 0 )
        
    def right( self, v ):
        self.proxy.setMoto( 0, 0, 1, 0 )
        
    def stop( self, v ):
        self.proxy.setMoto( 0, 0, 0, 0 )
        
    def light( self ):
        v = self.lightVar.get()
        print "value = ", v
        self.proxy.setLight( v )

    def __init__( self, master=None ):
        Frame.__init__( self, master )
        self.grid()
        self.createWidgets()
        self.proxy = xmlrpclib.ServerProxy( "http://192.168.0.196:8765/" )
        print "proxy = ", self.proxy


root = Tk()
app = Application( master=root )
app.mainloop()




