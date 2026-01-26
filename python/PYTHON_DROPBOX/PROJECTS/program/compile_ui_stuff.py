#import /usr/share/pyshared/PyQt4/uic/pyuic
#/usr/share/pyshared/PyQt4/uic/pyuic.py -x mainwindow.ui -o mainwindow_ui.py

import subprocess
from subprocess import call
import os


print "mainwindow .ui to .py:",
call("pyuic4 -x mainwindow.ui -o mainwindow_ui.py", shell=True)
print "done."

print "USBHelp .ui to .py:",

call("pyuic4 -x USBHelp.ui -o USBHelp_ui.py", shell=True) 
print "done."

print "IOHelp .ui to .py:",
call("pyuic4 -x IOHelp.ui -o IOHelp_ui.py", shell=True) 
print "done."

print "ardIOnote .ui to .py:",
call("pyuic4 -x ardIOnote.ui -o ardIOnote_ui.py", shell=True) 
print "done."

print "coil .ui to .py:",
call("pyuic4 -x coil.ui -o coil_ui.py", shell=True) 
print "done."

print "contact .ui to .py:",
call("pyuic4 -x cont.ui -o cont_ui.py", shell=True) 
print "done."

print "edge .ui to .py:",
call("pyuic4 -x counter.ui -o counter_ui.py", shell=True) 
print "done."

print "timer .ui to .py:",
call("pyuic4 -x timer.ui -o timer_ui.py", shell=True) 
print "done."

print "counter .ui to .py:",
call("pyuic4 -x edge.ui -o edge_ui.py", shell=True) 
print "done."

print "compair .ui to .py:",
call("pyuic4 -x compair.ui -o compair_ui.py", shell=True) 
print "done."

print "math .ui to .py:",
call("pyuic4 -x math.ui -o math_ui.py", shell=True) 
print "done."

print "move .ui to .py:",
call("pyuic4 -x move.ui -o move_ui.py", shell=True) 
print "done."

print "PWM .ui to .py:",
call("pyuic4 -x PWM.ui -o PWM_ui.py", shell=True) 
print "done."

print "ADC .ui to .py:",
call("pyuic4 -x ADC.ui -o ADC_ui.py", shell=True) 
print "done."

print "wrongVersion .ui to .py:",
call("pyuic4 -x wrongVersion.ui -o wrongVersion_ui.py", shell=True) 
print "done."

#os.chdir("./icons")

print "compile icons:",
call("pyrcc4 "+"toolbaricons.qrc "+"-o toolbaricons_rc.py", shell=True) 
print "done."

"""
#for older linux
print "mainwindow .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x mainwindow.ui -o mainwindow_ui.py", shell=True) 
print "done."

print "USBHelp .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x USBHelp.ui -o USBHelp_ui.py", shell=True) 
print "done."

print "IOHelp .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x IOHelp.ui -o IOHelp_ui.py", shell=True) 
print "done."

print "ardIOnote .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x ardIOnote.ui -o ardIOnote_ui.py", shell=True) 
print "done."

print "coil .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x coil.ui -o coil_ui.py", shell=True) 
print "done."

print "contact .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x cont.ui -o cont_ui.py", shell=True) 
print "done."

print "edge .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x counter.ui -o counter_ui.py", shell=True) 
print "done."

print "timer .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x timer.ui -o timer_ui.py", shell=True) 
print "done."

print "counter .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x edge.ui -o edge_ui.py", shell=True) 
print "done."

print "compair .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x compair.ui -o compair_ui.py", shell=True) 
print "done."

print "math .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x math.ui -o math_ui.py", shell=True) 
print "done."

print "move .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x move.ui -o move_ui.py", shell=True) 
print "done."

print "PWM .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x PWM.ui -o PWM_ui.py", shell=True) 
print "done."

print "ADC .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x ADC.ui -o ADC_ui.py", shell=True) 
print "done."

print "wrongVersion .ui to .py:",
call("python "+"/usr/share/pyshared/PyQt4/uic/pyuic.py "+"-x wrongVersion.ui -o wrongVersion_ui.py", shell=True) 
print "done."

#os.chdir("./icons")

print "compile icons:",
call("pyrcc4 "+"toolbaricons.qrc "+"-o toolbaricons_rc.py", shell=True) 
print "done."
"""

#os.chdir("..")

#Note: to get svg to work in windows:
#In application directory, create /imageformats/ directory and put qsvg4.dll



