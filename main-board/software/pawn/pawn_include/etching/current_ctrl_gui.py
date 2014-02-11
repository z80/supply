#!/bin/python

import xmlrpclib
from Tkinter import *
import matplotlib.pyplot as plt
from current_ctrl import *
import time


class Application(Frame):

    def createWidgets(self):
        l = Label( text="Volt(mv)")
        l.grid( row=0, column=0)

        l = Label( text="Curr(ma)")
        l.grid( row=0, column=1)
        
        self.voltSb = Spinbox( from_=0, to=4000, width=5 )
        self.voltSb.insert( 0, 0 )
        self.voltSb.grid( row=1, column=0 )
        self.voltSb[ "command" ] = self.setVoltCurr

        self.currSb = Spinbox( from_=0, to=4000, width=5 )
        self.currSb.insert( 0, 0 )
        self.currSb.grid( row=1, column=1 )
        self.currSb[ "command" ] = self.setVoltCurr
        
        self.voltSc = Scale( orient='vertical', from_=0, to=4000, command=self.postVoltCurr )
        self.voltSc.set( 0 )
        self.voltSc.grid( row=2, column=0, rowspan=25, columnspan=1 )

        self.currSc = Scale( orient='vertical', from_=0, to=200, command=self.postVoltCurr )
        self.currSc.set( 0 )
        self.currSc.grid( row=2, column=1, rowspan=25, columnspan=1 )

        self.showBtn = Button( text="show plot", command=self.plotData )
        self.showBtn.grid( row=27, column=0 )
        
        self.io = CurrentCtrl()
        self.initData()
        self.updateClock()
        

    def setVoltCurr( self ):
        v = self.voltSb.get()
        i = self.currSb.get()
        self.voltSc.set( v )
        self.currSc.set( i )

    def postVoltCurr( self, arg ):
        v = self.voltSc.get()
        i = self.currSc.get()
        self.voltSb.delete( 0, 'end' )
        self.voltSb.insert( 0, v )
        self.currSb.delete( 0, 'end' )
        self.currSb.insert( 0, i )
        self.io.setVi( v, i )
        
    def updateClock( self ):
        self.master.after( 1000, self.updateClock )
        v, i = self.io.vi()
        print "Timeout i = " + str( i ) + ", v = " + str( v )
        self.vPlot.append( v )
        self.iPlot.append( i )
        self.tPlot.append( time.time() - self.baseT )

    def plotData( self ):
        vv = self.vPlot
        ii = self.iPlot
        tt = self.tPlot

        plt.figure( 1 )
        plt.subplot( 2, 1, 1 )
        plt.plot( tt, vv )
        plt.subplot( 2, 1, 2 )
        plt.plot( tt, ii )
        plt.show()
       
        
    def initData( self ):
        self.vPlot = []
        self.iPlot = []
        self.tPlot  = []
        self.baseT = time.time()

    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master = master
        self.grid()
        self.createWidgets()


root = Tk()
app = Application( master=root )
app.mainloop()




