"""
Waltech Ladder Maker is distributed under the MIT License. 

Copyright (c) 2014 Karl Walter.  karl (at) waltech.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""
from PyQt4 import QtCore, QtGui
from PyQt4.Qt import QFont
from PyQt4.QtGui import QApplication, QCursor
from PyQt4.QtCore import Qt
import time
import subprocess
from subprocess import PIPE
import sys
import os
import glob
import re
import serial


os.chdir("../helpers/hexes")
#print "current dir:", os.getcwd()
print "looking for programming hardware on usb"





ardOnUsb = False
p = subprocess.Popen(r"lsusb",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
output,error =p
if "2341:0043" in output:
    print"Arduino probably connected to usb"
    ardOnUsb = True
else: 
    print"Arduino not found connected to USB"

if ardOnUsb == True:
    for i in range(4):
    
        USBserialPort = "/dev/ttyACM"+str(i)
        commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + USBserialPort + " -c stk500v1 -B5 -F"

        commandwfile = commandAvrDude

        p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        output,error =p

        print USBserialPort
        #print "output", output
        #print "error", error

        if "avrdude: AVR device initialized and ready to accept instructions" in error:
            print" this is the port:",  USBserialPort


