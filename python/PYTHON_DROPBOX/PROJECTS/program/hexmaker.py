#!/usr/bin/env python
# -*- coding: utf-8 -*-

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

class hexMaker():
    
    def __init__(self,opSys):#bring in all the things being sent down here
        self.opSys = opSys
        
    def saveCfileAndCompile(self,C_txt,displayOutputPlace,currentHW):
        import subprocess
        from subprocess import PIPE
        import sys
        import os
        import time
        from tester import tester
        
        QApplication.setOverrideCursor(QCursor(Qt.WaitCursor))
        #print "current dir:", os.getcwd()
        #os.chdir("../helpers/hexes")
        #print "current dir:", os.getcwd()
        #commands:
        #note: aavrgcc commands are here, but Arduino Avrdude commands are in tester.py
        #LINUX
        if currentHW == "Waltech" and self.opSys == "NIX":
            commandListo = r"../avr/bin/avr-gcc -x c -I. -g -mmcu=atmega32 -DF_CPU=4000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"../avr/bin/avr-gcc  -I. -T ../avr/lib/ldscripts/avr5.x -Wl,-Map,LADDER.out.map  -mmcu=atmega32 -lm -o LADDER.out " 
            commandHex = r"../avr/bin/avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude = r"../avrdude  -C ../avrdude.conf -p m32 -P usb -c usbtiny -B5"

        if currentHW == "ArduinoUno" and self.opSys == "NIX":
            commandListo = r"../avr/bin/avr-gcc -x c -I. -g -mmcu=atmega328 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"../avr/bin/avr-gcc  -I. -T ../avr/lib/ldscripts/avr5.x -Wl,-Map,LADDER.out.map  -mmcu=atmega328 -lm -o LADDER.out " 
            commandHex = r"../avr/bin/avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
            
        if currentHW == "ArduinoNano" and self.opSys == "NIX":
            commandListo = r"../avr/bin/avr-gcc -x c -I. -g -mmcu=atmega328 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"../avr/bin/avr-gcc  -I. -T ../avr/lib/ldscripts/avr5.x -Wl,-Map,LADDER.out.map  -mmcu=atmega328 -lm -o LADDER.out " 
            commandHex = r"../avr/bin/avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
     
        if currentHW == "ArduinoMega" and self.opSys == "NIX":
            commandListo = r"../avr/bin/avr-gcc -x c -I. -g -mmcu=atmega2560 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"../avr/bin/avr-gcc  -I. -T ../avr/lib/ldscripts/avr6.x -Wl,-Map,LADDER.out.map  -mmcu=atmega2560 -lm -o LADDER.out " 
            commandHex = r"../avr/bin/avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
            
        #MAC
        if currentHW == "Waltech" and self.opSys == "MAC":
            commandListo = r"avr-gcc -x c -I. -g -mmcu=atmega32 -DF_CPU=4000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"avr-gcc  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega32 -lm -o LADDER.out " 
            commandHex = r"avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude = r"avrdude  -C ../avrdude.conf -p m32 -P usb -c usbtiny -B5"
        if currentHW == "ArduinoUno" and self.opSys == "MAC":
            commandListo = r"avr-gcc -x c -I. -g -mmcu=atmega328 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"avr-gcc  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega328 -lm -o LADDER.out " 
            commandHex = r"avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
            
        if currentHW == "ArduinoNano" and self.opSys == "MAC":
            commandListo = r"avr-gcc -x c -I. -g -mmcu=atmega328 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"avr-gcc  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega328 -lm -o LADDER.out " 
            commandHex = r"avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
       
        if currentHW == "ArduinoMega" and self.opSys == "MAC":
            commandListo = r"avr-gcc -x c -I. -g -mmcu=atmega2560 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut = r"avr-gcc  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega2560 -lm -o LADDER.out " 
            commandHex = r"avr-objcopy -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
       
        #WINDOWS
        if currentHW == "Waltech" and self.opSys == "WIN":
            commandListo = r"..\\WinAVR\\bin\\avr-gcc.exe -x c -I. -g -mmcu=atmega32 -DF_CPU=4000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut =r"..\\WinAVR\\bin\\avr-gcc.exe  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega32 -lm -o LADDER.out " 
            commandHex = r"..\\WinAVR\\bin\\avr-objcopy.exe -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude = r"..\\WinAVR\\bin\\avrdude.exe -p m32 -P usb -c usbtiny -B5"
        if currentHW == "ArduinoUno" and self.opSys == "WIN":
            commandListo = r"..\\WinAVR\\bin\\avr-gcc.exe -x c -I. -g -mmcu=atmega328 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut =r"..\\WinAVR\\bin\\avr-gcc.exe  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega328 -lm -o LADDER.out " 
            commandHex = r"..\\WinAVR\\bin\\avr-objcopy.exe -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
        if currentHW == "ArduinoNano" and self.opSys == "WIN":
            commandListo = r"..\\WinAVR\\bin\\avr-gcc.exe -x c -I. -g -mmcu=atmega328 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut =r"..\\WinAVR\\bin\\avr-gcc.exe  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega328 -lm -o LADDER.out " 
            commandHex = r"..\\WinAVR\\bin\\avr-objcopy.exe -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
            
        if currentHW == "ArduinoMega" and self.opSys == "WIN":
            commandListo = r"..\\WinAVR\\bin\\avr-gcc.exe -x c -I. -g -mmcu=atmega2560 -DF_CPU=16000000UL -Os -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char -Wall -std=gnu99 -Wa,-ahlms=LADDER.lst -c "
            commandOut =r"..\\WinAVR\\bin\\avr-gcc.exe  -I. -Wl,-Map,LADDER.out.map  -mmcu=atmega2560 -lm -o LADDER.out " 
            commandHex = r"..\\WinAVR\\bin\\avr-objcopy.exe -j .text -j .data -O ihex LADDER.out LADDER.hex"
            commandAvrDude =tester(self.opSys,currentHW).test1(displayOutputPlace)
            
#####run commands:   
        
        print "current dir:", os.getcwd()
        os.chdir("../helpers/hexes")
        print "current dir:", os.getcwd()
        
        f = open('LLCode', 'w')
        f.write(C_txt)
        f.close()   # file is not immediately deleted because we used delete=False
        filename = 'LLCode'
      
        commandwfile = commandListo
        commandwfile = commandwfile + filename
        print commandwfile
        
        #p = subprocess.Popen(commandwfile, shell=True, cwd=r"./hexes")#linux
        p = subprocess.Popen(commandwfile, shell=True)
        while p.poll() is None:# polls to see if the programming is done
            time.sleep(0.5)
        print "Process ended, ret code", p.returncode
        #displayOutputPlace.clear()
        if p.returncode != 0:
            displayOutputPlace.append ("lst and o failed")
        if p.returncode == 0:
            displayOutputPlace.append ( ".lst and .o file generated")
        
        commandwfile =commandOut + filename + ".o"
        p = subprocess.Popen(commandwfile, shell=True )
        while p.poll() is None:# polls to see if the programming is done
            time.sleep(0.5)
        #print "Process ended, ret code:", p.returncode
        if p.returncode != 0:
            displayOutputPlace.append ( "out file failed")
        if p.returncode == 0:
           displayOutputPlace.append ( "out file generated")
        
        
        commandwfile = commandHex      
        p = subprocess.Popen(commandwfile, shell=True)
        while p.poll() is None:# polls to see if the programming is done
            time.sleep(0.5)
        #print "Process ended, ret code:", p.returncode
        if p.returncode != 0:
            displayOutputPlace.append ( "hex file failed")
        if p.returncode == 0:
            displayOutputPlace.append ( "hex file generated")
        

        if commandAvrDude != None:
            displayOutputPlace.append ( "checking port and programming")
            commandwfile = commandAvrDude+" -U flash:w:LADDER.hex:i"
            print "command", commandwfile
            p = subprocess.Popen(commandwfile, shell=True, stdout=PIPE, stderr=PIPE)
            while p.poll() is None:# polls to see if the programming is done
                time.sleep(0.5)
            print "P outut:", p.communicate() 
            if p.returncode != 0:
                displayOutputPlace.append ( "upload failed")
            if p.returncode == 0:
                displayOutputPlace.append ( "Hex file uploaded")
            else: print( "progrmming error")
            """
            #p = subprocess.Popen(commandwfile,stdout = subprocess.PIPE, stderr= subprocess.PIPE,shell=True).communicate()
               
            #output,error =p
            #print"avrdude errstream", error
            """
        if commandAvrDude == None:
            displayOutputPlace.append ("Hardware: "+currentHW+" Not found")
        #delete all temp files:
        os.unlink(f.name)
        
        import os
        import shutil
        #delete temp files:
        if "hexes" in os.getcwd():

            for root, dirs, files in os.walk("./"):
                for f in files:
                    os.unlink(os.path.join(root, f))
                for d in dirs:
                    shutil.rmtree(os.path.join(root, d))
            time.sleep(1)
        else: print "in wrong place, not deleting!"
        QApplication.restoreOverrideCursor()
        os.chdir("../")
        os.chdir("../")
        print "current dir:", os.getcwd()
        os.chdir("./program")
        print "current dir:", os.getcwd()