#!/usr/bin/env python
# -*- coding: utf-8 -*- 
#AAAA
"""
Waltech Ladder Maker is distributed under the MIT License. 

Copyright (c) 2014 Karl Walter.  karl (at) waltech.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

#this wil be the outline to C functions
from PyQt4 import QtCore, QtGui
from PyQt4.Qt import QFont
from PyQt4.QtGui import QApplication, QCursor
from PyQt4.QtCore import Qt

import subprocess, datetime, os, time, signal

from subprocess import PIPE
import sys

import re
#import serial


class tester():
    
    def __init__(self, opSys,currentHW):#bring in all the things being sent down here
        self.opSys = opSys
        self.currentHW = currentHW
    
    def test1(self,displayOutputPlace):
        QApplication.setOverrideCursor(QCursor(Qt.WaitCursor))
        displayOutputPlace.setText("")
        self.boldLine(displayOutputPlace,"Test for "+self.currentHW+" Hardware on USB")
        print "current dir:", os.getcwd()
        os.chdir("../helpers/hexes")
        print "current dir:", os.getcwd()
        print "looking for programming hardware on usb"
        dudeCommand  = None
        QApplication.processEvents()#this makes the UI update before going on.
        if self.opSys == "NIX" and self.currentHW == "Waltech": dudeCommand = self.testWaltechNIX(displayOutputPlace)
        if self.opSys == "WIN" and self.currentHW == "Waltech": dudeCommand = self.testWaltechWIN(displayOutputPlace)
        if self.opSys == "MAC" and self.currentHW == "Waltech": dudeCommand = self.testWaltechMAC(displayOutputPlace)
        if self.opSys == "NIX" and self.currentHW == "ArduinoUno": dudeCommand = self.testArduinoUnoNIX(displayOutputPlace)
        if self.opSys == "WIN" and self.currentHW == "ArduinoUno": dudeCommand = self.testArduinoUnoWIN(displayOutputPlace)
        if self.opSys == "MAC" and self.currentHW == "ArduinoUno": dudeCommand = self.testArduinoUnoMAC(displayOutputPlace)
        if self.opSys == "NIX" and self.currentHW == "ArduinoMega": dudeCommand = self.testArduinoMegaNIX(displayOutputPlace)
        if self.opSys == "WIN" and self.currentHW == "ArduinoMega": dudeCommand = self.testArduinoMegaWIN(displayOutputPlace)
        if self.opSys == "MAC" and self.currentHW == "ArduinoMega": dudeCommand = self.testArduinoMegaMAC(displayOutputPlace)
        if self.opSys == "NIX" and self.currentHW == "ArduinoNano": dudeCommand = self.testArduinoNanoNIX(displayOutputPlace)
        if self.opSys == "WIN" and self.currentHW == "ArduinoNano": dudeCommand = self.testArduinoNanoWIN(displayOutputPlace)
        if self.opSys == "MAC" and self.currentHW == "ArduinoNano": dudeCommand = self.testArduinoNanoMAC(displayOutputPlace)
        os.chdir("../")
        time.sleep(1)
        QApplication.restoreOverrideCursor()
        os.chdir("../")
        print "current dir:", os.getcwd()
        os.chdir("./program")
        print "current dir:", os.getcwd()
        if "program" not in os.getcwd(): print "worng place"
        return dudeCommand 
  
  
    """
    Win: 
        send avrdude command to all ports 1-9
        timeout
        parse error

    Nix:
        Waltech: strait to avrdude command
        
        Ard: 
            lsusb
            dmesg
            avrdude command


    """  
  
  
        
###WALTECH        
    def testWaltechWIN(self,displayOutputPlace):

        #first check for libusb-win32?
        
        commandwfile = r"..\\WinAVR\\bin\\avrdude.exe -p m32 -P usb -c usbtiny -B5 -U lfuse:r:-:h -U hfuse:r:-:h"
        output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        displayOutputPlace.setText ("")
        self.boldLine(displayOutputPlace,"Output:")
        displayOutputPlace.append (str(error))
        if "avrdude: AVR device initialized and ready to accept instructions" in str(error) \
            and "avrdude: Device signature = 0x1e9502" in str(error):
            self.boldLine(displayOutputPlace,"USB Programmer Found, OK.")
            displayOutputPlace.append("Fuses:")
            displayOutputPlace.append(str(output))
            if "0x1f"in str(output) and "0xc9" in str(output):
                displayOutputPlace.append("Fuses OK.")

            else:
                commandwfile = r"..\\WinAVR\\bin\\avrdude.exe -p m32 -P usb -c usbtiny -B5 -U hfuse:w:0xC9:m -U lfuse:w:0x1F:m"
                output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                if "avrdude: 1 bytes of lfuse verified" in str(error):
                    displayOutputPlace.append ("Fuses Reset, OK.")
                else:
                    self.boldLine(displayOutputPlace,"Fuse Error")
                    
        if "avrdude.exe: Error: Could not find" in str(error):
            self.boldLine(displayOutputPlace,"USB Programmer Not Found.")
            displayOutputPlace.append("Check USB connection, and USB driver")
            
        if "avrdude.exe: initialization failed, rc=-1" in str(error):
            self.boldLine(displayOutputPlace,"Hardware Not Responding.")
            displayOutputPlace.append("USB OK, Check power to hardware.")
            
        if "avrdude.exe: error: usbtiny_transmit: error sending control message: Operation not permitted" \
                in str(error) and "(expected 4, got -1)" in str(error) : 
            self.boldLine(displayOutputPlace,"No permission to USB device")
            displayOutputPlace.append("See Help > USB")


    def testWaltechNIX(self,displayOutputPlace):
        commandwfile = r"../avrdude  -C ../avrdude.conf -p m32 -P usb -c usbtiny -B5 -U lfuse:r:-:h -U hfuse:r:-:h"
        output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        displayOutputPlace.setText ("")
        self.boldLine(displayOutputPlace,"Output:")
        displayOutputPlace.append (str(error))
        
        if "avrdude: AVR device initialized and ready to accept instructions" in str(error) \
            and "avrdude: Device signature = 0x1e9502" in str(error):
            self.boldLine(displayOutputPlace,"USB Programmer Found, OK.")
            displayOutputPlace.append("Fuses:")
            displayOutputPlace.append(str(output))
            if "0x1f"in str(output) and "0xc9" in str(output):
                displayOutputPlace.append("Fuses OK.") 
            else:
                commandwfile = r"../avrdude  -C ../avrdude.conf -p m32 -P usb -c usbtiny -B5 -U hfuse:w:0xC9:m -U lfuse:w:0x1F:m "
                output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                if "avrdude: 1 bytes of lfuse verified" in str(error):
                    displayOutputPlace.append ("Fuses Reset, OK.")
                else:
                    self.boldLine(displayOutputPlace,"Fuse Error")
                            
        if "avrdude: Error: Could not find USBtiny device" in str(error):
            self.boldLine(displayOutputPlace,"USB Programmer Not Found.")
            displayOutputPlace.append("Check USB connection, and USB driver")
            
        if "avrdude: initialization failed, rc=-1" in str(error):
            self.boldLine(displayOutputPlace,"Hardware Not Responding.")
            displayOutputPlace.append("USB OK, Check power to hardware.")
            
        if "avrdude: error: usbtiny_transmit: error sending control message: Operation not permitted" \
                in str(error) and "(expected 4, got -1)" in str(error) : 
            self.boldLine(displayOutputPlace,"No permission to USB device")
            displayOutputPlace.append("See Help > USB")
    
            #SUBSYSTEM=="usb", ATTR{product}=="USBtiny", ATTR{idProduct}=="0c9f", ATTRS{idVendor}=="1781", MODE="0660", GROUP="dialout"
            #disconnect and reconnect USB"  


    def testWaltechMAC(self,displayOutputPlace):
        commandwfile = r"avrdude -p m32 -P usb -c usbtiny -B5 -U lfuse:r:-:h -U hfuse:r:-:h"
        output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        displayOutputPlace.setText ("")
        self.boldLine(displayOutputPlace,"Output:")
        displayOutputPlace.append (str(error))
        
        if "avrdude: AVR device initialized and ready to accept instructions" in str(error) \
            and "avrdude: Device signature = 0x1e9502" in str(error):
            self.boldLine(displayOutputPlace,"USB Programmer Found, OK.")
            displayOutputPlace.append("Fuses:")
            displayOutputPlace.append(str(output))
            if "0x1f"in str(output) and "0xc9" in str(output):
                displayOutputPlace.append("Fuses OK.") 
            else:
                commandwfile = r"avrdude -p m32 -P usb -c usbtiny -B5 -U hfuse:w:0xC9:m -U lfuse:w:0x1F:m "
                output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                if "avrdude: 1 bytes of lfuse verified" in str(error):
                    displayOutputPlace.append ("Fuses Reset, OK.")
                else:
                    self.boldLine(displayOutputPlace,"Fuse Error")
                            
        if "avrdude: Error: Could not find USBtiny device" in str(error):
            self.boldLine(displayOutputPlace,"USB Programmer Not Found.")
            displayOutputPlace.append("Check USB connection, and USB driver")
            
        if "avrdude: initialization failed, rc=-1" in str(error):
            self.boldLine(displayOutputPlace,"Hardware Not Responding.")
            displayOutputPlace.append("USB OK, Check power to hardware.")
            
        if "avrdude: error: usbtiny_transmit: error sending control message: Operation not permitted" \
                in str(error) and "(expected 4, got -1)" in str(error) : 
            self.boldLine(displayOutputPlace,"No permission to USB device")
            displayOutputPlace.append("See Help > USB")
    
            #SUBSYSTEM=="usb", ATTR{product}=="USBtiny", ATTR{idProduct}=="0c9f", ATTRS{idVendor}=="1781", MODE="0660", GROUP="dialout"
            #disconnect and reconnect USB"  
     
####ARD MEGA

    def testArduinoMegaWIN(self,displayOutputPlace):
        self.boldLine(displayOutputPlace,"Checking ports 1-9 for Arduino.")
        QApplication.processEvents()#this makes the UI update before going on.
        print "scanning com 1 to com 9..."
        USBserialPort = None
        for i in range(9):
            
            maybePort = "com"+str(i)
            print "maybe port : ",maybePort
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m2560 -P " + maybePort + " -c wiring"
            commandwfile = commandAvrDude #why?  
            start = datetime.datetime.now()
            process = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True)
            working = False
            while process.poll() is None:
                time.sleep(0.1)
                now = datetime.datetime.now()
                if (now - start).seconds > 2 and working == False:
                    displayOutputPlace.append("Working...")
                    working = True
                    QApplication.processEvents()#this makes the UI update before going on.
                if (now - start).seconds > 10:
                    subprocess.call(['taskkill', '/F', '/T', '/PID', str(process.pid)])
                    #os.kill(process.pid, signal.SIGKILL) #use SIGKILL for not windows
                    #os.waitpid(-1, os.WNOHANG)              #use WHOHANG for not windows
                    print "timed out"
                    output = process.stdout.read()
                    error = process.stderr.read()
                    print "error:", error
                    print "output", output
                    if "timeout" in error:
                        self.boldLine(displayOutputPlace, "Arduino stk500 progrmmer timeout")
                        USBserialPort = "timeout"
            output = process.stdout.read()
            error = process.stderr.read()
            if "avrdude.exe: AVR device initialized and ready to accept instructions" in error:
                USBserialPort = maybePort
                print" this is the port:",  USBserialPort
                self.boldLine(displayOutputPlace, "Arduino found on "+str(USBserialPort))
        if USBserialPort == None: 
            self.boldLine(displayOutputPlace,"Arduino not found")
            displayOutputPlace.append("or is numbered greater than COM9")
            return None
        else: 
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m2560 -P " + USBserialPort + " -c wiring"
            return commandAvrDude 

    def testArduinoMegaNIX(self,displayOutputPlace): 
        USBserialPort = None
        ardOnUsb = False
        output,error = subprocess.Popen(r"lsusb",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        if "2341:" in output:
            self.boldLine(displayOutputPlace,"Arduino is in USB list")
            ardOnUsb = True
        else: 
            self.boldLine(displayOutputPlace,"Arduino not found in USB list")
        displayOutputPlace.append("checking dmesg:")
        output,error = subprocess.Popen(r"dmesg",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        match_found=False
        matches = re.finditer("Arduino", output)
        for m in matches: match_found=True
        if (match_found):
            displayOutputPlace.append("Arduino in dmesg")
            #m.start()  # equals the starting index of the last match
            #m.end()    # equals the ending index of the last match 
            rest = output[m.end():-1]
            print "the rest:" ,rest
            match_found=False
            matches = re.finditer("tty", rest)
            for m in matches: match_found=True
            if (match_found):
                port = rest[m.start():m.end()+4]
                if ardOnUsb == True:
                    displayOutputPlace.append("Arduino may be on port: "+str(port))
                else: displayOutputPlace.append("Arduino has been on\n port: "+str(port))
        else: displayOutputPlace.append("Arduino not listed in dmesg")
        portFound = False
        if ardOnUsb == True:
            displayOutputPlace.append("checking ports")
            for i in range(6):
                maybePort = "/dev/ttyACM"+str(i)
                commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m2560 -P " + maybePort + " -c stk500v2 -F -D"
                QApplication.processEvents()#this makes the UI update before going on.
                start = datetime.datetime.now()
                process = subprocess.Popen(commandAvrDude,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True)
                working = False
                while process.poll() is None:
                    time.sleep(0.1)
                    now = datetime.datetime.now()
                    if (now - start).seconds > 2 and working == False:
                        displayOutputPlace.append("Working...")
                        working = True
                        QApplication.processEvents()#this makes the UI update before going on.
                    if (now - start).seconds > 10:
                        subprocess.call(['taskkill', '/F', '/T', '/PID', str(process.pid)])
                        os.kill(process.pid, signal.SIGKILL)
                        os.waitpid(-1, os.WNOHANG)
                        print "timed out"
                        output = process.stdout.read()
                        error = process.stderr.read()
                        print "error:", error
                        print "output", output
                        if "timeout" in error:
                            self.boldLine(displayOutputPlace, "Arduino stk500 progrmmer timeout")
                            USBserialPort = "timeout"
                output = process.stdout.read()
                error = process.stderr.read()
                print error
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    self.boldLine(displayOutputPlace,"this is the port:"+str(USBserialPort))
                    print"This is the port: ", USBserialPort
                    portFound = True
                    break
        if portFound == False:
            self.boldLine(displayOutputPlace,"Arduino port not found in scan")
            return None
        else:
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m2560 -P " + USBserialPort  + " -c stk500v2 -F -D"
            return commandAvrDude 
                
    def testArduinoMegaMAC(self,displayOutputPlace):
        USBserialPort = None
        ardOnUsb = False
        p = subprocess.Popen(r"system_profiler SPUSBDataType",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        output,error =p
        print output
        if "0x2341" in output:
            self.boldLine(displayOutputPlace,"Arduino is in USB list")
            ardOnUsb = True
        else: 
            self.boldLine(displayOutputPlace,"Arduino not found in USB list")

        QApplication.processEvents()#this makes the UI update before going on.
        portFound = False
        if ardOnUsb == True:
            
            displayOutputPlace.append("checking usb ports in /dev:")
            output,error = subprocess.Popen("ls /dev/tty.*",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
            devList = output.split()
            for i in range(len(devList)):
                maybePort = devList[i]
                commandAvrDude = r"avrdude -p m2560 -P " + maybePort + " -c stk500v2 -B5 -F"
                commandwfile = commandAvrDude
                p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                output,error =p
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    print" this is the port:",  USBserialPort
                    portFound = True
                    displayOutputPlace.append("MEGA found on "+ USBserialPort )
            #again for cu.usbmodem...
            output,error = subprocess.Popen("ls /dev/cu.*",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
            devList = output.split()
            for i in range(len(devList)):
                maybePort = devList[i]
                commandAvrDude = r"avrdude -p m2560 -P " + maybePort + " -c stk500v2 -B5 -F"
                commandwfile = commandAvrDude
                p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                output,error =p
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    print" this is the port:",  USBserialPort
                    portFound = True
                    displayOutputPlace.append("MEGA found on " + USBserialPort )
        if portFound == False:
            self.boldLine(displayOutputPlace,"Arduino port not found in scan")
            return None
        else: 
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m2560 -P " + USBserialPort  + " -c stk500v2 -B5 -F"
            return commandAvrDude 
        
###ARD UNO        
    def testArduinoUnoWIN(self,displayOutputPlace):
        
        self.boldLine(displayOutputPlace,"Checking ports for Arduino.")
        USBserialPort = None
        for i in range(9):
            
            maybePort = "com"+str(i)    
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m328p -P " + maybePort + " -c arduino"
            start = datetime.datetime.now()
            process = subprocess.Popen(commandAvrDude,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True)
            working = False
            while process.poll() is None:
                time.sleep(0.1)
                now = datetime.datetime.now()
                if (now - start).seconds > 2 and working == False:
                    displayOutputPlace.append("Working...")
                    working = True
                    QApplication.processEvents()#this makes the UI update before going on.
                if (now - start).seconds > 10:
                    subprocess.call(['taskkill', '/F', '/T', '/PID', str(process.pid)])
                    #os.kill(process.pid, signal.SIGKILL) #use SIGKILL for not windows
                    #os.waitpid(-1, os.WNOHANG)              #use WHOHANG for not windows
                    print "timed out"
                    output = process.stdout.read()
                    error = process.stderr.read()
                    print "error:", error
                    print "output", output
                    if "timeout" in error:
                        self.boldLine(displayOutputPlace, "Arduino stk500 progrmmer timeout")
                        USBserialPort = "timeout"
            output = process.stdout.read()
            error = process.stderr.read()
            if "avrdude.exe: AVR device initialized and ready to accept instructions" in error:
                USBserialPort = maybePort
                print" this is the port:",  USBserialPort
                self.boldLine(displayOutputPlace, "Arduino found on "+str(USBserialPort))
        if USBserialPort == None: 
            self.boldLine(displayOutputPlace,"Arduino not found")
            displayOutputPlace.append("or is numbered greater than COM9")
            return None
        else: 
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m328p -P " + USBserialPort + " -c arduino"
            return commandAvrDude    
            
    def testArduinoUnoNIX(self,displayOutputPlace): 
        USBserialPort = None
        ardOnUsb = False
        output,error = subprocess.Popen(r"lsusb",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        if "2341:" in output:
            self.boldLine(displayOutputPlace,"Arduino is in USB list")
            ardOnUsb = True
        else: 
            self.boldLine(displayOutputPlace,"Arduino not found in USB list")
        displayOutputPlace.append("checking dmesg:")
        output,error = subprocess.Popen(r"dmesg",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        match_found=False
        matches = re.finditer("Arduino", output)
        for m in matches: match_found=True
        if (match_found):
            displayOutputPlace.append("Arduino in dmesg")
            #m.start()  # equals the starting index of the last match
            #m.end()    # equals the ending index of the last match 
            rest = output[m.end():-1]
            print "the rest:" ,rest
            match_found=False
            matches = re.finditer("tty", rest)
            for m in matches: match_found=True
            if (match_found):
                port = rest[m.start():m.end()+4]
                if ardOnUsb == True:
                    displayOutputPlace.append("Arduino may be on port: "+str(port))
                else: displayOutputPlace.append("Arduino has been on\n port: "+str(port))
        else: displayOutputPlace.append("Arduino not listed in dmesg")
        portFound = False
        if ardOnUsb == True:
            displayOutputPlace.append("checking ports")
            for i in range(6):
                maybePort = "/dev/ttyACM"+str(i)
                commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + maybePort + " -c stk500v1 -B5 -F"
                commandwfile = commandAvrDude
                output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    self.boldLine(displayOutputPlace,"this is the port:"+str(USBserialPort))
                    print"This is the port: ", USBserialPort
                    portFound = True
        if portFound == False:
            self.boldLine(displayOutputPlace,"Arduino port not found in scan")
            return None
        else: 
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + USBserialPort + " -c stk500v1 -B5 -F"
            return commandAvrDude
        
        
                
    def testArduinoUnoMAC(self,displayOutputPlace):
        USBserialPort = None
        ardOnUsb = False
        p = subprocess.Popen(r"system_profiler SPUSBDataType",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        output,error =p
        print output
        if "0x2341" in output:
            self.boldLine(displayOutputPlace,"Arduino is in USB list")
            ardOnUsb = True
        else: 
            self.boldLine(displayOutputPlace,"Arduino not found in USB list")
        QApplication.processEvents()#this makes the UI update before going on.
        portFound = False
        if ardOnUsb == True:
            
            displayOutputPlace.append("checking usb ports in /dev:")
            output,error = subprocess.Popen("ls /dev/tty.*",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
            devList = output.split()
            for i in range(len(devList)):
                maybePort = devList[i]
                commandAvrDude = r"avrdude -p m328p -P " + maybePort + " -c stk500v1 -B5 -F"
                commandwfile = commandAvrDude
                p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                output,error =p
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    print" this is the port:",  USBserialPort
                    portFound = True
                    displayOutputPlace.append("UNO found on "+ USBserialPort )
            #again for cu.usbmodem...
            output,error = subprocess.Popen("ls /dev/cu.*",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
            devList = output.split()
            for i in range(len(devList)):
                maybePort = devList[i]
                commandAvrDude = r"avrdude -p m328p -P " + maybePort + " -c stk500v1 -B5 -F"
                commandwfile = commandAvrDude
                p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                output,error =p
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    print" this is the port:",  USBserialPort
                    portFound = True
                    displayOutputPlace.append("UNO found on " + USBserialPort )
        if portFound == False:
            self.boldLine(displayOutputPlace,"Arduino port not found in scan")
            return None
        else: 
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + USBserialPort + " -c stk500v1 -B5 -F"
            return commandAvrDude
        
###ARD Nano       
    def testArduinoNanoWIN(self,displayOutputPlace):
        
        self.boldLine(displayOutputPlace,"Checking ports for Arduino.")
        USBserialPort = None
        for i in range(9):
            
            maybePort = "com"+str(i)    
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m328p -P " + maybePort + " -c arduino"
            start = datetime.datetime.now()
            process = subprocess.Popen(commandAvrDude,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True)
            working = False
            while process.poll() is None:
                time.sleep(0.1)
                now = datetime.datetime.now()
                if (now - start).seconds > 2 and working == False:
                    displayOutputPlace.append("Working...")
                    working = True
                    QApplication.processEvents()#this makes the UI update before going on.
                if (now - start).seconds > 10:
                    subprocess.call(['taskkill', '/F', '/T', '/PID', str(process.pid)])
                    #os.kill(process.pid, signal.SIGKILL) #use SIGKILL for not windows
                    #os.waitpid(-1, os.WNOHANG)              #use WHOHANG for not windows
                    print "timed out"
                    output = process.stdout.read()
                    error = process.stderr.read()
                    print "error:", error
                    print "output", output
                    if "timeout" in error:
                        self.boldLine(displayOutputPlace, "Arduino stk500 progrmmer timeout")
                        USBserialPort = "timeout"
            output = process.stdout.read()
            error = process.stderr.read()
            if "avrdude.exe: AVR device initialized and ready to accept instructions" in error:
                USBserialPort = maybePort
                print" this is the port:",  USBserialPort
                self.boldLine(displayOutputPlace, "Arduino found on "+str(USBserialPort))
        if USBserialPort == None: 
            self.boldLine(displayOutputPlace,"Arduino not found")
            displayOutputPlace.append("or is numbered greater than COM9")
            return None
        else: 
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m328p -P " + USBserialPort + " -c wiring"
            return commandAvrDude    
            
    def testArduinoNanoNIX(self,displayOutputPlace): 
        USBserialPort = None
        #ardOnUsb = False
        ardOnUsb = True
        """
        output,error = subprocess.Popen(r"lsusb",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        if "FT232" in output:
            self.boldLine(displayOutputPlace,"Arduino Nano maybe in USB list")
            ardOnUsb = True
        else: 
            self.boldLine(displayOutputPlace,"Arduino Nano not found in USB list")
        #check for uno or nano:
        displayOutputPlace.append("checking dmesg:")
        output,error = subprocess.Popen(r"dmesg",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        port = None
        match_found=False
        matches = re.finditer("Arduino", output)
        for m in matches: match_found=True
        if (match_found):
            displayOutputPlace.append("Arduino in dmesg")
            rest = output[m.end():-1]
            print "the rest:" ,rest
            match_found=False
            matches = re.finditer("tty", rest)
            for m in matches: match_found=True
            if (match_found):
                port = rest[m.start():m.end()+4]
                if ardOnUsb == True:
                    displayOutputPlace.append("Arduino may be on port: "+str(port))
                else: displayOutputPlace.append("Arduino has been on\n port: "+str(port))    
    
        #FTDI USB Serial Device converter now attached to ttyUSB0
        matches = re.finditer("FTDI USB Serial Device converter", output)
        for m in matches: match_found=True
        if (match_found):
            displayOutputPlace.append("Arduino Nano maybe in dmesg")
            rest = output[m.end():-1]
            print "the rest:" ,rest
            match_found=False
            matches = re.finditer("tty", rest)
            for m in matches: match_found=True
            if (match_found):
                port = rest[m.start():m.end()+4]
                if ardOnUsb == True:
                    displayOutputPlace.append("Arduino may be on port: "+str(port))
                else: displayOutputPlace.append("Arduino has been on\n port: "+str(port))
                
        if port == None: displayOutputPlace.append("Arduino not listed in dmesg")
        """
        #try avrdude on all ttyACM's:
        portFound = False
        if ardOnUsb == True:
            displayOutputPlace.append("checking ports")
            for i in range(6):
                maybePort = "/dev/ttyUSB"+str(i)
                commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + maybePort + " -c arduino -b 57600 -F"
                commandwfile = commandAvrDude
                output,error = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    self.boldLine(displayOutputPlace,"this is the port:"+str(USBserialPort))
                    print"This is the port: ", USBserialPort
                    portFound = True
        if portFound == False:
            self.boldLine(displayOutputPlace,"Arduino port not found in scan")
            return None
        else: 
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + USBserialPort + " -c arduino -b 57600 -F"
            return commandAvrDude
        
        
                
    def testArduinoNanoMAC(self,displayOutputPlace):
        USBserialPort = None
        ardOnUsb = False
        p = subprocess.Popen(r"system_profiler SPUSBDataType",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
        output,error =p
        print output
        if "FT232" in output:
            self.boldLine(displayOutputPlace,"Arduino Nano maybe in USB list")
            ardOnUsb = True
        else: 
            self.boldLine(displayOutputPlace,"Arduino not found in USB list")
        QApplication.processEvents()#this makes the UI update before going on.
        portFound = False
        if ardOnUsb == True:
            
            displayOutputPlace.append("checking usb ports in /dev:")
            output,error = subprocess.Popen("ls /dev/tty.*",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
            devList = output.split()
            for i in range(len(devList)):
                maybePort = devList[i]
                commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + maybePort + " -c arduino -b 57600 -F"
                commandwfile = commandAvrDude
                p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                output,error =p
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    print" this is the port:",  USBserialPort
                    portFound = True
                    displayOutputPlace.append("Nano found on "+ USBserialPort )
            #again for cu.usbmodem...
            output,error = subprocess.Popen("ls /dev/cu.*",stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
            devList = output.split()
            for i in range(len(devList)):
                maybePort = devList[i]
                commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + maybePort + " -c arduino -b 57600 -F"
                commandwfile = commandAvrDude
                p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
                output,error =p
                print maybePort
                if "avrdude: AVR device initialized and ready to accept instructions" in error:
                    USBserialPort = maybePort
                    print" this is the port:",  USBserialPort
                    portFound = True
                    displayOutputPlace.append("Nano found on " + USBserialPort )
        if portFound == False:
            self.boldLine(displayOutputPlace,"Arduino port not found in scan")
            return None
        else: 
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m328p -P " + maybePort + " -c arduino -b 57600 -F"
            return commandAvrDude


    def boldLine(self, displayOutputPlace, txt):
        font=displayOutputPlace.currentFont()
        font.setWeight(QFont.Bold)
        displayOutputPlace.setCurrentFont(font)
        displayOutputPlace.append (txt)
        font.setWeight(QFont.Normal)
        displayOutputPlace.setCurrentFont(font)
