#!/usr/bin/python
# -*- coding: utf-8 -*-

from ttk import Frame, Button, Style
from Tkinter import Tk, Text, END, BOTH, W, N, E, S
import tkMessageBox as box
import tkFileDialog
import re
import os
import subprocess
import sys

PAWNCC        = "./bin/pawncc"
COMPILED_SCRIPT_FILE_NAME = "./instructions.amx"
PAWNCC_SUFFIX = [ "-i./include", "-oinstructions", "-S2000", "-O3", "-v" ]
USBCTRL       = [ "./bin/usbctrl", "./instructions.amx" ]
DFU_EXEC      = [ "./bin/dfu_stm", "flash" ]
HELP_FILE     = "./doc/index.html"

class Gui( Frame ):
    def __init__( self, parent ):
        Frame.__init__( self, parent )
        self.parent = parent
        self.initUi()
        
    def initUi( self ):
        self.parent.title( "Supply handler" )
        self.style = Style()
        self.style.theme_use( "default" )
        self.pack( fill=BOTH, expand=1 )

        self.columnconfigure( 1, weight=1 )
        self.columnconfigure( 3, pad=7 )
        self.rowconfigure( 3, weight=1 )
        self.rowconfigure( 5, pad=7 )

        self.openBtn = Button( self, text="Compile script", command=self.openFirmwareSource )
        self.openBtn.grid( row=0, column=0, rowspan=1, columnspan=1, sticky=W+N )

        self.flashBtn = Button( self, text="Load script", command=self.flashFirmware )
        self.flashBtn.grid( row=0, column=1, rowspan=1, columnspan=1, sticky=W+N )

        self.dfuBtn = Button( self, text="Firmware upgrade", command=self.dfuFirmware )
        self.dfuBtn.grid( row=0, column=2, rowspan=1, columnspan=1, sticky=W+N )

        self.helpBtn = Button( self, text="Help", command=self.openHelp )
        self.helpBtn.grid( row=0, column=3, rowspan=1, columnspan=1, sticky=W+N )

        self.txt = Text( self )
        self.txt.grid( row=2, column=0, rowspan=5, columnspan=4, sticky=E+W+S+N )

    def openFirmwareSource( self ):
        ftypes = [ ('Script files', '*.p'), ('All files', '*') ]
        dlg = tkFileDialog.Open( self, filetypes = ftypes )
        fileName = dlg.show()
        
        if ( fileName != '' ):
            # Clear text output window.
            self.txt.delete( 1.0, END )
            # Extract file path to include it into consideration.
            path = os.path.dirname( fileName )
            path = "-i" + path
            print "Path: "
            print path
            cmd = [ PAWNCC, fileName, path ]
            cmd = cmd + PAWNCC_SUFFIX
            # Execute compilation.
            try:
                p = subprocess.Popen( cmd, stdout=subprocess.PIPE )
                out, err = p.communicate()
            except OSError:
                out = "Error: failed to execute compiled instructions load procedure!"
            self.txt.insert( END, out )

    def flashFirmware( self ):
        self.txt.delete( 1.0, END )
        if ( not os.path.exists( COMPILED_SCRIPT_FILE_NAME ) ):
            out = "Error: it seems there is no compiled script file for supply board."
        else:
            cmd = USBCTRL
            p = subprocess.Popen( cmd, stdout=subprocess.PIPE )
            out, err = p.communicate()
        self.txt.insert( END, out )
        
    def dfuFirmware( self ):
        ftypes   = [ ('Firmware files', '*.bin'), ('All files', '*') ]
        dlg      = tkFileDialog.Open( self, filetypes = ftypes )
        fileName = dlg.show()
        if ( fileName != "" ):
            cmd = DFU_EXEC
            cmd.append( fileName )
            try:
                p = subprocess.Popen( cmd, stdout=subprocess.PIPE )
                out, err = p.communicate()
            except OSError:
                out = "Error: Failed to execure device firmware upgrade"

    def openHelp( self ):
        self.openFile( HELP_FILE );

    def openFile( self, fileName ):
        if sys.platform=='win32':
            subprocess.Popen(['start', fileName], shell= True)

        elif sys.platform=='darwin':
            subprocess.Popen(['open', fileName])

        else:
            try:
                subprocess.Popen( [ 'xdg-open', fileName ] )
            except OSError:
                # er, think of something else to try
                # xdg-open *should* be supported by recent Gnome, KDE, Xfce
                print "Error opening file!"
    
def main():
    root = Tk()
    ex = Gui( root )
    root.geometry( "350x300+300+300" )
    root.mainloop()  


if __name__ == '__main__':
    main() 
