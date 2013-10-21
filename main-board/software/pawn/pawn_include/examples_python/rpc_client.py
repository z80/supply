#!/bin/python

import xmlrpclib
from Tkinter import *

#proxy = xmlrpclib.ServerProxy( "http://localhost:8000/" )
#print "3 is even: %s" % str(proxy.is_even(3))
#print "100 is even: %s" % str(proxy.is_even(100))



class Application(Frame):
    def say_hi(self):
        print "hi there, everyone!"

    def createWidgets(self):
        self.QUIT = Button(self)
        self.QUIT["text"] = "QUIT"
        self.QUIT["fg"]   = "red"
        self.QUIT["command"] =  self.quit

        self.QUIT.pack({"side": "left"})

        self.hi_there = Button(self)
        self.hi_there["text"] = "Hello",
        self.hi_there["command"] = self.say_hi

        self.hi_there.pack( {"side": "left"} )
        
        self.scaleX = Scale( orient='horizontal', from_=0, to=255, command=self.postValue )
        self.scaleX.pack()
        self.scaleX.set( 127 )

        self.scaleY = Scale( orient='vertical', from_=0, to=255, command=self.postValue )
        self.scaleY.pack()
        self.scaleY.set( 127 )

    def postValue( self, arg ):
        x = self.scaleX.get()
        y = self.scaleY.get()
        print "x=", x, ", y=", y
        self.proxy.setCamPos( x, y )

    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.pack()
        self.createWidgets()
        self.proxy = xmlrpclib.ServerProxy( "http://localhost:8765/" )
        print "proxy = ", self.proxy


root = Tk()
app = Application( master=root )
app.mainloop()




