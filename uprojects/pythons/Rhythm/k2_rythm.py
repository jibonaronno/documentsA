#!/usr/bin/python3
import sys
import enum
from os.path import join, dirname, abspath
import queue
import serial
import serial.tools.list_ports as port_list
from qtpy import uic
from qtpy.QtCore import Slot, QTimer, QThread, Signal, QObject, Qt
from qtpy.QtWidgets import QApplication, QMainWindow, QMessageBox, QAction, QDialog, QTableWidgetItem, QLabel
from pyqtgraph import PlotWidget
import pyqtgraph as pg
from collections import deque
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5 import QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QGroupBox, QPushButton, QTableWidget

import math
import os
import numpy as np
import random
import qtmodern.styles
import qtmodern.windows
import time
import json
import pprint

from gcodegenerator import GcodeGenerator
from dispatchers import PrimaryThread, WorkerThread, SensorThread, BipapThread, EncoderThread, BipapInitializationThread
from kalmanlib import kalman
from flowprocess import FlowProcess
from wavegenerator import WaveMapper
from startdialog import StartDialog
from portdetection import DetectDevices
from backfeed import Backfeed
from modes import MachineRunModes, BipapReturns, BipapLookup
from machinesetup import MachineSetup
from math import pi, sin
from PyQt5.QtMultimedia import *
from datalogger import DataLogger
import struct
#import RPi.GPIO as GPIO
from time import sleep
import pyautogui


_UI = join(dirname(abspath(__file__)), 'VentUI.ui')

_listselect = join(dirname(abspath(__file__)), 'listselect.ui')

_volumes = join(dirname(abspath(__file__)), 'volumes.ui')

class AlarmTypes(enum.Enum):
    NO_ALARM = 1
    PEAK_PRESSURE = 2

class liveVolumeTable(QWidget):
    def __init__(self, parent=None):
        super(liveVolumeTable, self).__init__(parent)
        self.widget = uic.loadUi(_volumes, self)
        self.widget.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        self.table.setRowCount(1)
        self.table.setColumnCount(2)
        self.vols = JsonSettings('volumes.json')
        self.load_json()

    def load_json(self, file='volumes.json'):
        idx = 0
        for key,value in self.vols.dict.items():
            self.table.setItem(idx, 0, QTableWidgetItem(str(key)))
            self.table.setItem(idx, 1, QTableWidgetItem(str(value)))
            
            idx += 1
            self.table.insertRow(idx)
        pass

class ListSelect(QWidget):
    def __init__(self, parent=None):
        super(ListSelect, self).__init__(parent)
        self.widget = uic.loadUi(_listselect, self)
        self.widget.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        self.Mode = 'BiPAP'

    def changeSelection(self):
        cnt = self.lstOptions.count()
        idx = self.lstOptions.row(self.lstOptions.currentItem())
        idx += 1
        if idx < cnt:
            pass
        else:
            idx = 0
        self.lstOptions.setCurrentRow(idx)
        self.Mode = self.lstOptions.currentItem().text()

    def closeEvent(self, event):
        pass

try:
    import RPi.GPIO as GPIO
except:
    print('RPi.GPIO Platform Missmatch')

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        #startdlg = StartDialog(None)
        
        self.tableHeaders = ['VT', 'I:E', 'RR', 'FIO2']
        self.widget = uic.loadUi(_UI, self)

        self.modeSelectionVisible = False
        self.modeselectwidget = ListSelect()
        self.modeselectwidget.lstOptions.addItem('BiPAP')
        self.modeselectwidget.lstOptions.addItem('CMV')

        self.volstable = liveVolumeTable()
        
        window_title = "Rhythm"
        self.setWindowTitle(window_title)
        self.json = JsonSettings("settings.json")
        self.settings_dict = self.json.dict
        pprint.pprint(self.settings_dict)

        self.wave = WaveMapper()
        
        # Setting up Runmode for BiPAP. Call a cyclic function in LungSensorData(...) BipapLookup.lookUp(pressure)
        # This function will return BipapReturns.Continue or BipapReturns.Stop
        self.runMode = MachineRunModes.BiPAP
        self.ipap = 0.0
        self.bipapReturns = BipapReturns.Continue
        self.bipapLookup = BipapLookup()
        self.lst = []

        self.vt = (self.vtdial.value() * 50) + 200
        self.ie = self.iedial.value()
        self.rr = self.rrdial.value()
        self.fio2 = self.fiodial.value()

        self.epap = 0.5
        

        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2, self.vt_adjust)

        self.loadMachineSetup(self.generator)

        self.pulseData = deque()

        self.lungpressuredata = deque()
        self.lungpressurepeakdata = deque()
        self.peeppressuredata = deque()
        self.peeppressurepeakdata = deque()
        self.kalmandata = deque()
        self.kalmanofpressuredata = deque()
        self.voldata = deque()
        self.volpeakdata = deque()
        self.sumofvolume = 0.0

        self.dvdata_compressed = deque()
        self.dvdata = deque()
        self.deriv_points = deque()
        self.timesnap = 0.0
        self.tic = 0.0

        pg.setConfigOptions(antialias=True)

        self.lungpressure_line_pen = pg.mkPen(200, 100, 0)
        self.plotter = PlotWidget()
        self.plotter.showGrid(x=True, y=True, alpha=None)
        #self.plotter.setTitle("Pressure : mb")
        self.plotter.setLabel('left','Pressure : mb')
        #self.plotter.getViewBox().enableAutoRange(axis='y', enable=False)
        self.plotter.getViewBox().setYRange(-2, 30)
        self.curve1 = self.plotter.plot(0,0,"lungpressure", 'b')
        #self.curve2 = self.plotter.plot(0,0,"peakpressure", pen = self.lungpressure_line_pen)
        self.kalmanpen = pg.mkPen(100, 100, 100, 100)
        self.curve3 = self.plotter.plot(0,0, "kalman", pen = self.kalmanpen)

        self.pulsepen = pg.mkPen(255, 200, 0)
        self.pulseCurve = self.plotter.plot(0,0, "pulsecurve", pen=self.pulsepen)

        self.derivative_pen = pg.mkPen(0,200,200, 100)
        self.derivative_pen_in = pg.mkPen(10, 200, 10)
        self.derivative_pen_out = pg.mkPen(10, 200, 200)
        #self.dvcurve = self.plotter.plot(0,0,"dvcurve", pen = self.derivative_pen)

        self.flowpen = pg.mkPen(200, 200, 10)

        self.inhale_t_count = 0
        self.inhale_t = 0
        self.exhale_t = 0
        self.exhale_t_count = 0
        self.flag_idle = True
        self.idle_count = 0

        #self.dvcurve.setPen()

        self.flowplotter = PlotWidget()
        self.flowplotter.showGrid(x=True, y=True, alpha=None)
        #self.flowplotter.setTitle("Flow L/M")
        self.flowplotter.setLabel('left', 'Flow L/M')
        #self.flowplotter
        #self.flowplotter.getViewBox().enableAutoRange(axis='y', enable=False)
        #self.flowplotter.getViewBox().setMinimumHeight(45)
        #self.flowplotter.getViewBox().setYRange(-5, 5)

        self.dvcurve = self.flowplotter.plot(0,0,"dvcurve", pen = self.derivative_pen)
        self.flowcurve = self.flowplotter.plot(0,0,"flowcurve", pen = self.flowpen)
        self.flowpeakcurve = self.flowplotter.plot(0,0,"flowpeakcurve", pen = self.derivative_pen)
        

        self.flowdata = deque()
        self.flowpeakdata = deque()
        self.flowmindata = deque()

        self.volplotter_pen = pg.mkPen(200, 20, 10)
        self.volplotter = PlotWidget()
        self.volplotter.showGrid(x=True, y=True, alpha=None)
        #self.volplotter.setTitle("Volume ml")
        self.volplotter.setLabel('left', 'Volume ml')
        ##self.volplotter.getViewBox().enableAutoRange(axis='y', enable=False)
        ##self.volplotter.getViewBox().setYRange(-10, 500)
        self.volcurve = self.volplotter.plot(0,0,"volcurve", self.volplotter_pen)
        self.volpeakcurve = self.volplotter.plot(0,0,"volpeakcurve", self.volplotter_pen)
        
        ###self.CalculateSettings()
        self.verticalLayout_2.addWidget(self.plotter)
        self.verticalLayout_2.addWidget(self.flowplotter)
        self.verticalLayout_2.addWidget(self.volplotter)
        #self.plotter.hide()
        #self.flowplotter.hide()
        self.volplotter.hide()

        self.show_hide_LeftPanel()
        #self.infoStack.hide()
        self.controlStack.hide()
        self.controls_show_hide = False

        self.gcodetable = QTableWidget(self)
        self.gcodetable.setRowCount(1)
        self.gcodetable.setColumnCount(1)
        #self.verticalLayout_2.addWidget(self.gcodetable)

        self.hbox = QHBoxLayout()
        #self.verticalLayout_2.addChildLayout(self.hbox)
        self.verticalLayout_2.addLayout(self.hbox)
        self.hbox.addWidget(self.gcodetable)
        self.txrxtable = QTableWidget()
        self.txrxtable.setRowCount(1)
        self.txrxtable.setColumnCount(1)
        self.gcodetable.hide()
        self.txrxtable.hide()
        self.txrxtablevisible = False
        self.hbox.addWidget(self.txrxtable)

        self.flowprocess = FlowProcess()
        print("D_ratio : " + str(self.flowprocess.diameter_ratio))
        print("orifice area : " + str(self.flowprocess.orifice_area))
        print("inlet area : " + str(self.flowprocess.inlet_area))
        print("Korifice : " + str(self.flowprocess.Korifice))
        print('CDD : ' + str(self.flowprocess.CDD))

        #self.bipap = BipapThread("", self.generator)
        self.pressureque = queue.Queue()
        self.bipap_init_threadcreated = False
        self.bipapthreadcreated = False

        self.ipapdial.valueChanged.connect(self.ipapDialChanged)
        self.ipaplcd.display(self.ipapdial.value())
        self.epapdial.valueChanged.connect(self.epapDialChanged)
        self.epaplcd.display(self.epapdial.value())
        self.iedial_bipap.valueChanged.connect(self.iedial_bipapChanged)
        self.elcd_bp.display(self.iedial_bipap.value())
        self.rrdial_bipap.valueChanged.connect(self.rrdial_bipapChanged)
        self.rrlcd_bp.display(self.rrdial_bipap.value())

        self.modecombobox.currentIndexChanged.connect(self.modeselectionchanged)
        self.peepdial.valueChanged.connect(self.peepDialChanged)
        self.peeplcd.display(self.peepdial.value())
        self.peakdial.valueChanged.connect(self.peakDialChanged)
        self.peaklcd.display(self.peakdial.value())
        self.vtdial.valueChanged.connect(self.vtDialChanged)
        self.vtlcd.display((self.vtdial.value() * 50) + 200)
        self.iedial.valueChanged.connect(self.ieDialChanged)
        self.ielcd.display(self.iedial.value())
        self.rrdial.valueChanged.connect(self.rrDialChanged)
        self.rrlcd.display(self.rrdial.value())
        self.fiodial.valueChanged.connect(self.fioDialChanged)
        self.fiolcd.display(self.fiodial.value())
        self.lowpdial.valueChanged.connect(self.lowpDialChanged)
        self.lowplcd.display(self.lowpdial.value())
        self.peeplcd.display(self.peepdial.value())
        self.himinitdial.valueChanged.connect(self.himinitDialChanged)
        self.himinitlcd.display(self.himinitdial.value())
        self.lowminitdial.valueChanged.connect(self.lowminitDialChanged)
        self.lowminitlcd.display(self.lowminitdial.value())
        self.alarm.hide()
        self.startpush.hide()
        self.btnhault.hide()
        self.portsList.hide()
        self.monitoringPort.hide()
        self.scanPorts.hide()
        self.connect.hide()
        self.disconnect.hide()
        #self.btnstream.hide()

        self.kalman = kalman(1.2)
        self.kalmanpressure = kalman(2.0)

        #self.vtdial.setStyleSheet("{ background-color: rgb(20,20,20) }")

        self.AlarmNumber = AlarmTypes.NO_ALARM

        self.serialMarlin = ""
        self.serialSensor = ""
        self.serialEncoder = ""
        self.ports = list(port_list.comports())

        self.bipapthreadcreated = False

        self.primaryThreadCreated = False
        self.workerThreadCreated = False
        self.sensorThreadCreated = False
        self.encoderThreadCreated = False
        self.marlinPortOpen = False
        self.sensorPortOpen = False
        self.EncoderPortOpen = False
        self.gengcode.hide()
        self.childrenMakeMouseTransparen()

        self.datalogger = DataLogger()
        self.log_interval_count = 0

        self.strtx = "<D,10," + str(self.peepdial.value()) + ".0>\r\n"
        self.flag_sensorlimit_tx = False
        self.sensorLimitTimer = QTimer(self)
        self.sensorLimitTimer.timeout.connect(self.checkSensorLimitChanged)

        self.sensorwatchtimer = QTimer(self)
        self.sensorwatchtimer.timeout.connect(self.reconnectSensor)

        self.lungtimer = QTimer(self)
        self.lungtimer.timeout.connect(self.lungtimeout)

        self.pulseTimer = QTimer(self)

        self.modecombobox.addItem("BiPAP")
        self.modecombobox.addItem("CMV")
        self.modecombobox.addItem("PS")

        self.ComPorts = {'Marlin':'NA', 'Sensor':'NA', 'Encoder':'NA'}
        self.selected_ports = []

        #self.ComPorts['Marlin'] = "COM16"
        #self.ComPorts['Sensor'] = "COM5"
        #self.ComPorts['Marlin'] = "ttyACM0"
        #self.ComPorts['Sensor'] = "ttyACM1"
        
        '''
        self.automatePorts()
        pprint.pprint(self.ComPorts)

        if self.ComPorts['Sensor'] == 'NA':
            self.showdialog("Sensor Controller")

        if self.ComPorts['Marlin'] == 'NA':
            self.showdialog("Motion Controller")
        else:
            self.autoConnect()
        '''

        self.devices = DetectDevices()
        # print("All Ports: ")
        #self.devices.printPorts()
        print("USB Ports: ")
        self.devices.printUsbPorts()
        print("\r\n")
        self.devices.detectCustomBoards()
        print('Marlin Port : ' + self.devices.MarlinPort[0])
        print('Encoder Port : ' + self.devices.EncoderPort[0])
        print('Sensor Port : ' + self.devices.SensorPort[0])

        self.ComPorts['Marlin'] = self.devices.MarlinPort[0]
        self.ComPorts['Encoder'] = self.devices.EncoderPort[0]
        self.ComPorts['Sensor'] = self.devices.SensorPort[0]

        self.autoConnect()
        

        '''
        if self.ComPorts['Marlin'] == 'NA':
            self.showdialog("Motion Controller")
        else:
            self.autoConnect()
        '''

        self.breath_in_tick = False # flag to play the breath in wave file for only once
        self.sensorLimitTimer.start(1000)

        self.enc_elements = []
        self.addEncoderElements()

        self.flow_average:float = 0.0
        self.flowavgcount:int = 0

        self.plot_run = True

        self.pulseTimer.timeout.connect(self.pulseGen)
        self.pulse_state = 0
        self.pulseTimer.setSingleShot(True)
        #self.pulseTimer.start(0.95)
        self.pulsegencounter = 0

        self.breathInMinTimer = QTimer()
        self.breathInMinTimer.setSingleShot(True)
        self.breathInState = False
        self.breathInMinTimer.timeout.connect(self.BreathInOver)

        self.plottingBaseTimer = QTimer()
        self.plottingBaseTimer.timeout.connect(self.plotTimer)
        ###self.plottingBaseTimer.start(0.025)

        self.alarm_show = False
        self.label_alarm.hide()
        self.alarms:list = []
        self.alarmTimer = QTimer()
        self.alarmTimer.timeout.connect(self.ShowHideAlarm)
        self.alarmTimer.start(1000)
        self.lowp_alarm_enable = False
        self.breathfail_alarm_enable = False

        self.msgwindow = MessageWindow(['ALARM', ''])

        self.blinkpin = 16

        try:
            GPIO.setmode(GPIO.BOARD)
            GPIO.setup(self.blinkpin, GPIO.OUT)
        except:
            print('GPIO.setmode(GPIO.BCM) Platform Missmatch')

        self.flagBlinkState = False
        self.watchdogtimer = QTimer()
        self.watchdogtimer.timeout.connect(self.blink)
        self.watchdogtimer.start(90)

        #self.markerPeakPressure = pg.TextItem(html='<div style="text-align: center"><span style="color: #FFF;">This is the</span><br><span style="color: #FF0; font-size: 16pt;">PEAK</span></div>', anchor=(-0.3,0.5), angle=45, border='w', fill=(0, 0, 255, 100))

        self.labelSelectedMode()
        self.auxMode = MachineRunModes.BiPAP

    #On Mode Changed
    def labelSelectedMode(self):
        if 'BiPAP' in self.modeselectwidget.Mode:
            self.lblMode.setText('BiPAP')
            self.auxMode = MachineRunModes.BiPAP
            self.show_hide_vtdial(False)
            self.lblPressure.setText('IPAP')
            self.lblPeep.setText('EPAP')
        elif 'CMV' in self.modeselectwidget.Mode:
            self.lblMode.setText('CMV')
            self.auxMode = MachineRunModes.CMV
            self.show_hide_vtdial(True)
            self.lblPressure.setText('LPeak')
            self.lblPeep.setText('PEEP')

    def show_hide_vtdial(self, sh):
        if sh:
            self.vtdial.show()
            self.vtlcd.show()
            self.lblVt.show()
            self.labelipap.hide()
            self.ipapdial.hide()
            self.ipaplcd.hide()
        else:
            self.vtdial.hide()
            self.vtlcd.hide()
            self.lblVt.hide()
            self.labelipap.show()
            self.ipapdial.show()
            self.ipaplcd.show()


    flagStartPulse = False

    def blink(self):
        if self.flagBlinkState:
            self.flagBlinkState = False
            try:
                GPIO.output(self.blinkpin, GPIO.HIGH)
            except Exception as e:
                pass
                #print('Exception GPIO.output(HIGH) ' + str(e))
            finally:
                pass
                #print("clean up1") 
                #GPIO.cleanup() # cleanup all GPIO 
        else:
            self.flagBlinkState = True
            try:
                GPIO.output(self.blinkpin, GPIO.LOW)
            except Exception as e:
                pass
                #print('Exception GPIO.output(LOW) ' + str(e))
            finally:
                pass
                #print("clean up2") 
                #GPIO.cleanup() # cleanup all GPIO 

    def ShowHideAlarm(self):
        if self.lowp_alarm_enable or self.breathfail_alarm_enable:
            if self.alarm_show:
                self.alarm_show = False
                self.label_alarm.hide()
                self.msgwindow.hide()
            else:
                self.alarm_show = True
                self.label_alarm.show()
                self.msgwindow.show()
        else:
            self.label_alarm.hide()
            self.msgwindow.hide()

    def BreathInOver(self):
        self.breathInState = False

    def plotTimer(self):
        if self.sensorDataString != '':
            pass
            #self.LungSensorData(self.sensorDataString, 0.025)

    def pulseGen(self):
        if self.flagStartPulse:
            if self.pulsegencounter >= 10:
                self.pulsegencounter = 0
                if self.pulse_state == 0:
                    self.pulse_state = 1
                    #self.pulseTimer.start(0.1)
                else:
                    self.pulse_state = 0
            else:
                self.pulsegencounter += 1

    def lungtimeout(self):
        self.label_alarm.setText("Alarm: Flow Sequence Missing")
        self.wave.playBeep()
        self.lungtimer.setInterval(8000)
        self.breathfail_alarm_enable = True


    
    
    def reconnectSensor(self):
        pass
        '''
        self.sensorwatchtimer.stop()
        if self.sensorThreadCreated:
            self.sensor.Stop()
            self.sensorThread.exit()
            self.sensorThread.wait()
            self.sensorThreadCreated = False
            if self.sensorPortOpen:
                self.serialSensor.close()
                time.sleep(1)
        self.autoConnect()
        self.on_btninit_clicked()
        self.sensorwatchtimer.start(500)
        '''

    enc_focus_index = 0
    def addEncoderElements(self):
        self.enc_elements.append(self.btninit)
        self.enc_elements.append(self.runloop)
        self.enc_elements.append(self.btnstopcmv)
        self.enc_elements.append(self.gcodeshow)
        self.enc_elements.append(self.btnalarmpage)
        self.enc_elements.append(self.btnmachinesetup)
        self.enc_elements.append(self.alarm)
        self.enc_elements.append(self.btnchangeset)

    def encrFocus(self, value=1):
        if value == 1:
            self.enc_focus_index += 1
            print("Focus Index : " + str(self.enc_focus_index))
            pyautogui.press('\t')
            if self.enc_focus_index < len(self.enc_elements):
                self.enc_elements[self.enc_focus_index].setFocus()
        elif value == 0:
            pyautogui.keyDown('shift')
            pyautogui.press('\t')
            pyautogui.keyUp('shift')

    def showdialog2(self, msg):
        d = QDialog()
        b1 = QPushButton("ok",d)
        b1.move(50,50)
        d.setWindowTitle(msg)
        d.setWindowModality(Qt.ApplicationModal)
        d.exec_()

    def showdialog(self, msgstr):
        msg = QMessageBox()
        msg.setIcon(QMessageBox.Information)
        msg.setText(msgstr + "Controller Not Connected")
        msg.setInformativeText(msgstr + "Controller Not Connected")
        msg.setWindowTitle("Controller Error")
        msg.setStandardButtons(QMessageBox.Ok)
        msg.exec_()

    def pauseVentilator(self):
        if self.workerThreadCreated:
            self.worker.Stop()

    def resumeVentilator(self):
        if self.workerThreadCreated:
            self.worker.Resume()

    def loadMachineSetup(self, generator):
        self.t_acc.setText(str(generator.ACC))
        self.t_xmax.setText(str(generator.xmax))
        self.t_xamb.setText(str(generator.xamb))
        self.t_xrect.setText(str(generator.xrect))
        self.t_xconoffset.setText(str(generator.xcon_offset))
        self.t_vtmax.setText(str(generator.vtmax))

    # @Slot()
    # def on_btncmv_clicked(self):
    #     self.buttonstack.setCurrentIndex(0)
    #     pass

    # @Slot()
    # def on_btnbipap_clicked(self):
    #     self.buttonstack.setCurrentIndex(1)
    #     pass

    left_panel_visible = True

    def show_hide_LeftPanel(self):
        if self.left_panel_visible:
            self.stackedWidget_2.hide()
            self.left_panel_visible = False
        else:
            self.left_panel_visible = True
            self.stackedWidget_2.show()

    def onEncoderValue(self, msg):
        if self.runMode == MachineRunModes.BiPAP:
            parts = None
            value = 2
            if len(msg) <= 7:
                parts = msg.split(':')
                if len(parts) > 1:
                    if parts[0] == '1':
                        value = int(parts[1])
                        if value < 3:
                            if self.auxMode == MachineRunModes.CMV:
                                self.changeVTdial(value)
                        elif value == 3:
                            if self.workerThreadCreated:
                                if self.worker.flagStop:
                                    self.on_runloop_clicked()
                                    #self.plottingBaseTimer.start(0.025)
                                    #self.pulse_state = True
                                    #self.flagStartPulse = True
                                else:
                                    self.on_btnstopcmv_clicked()
                                    #self.plottingBaseTimer.stop()
                                    #self.pulse_state = False
                                    #self.flagStartPulse = False
                            else:
                                self.modeselectwidget.hide()
                                self.modeSelectionVisible = False
                                self.labelSelectedMode()
                                if self.runloop.isEnabled():
                                    self.on_runloop_clicked()
                    if parts[0] == '2':
                        value = int(parts[1])
                        if value < 3:
                            self.changeIEdial(value)
                        elif value == 3:
                            self.modeselectwidget.hide()
                            self.modeSelectionVisible = False
                            self.labelSelectedMode()
                            self.on_btninit_clicked()
                    if parts[0] == '3':
                        value = int(parts[1])
                        if value < 3:
                            self.changeRRdial(value)
                        elif value == 3:
                            if self.plot_run:
                                self.plot_run = False
                            else:
                                self.plot_run = True
                            #self.emulateSpace()
                    if parts[0] == '4':
                        value = int(parts[1])
                        if value < 3:
                            if not self.modeSelectionVisible:
                                self.changePeakDial(value)
                            else:
                                self.modeselectwidget.changeSelection()
                        elif value == 3:
                            if self.modeSelectionVisible:
                                self.modeselectwidget.hide()
                                self.modeSelectionVisible = False
                                self.labelSelectedMode()
                            elif not self.workerThreadCreated:
                                self.modeselectwidget.show()
                                self.modeSelectionVisible = True
                            ##self.show_hide_LeftPanel()
                    if parts[0] == '5':
                        value = int(parts[1])
                        if value < 3:
                            self.changeBipapdial(value)
                            #self.encrFocus(value)
                        elif value == 3:
                            self.change_set(parts[1])
                            self.change_set_bipap(parts[1])
                            self.ShowHideControls()
                            self.show_hide_LeftPanel()

        elif self.runMode == MachineRunModes.CMV:
            parts = None
            value = 2
            if len(msg) <= 7:
                parts = msg.split(':')
                if len(parts) > 1:
                    if parts[0] == '1':
                        value = int(parts[1])
                        if value < 3:
                            self.changeBipapdial(value)
                        elif value == 3:
                            pass #VT Button Pressed
                    if parts[0] == '2':
                        value = int(parts[1])
                        if value < 3:
                            self.changeEpapDial(value)
                        elif value == 3:
                            pass
                    if parts[0] == '3':
                        value = int(parts[1])
                        if value < 3:
                            self.changeIEdialBipap(value)
                        elif value == 3:
                            pass
                    if parts[0] == '4':
                        value = int(parts[1])
                        if value < 3:
                            self.changeRRdialBipap(value)
                        elif value == 3:
                            self.show_hide_LeftPanel()
                    if parts[0] == '5':
                        value = int(parts[1])
                        if value < 3:
                            self.encrFocus(value)
                        elif value == 3:
                            self.change_set_bipap(parts[1])

    def emulateEnter(self):
        pyautogui.press('enter')

    def emulateSpace(self):
        pyautogui.press(' ')

    def changePeakDial(self, incr=1):
        if self.peakdial.isEnabled():
            self.changedial(incr, self.peakdial)

    def changeBipapdial(self, incr=1):
        if self.ipapdial.isEnabled():
            self.changedial(incr, self.ipapdial)

    def changeEpapDial(self, incr=1):
        if self.epapdial.isEnabled():
            self.changedial(incr, self.epapdial)

    def changeIEdialBipap(self, incr=1):
        if self.iedial_bipap.isEnabled():
            self.changedial(incr, self.iedial_bipap)

    def changeRRdialBipap(self, incr=1):
        if self.rrdial_bipap.isEnabled():
            self.changedial(incr, self.rrdial_bipap)

    def changeVTdial(self, incr = 1):
        if self.vtdial.isEnabled():
            self.changedial(incr, self.vtdial)

    def changeIEdial(self, incr=1):
        if self.iedial.isEnabled():
            self.changedial(incr, self.iedial)

    def changeRRdial(self, incr=1):
        if self.rrdial.isEnabled():
            self.changedial(incr, self.rrdial)

    def changeFIOdial(self, incr=1):
        if self.fiodial.isEnabled():
            self.changedial(incr, self.fiodial)

    def changedial(self, incr = 1, dial=None):
        if dial != None:
            dial_max = dial.maximum()
            dial_min = dial.minimum()
            dial_now = dial.value()
            if(incr == 1):
                if dial_now >= dial_max:
                    return
                else:
                    dial_now += incr
                    dial.setValue(dial_now)
            elif(incr == 0):
                if dial_now <= dial_min:
                    return
                else:
                    dial_now -= 1
                    dial.setValue(dial_now)


    def getStreamData(self, line):
        #print(line)
        self.LungSensorData(line)
        #self.sensorData(line)
        elements = line.split('\t')
        if len(elements) > 2:
            print(str(elements[1]))

    flagEditCmv = False

    def changeCmvParams(self):
        self.vtdial.setEnabled(True)
        self.iedial.setEnabled(True)
        self.rrdial.setEnabled(True)
        self.fiodial.setEnabled(True)
        self.ipapdial.setEnabled(True)
        self.peakdial.setEnabled(True)
        self.btnchangeset.setText("Set")
        self.flagEditCmv = True

    def setCmvParams(self):
        self.vtdial.setEnabled(False)
        self.iedial.setEnabled(False)
        self.rrdial.setEnabled(False)
        self.fiodial.setEnabled(False)
        self.ipapdial.setEnabled(False)
        self.peakdial.setEnabled(False)
        self.btnchangeset.setText("Change")
        self.flagEditCmv = False

    flagEditBipap = False

    def changeBipapParams(self):
        self.ipapdial.setEnabled(True)
        self.epapdial.setEnabled(True)
        self.iedial_bipap.setEnabled(True)
        self.rrdial_bipap.setEnabled(True)
        self.flagEditBipap = True

    def setBipapParams(self):
        self.ipapdial.setEnabled(False)
        self.epapdial.setEnabled(False)
        self.iedial_bipap.setEnabled(False)
        self.rrdial_bipap.setEnabled(False)
        self.flagEditBipap = False

    def change_set_bipap(self, cmd):
        print(cmd)
        if '3' in cmd:
            if self.flagEditBipap:
                self.setBipapParams()
            else:
                self.changeBipapParams()

    def change_set(self, cmd):
        print(cmd)
        if '3' in cmd:
            if self.flagEditCmv:
                self.setCmvParams()
            else:
                self.changeCmvParams()

    def ShowHideControls(self):
        if self.controls_show_hide:
            self.controlStack.hide()
            self.infoStack.show()
            self.controls_show_hide = False
        else:
            self.controlStack.show()
            self.infoStack.hide()
            self.controls_show_hide = True


    @Slot()
    def on_btnInfo_clicked(self):
        self.controlStack.hide()

    @Slot()
    def on_btnVols_clicked(self):
        self.volstable.show()
        pass

    @Slot()
    def on_btnShowHide_clicked(self):
        if self.controls_show_hide:
            self.controlStack.hide()
            self.controls_show_hide = False
            self.modeselectwidget.hide()
        else:
            self.controlStack.show()
            self.controls_show_hide = True
            #self.infoStack.hide()
            self.modeselectwidget.show()

        self.show_hide_LeftPanel()

    @Slot()
    def on_btnpausegraph_clicked(self):
        if self.plot_run:
            self.plot_run = False
        else:
            self.plot_run = True

    @Slot()
    def on_peepdisable_clicked(self):
        self.strtx = "<D,1," + str(self.peepdial.value()) + ".0>\r\n"
        self.flag_sensorlimit_tx = True


    @Slot()
    def on_btnchangeset_clicked(self):
        if self.flagEditCmv:
            self.setCmvParams()
        else:
            self.changeCmvParams()

    #when Stream button pressed.
    @Slot()
    def on_btnstream_clicked(self):
        self.streamer = Backfeed('log4.txt')
        self.streamer.setCallback(self.getStreamData)
        self.streamer.Start(100)
        #following lungtimer is commented for test.
        #self.lungtimer.start(8000) #The timer that alarms if lung peak is not detected within time period
        #self.plotter.addItem(self.markerPeakPressure)

    @Slot()
    def on_btninitbipap_clicked(self):
        if self.sensorPortOpen:
            if not self.sensorThreadCreated:
                self.sensor = SensorThread(self.serialSensor, self.pressureque)
                self.sensorThread = QThread()
                self.sensorThread.started.connect(self.sensor.run)
                self.sensor.signal.connect(self.sensorData)
                self.sensor.moveToThread(self.sensorThread)
                self.sensorThread.start()
                self.sensorThreadCreated = True
                print("Starting Sensor Thread ...")
        if not self.bipap_init_threadcreated:
            if not self.bipapthreadcreated:
                self.bipapinit = BipapInitializationThread(self.serialMarlin, self.generator, self.pressureque)
                self.bipapinitThread = QThread()
                self.bipapinitThread.started.connect(self.bipapinit.run)
                self.bipapinit.signal.connect(self.write_info)
                self.bipapinit.ppsignal.connect(self.endBipap)
                self.bipapinit.moveToThread(self.bipapinitThread)
                self.bipapinitThread.start()
                self.bipap_init_threadcreated = True
                print("Starting bipap_init Thread")

    @Slot()
    def on_btnmachinesetup_clicked(self):
        self.controlStack.setMinimumHeight(230)
        self.controlStack.setCurrentIndex(3)

    @Slot()
    def on_btnsavemachinesetup_clicked(self):
        self.generator.ACC = int(self.t_acc.text())
        self.generator.xmax = int(self.t_xmax.text())
        self.generator.xamb = int(self.t_xamb.text())
        self.generator.xrect = int(self.t_xrect.text())
        self.generator.xcon_offset = int(self.t_xconoffset.text())
        self.generator.vtmax = int(self.t_vtmax.text())
        self.generator.machinesetup.save()

    @Slot()
    def on_gengcode_clicked(self):
        self.CalculateSettings()
        self.generator.GenerateCMV()
        print(self.generator.gcodeprimary)
        self.ShowGcodeTable()

    @Slot()
    def on_scanPorts_clicked(self):
        self.ports = list(port_list.comports())
        self.widget.portsList.clear()
        self.widget.monitoringPort.clear()
        print(len(self.ports))
        for p in self.ports:
            self.widget.portsList.addItem(p[0])
            self.widget.monitoringPort.addItem(p[0])

    @Slot()
    def on_btninit_clicked(self):
        if self.marlinPortOpen:
            if not self.workerThreadCreated:
                if not self.primaryThreadCreated:
                    self.primary = PrimaryThread(self.serialMarlin, self.generator)
                    self.primaryThread = QThread()
                    self.primaryThread.started.connect(self.primary.run)
                    self.primary.signal.connect(self.write_info)
                    self.primary.moveToThread(self.primaryThread)
                    self.primaryThread.start()
                    self.primaryThreadCreated = True
                    print("Starting Primary Thread")
        if self.sensorPortOpen:
            if not self.sensorThreadCreated:
                self.sensor = SensorThread(self.serialSensor, self.pressureque)
                self.sensorThread = QThread()
                self.sensorThread.started.connect(self.sensor.run)
                ##self.sensor.signal.connect(self.sensorData)
                self.sensor.signal.connect(self.LungSensorData)
                self.sensor.moveToThread(self.sensorThread)
                self.sensorThread.start()
                self.sensorThreadCreated = True
                self.sensorwatchtimer.start(500)
                print("Starting Sensor Thread ...")


    def startEncoderThread(self):
        if self.EncoderPortOpen:
            if not self.encoderThreadCreated:
                print('Starting Encoder Thread')
                self.encoder = EncoderThread(self.serialEncoder)
                self.encoderThread = QThread()
                self.encoderThread.started.connect(self.encoder.run)
                self.encoder.signal_pass_encoder.connect(self.on_encoder)
                self.encoder.moveToThread(self.encoderThread)
                self.encoderThread.start()
                self.encoderThreadCreated = True

    def on_encoder(self, data_stream):
        #print(str(data_stream))
        try:
            self.onEncoderValue(data_stream)
        except Exception as e:
            print('Exception At on_encoder() : ' + str(e))

    
    pparr = []

    @Slot()
    def on_btnrunbploop_clicked(self):
        pprint.pprint(self.pparr)
        self.generator.GenerateBiPAP(self.pparr, self.ipapdial.value())
        print(self.generator.gcodestr)
        if not self.primaryThreadCreated:
            if not self.workerThreadCreated:
                self.worker_cmd_que = queue.Queue()
                self.worker = WorkerThread(self.serialMarlin, self.generator, self.worker_cmd_que)
                self.workerThread = QThread()
                self.workerThread.started.connect(self.worker.run)
                self.worker.signal.connect(self.write_info)
                self.worker.moveToThread(self.workerThread)
                self.workerThread.start()
                self.workerThreadCreated = True
                print("Starting Worker Thread")
                

    @Slot()
    def on_runloop_clicked(self):
        if not self.primaryThreadCreated:
            if not self.workerThreadCreated:
                self.worker_cmd_que = queue.Queue()
                self.worker = WorkerThread(self.serialMarlin, self.generator, self.worker_cmd_que)
                self.workerThread = QThread()
                self.workerThread.started.connect(self.worker.run)
                self.worker.signal.connect(self.write_info)
                self.worker.moveToThread(self.workerThread)
                self.workerThread.start()
                self.workerThreadCreated = True
                self.lungtimer.start(8000)
                print("Starting Worker Thread")

            elif self.workerThreadCreated:
                self.worker.Resume()
                self.lungtimer.start(8000)

    @Slot()
    def on_btnstopcmv_clicked(self):
        self.pauseVentilator()
        self.lungtimer.stop()

    @Slot()
    def on_disconnect_clicked(self):
        if self.marlinPortOpen:
            if self.workerThreadCreated:
                self.worker_cmd_que.put("exit")
                self.worker.Stop()
                self.workerThread.exit()
                self.workerThread.wait()
                self.workerThreadCreated = False
                del self.workerThread
            if self.primaryThreadCreated:
                self.primaryThread.exit()
                self.primaryThread.wait()
                self.primaryThreadCreated = False
                del self.primaryThread
            if self.sensorThreadCreated:
                self.sensor.Stop()
                self.sensorThread.exit()
                self.sensorThread.wait()
                self.sensorThreadCreated = False
            if self.bipap_init_threadcreated:
                self.bipapinit.Stop()
                self.bipapinitThread.exit()
                self.bipapinitThread.wait()
                self.bipap_init_threadcreated = False
            self.serialMarlin.close()
            if self.sensorPortOpen:
                self.serialSensor.close()
            self.marlinPortOpen = False
            self.sensorPortOpen = False
            self.connect.setEnabled(True)
            self.disconnect.setEnabled(False)
            self.runloop.setEnabled(False)
            self.btninit.setEnabled(False)

    @Slot()
    def on_btnalarmpage_clicked(self):
        #self.stackedWidget = QStackerWidget()
        self.controlStack.setMinimumHeight(110)
        if self.btnalarmpage.isChecked():
            self.controlStack.setCurrentIndex(1)
        else:
            self.controlStack.setCurrentIndex(0)

    @Slot()
    def on_startpush_clicked(self):
        if not self.bipapthreadcreated:
            self.bipap = BipapThread(self.serialMarlin, self.generator, self.pressureque)
            self.bipapThread = QThread()
            self.bipapThread.started.connect(self.bipap.run)
            #self.bipap.signal.connect(self...)
            self.bipap.moveToThread(self.bipapThread)
            self.bipapThread.start()
            self.bipapthreadcreated = True
            print("Bipap Thread Created")
        self.bipap.StartMoving()
        self.runMode = MachineRunModes.BiPAP

    @Slot()
    def on_connect_clicked(self):
        self.devices.detectCustomBoards()
        self.ComPorts['Marlin'] = self.devices.MarlinPort[0]
        self.ComPorts['Encoder'] = self.devices.EncoderPort[0]
        self.ComPorts['Sensor'] = self.devices.SensorPort[0]
        try:
            self.autoConnect()
        except Exception as ex:
            print('Error From on_connect_clicked')
            pprint.pprint(ex)
        else:
            self.connect.setEnabled(False)
            self.disconnect.setEnabled(True)
            self.btninit.setEnabled(True)

    @Slot()
    def on_gcodeshow_clicked(self):
        if self.txrxtablevisible:
            self.txrxtable.hide()
            self.txrxtablevisible = False
        else:
            self.txrxtablevisible = True
            self.txrxtable.show()
        #self.wave.BeepBeep()
        #self.wave.changeFrequency(1000)
        #self.wave.changeVolume(1000)
        #self.wave.play()

    def SaveSettings(self):
        ###self.json = JsonSettings("settings.json")
        ###self.settings_dict = self.json.dict
        self.json.dict[r'vt'] = str(self.vt)
        self.json.dict[r'ie'] = str(self.ie)
        self.json.dict[r'rr'] = str(self.rr)
        self.json.dict[r'fio2'] = str(self.fio2)
        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2, self.vt_adjust)
        self.generator.GenerateCMV()
        if self.workerThreadCreated:
            self.worker.updateGcode(self.generator)
        pprint.pprint(self.generator.gcodestr)
        #self.CalculateSettings()

    @Slot()
    def on_alarm_clicked(self):
        #self.wave.playin()
        #self.wave.playfile()
        self.wave.playBeep()

    def autoConnect(self):
        try:
            
            if not self.marlinPortOpen:
                if self.ComPorts['Marlin'] != 'NA':
                    print("Serial Port Name : " + self.ComPorts['Marlin'])
                    self.serialMarlin = serial.Serial(self.ComPorts['Marlin'], baudrate=115200, timeout=0)
                    time.sleep(1)
                    self.marlinPortOpen = True
                    while self.serialMarlin.in_waiting:
                        self.serialMarlin.readline()
            
            if self.ComPorts['Sensor'] != 'NA':
                
                if not self.sensorPortOpen:
                    self.serialSensor = serial.Serial(self.ComPorts['Sensor'], baudrate=115200, timeout=0)
                    self.sensorPortOpen = True

            if self.ComPorts['Encoder'] != 'NA':
                if not self.EncoderPortOpen:
                    self.serialEncoder = serial.Serial(self.ComPorts['Encoder'], baudrate=115200, timeout=0)
                    self.EncoderPortOpen = True
                    self.startEncoderThread()
            
        except serial.SerialException as ex:
            self.marlinPortOpen = False
            print(ex.strerror)
            print("Error Opening Serial Port..........................................")
        else:
            self.connect.setEnabled(False)
            self.disconnect.setEnabled(True)
            self.btninit.setEnabled(True)

    def checkSensorLimitChanged(self):
        #strtx = str(self.peakdial.value()) + "," + str(self.lowpdial.value()) + "," + str(self.peepdial.value()) + "," + str(self.himinitdial.value()) + "," + str(self.lowminitdial.value()) + "\r\n"
        #self.strtx = "<peak,12," + str(self.peakdial.value()) + "> "
        if self.sensorThreadCreated:
            if self.flag_sensorlimit_tx:
                #self.strtx = "<D,10," + str(self.peepdial.value()) + ".0>\r\n" # + "," + str(self.lowpdial.value()) + "," + str(self.peepdial.value()) + "," + str(self.himinitdial.value()) + "," + str(self.lowminitdial.value())
                self.sensor.txsensordata(self.strtx)
                print(self.strtx)
                self.flag_sensorlimit_tx = False


    def childrenMakeMouseTransparen(self):
        self.lblVt.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.vtlcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.ilcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.ielcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.rrlcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.fiolcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.label_15.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.label_17.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.label_14.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.label_16.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.peaklcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.peeplcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.lowplcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.lowminitlcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.himinitlcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.ipaplcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.labelipap.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.labelepap.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.ipaplcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.epaplcd.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.label_18.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.label_19.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.ilcd_bp.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.elcd_bp.setAttribute(Qt.WA_TransparentForMouseEvents, True)
        self.rrlcd_bp.setAttribute(Qt.WA_TransparentForMouseEvents, True)

    def modeselectionchanged(self):
        if "BiPAP" in self.modecombobox.currentText():
            self.buttonstack.setCurrentIndex(0)
            self.controlStack.setCurrentIndex(0)
            #self.label.setText("Mode : CMV")
            self.runMode = MachineRunModes.BiPAP
        elif "CMV" in self.modecombobox.currentText():
            self.buttonstack.setCurrentIndex(2)
            self.controlStack.setCurrentIndex(2)
            self.runMode = MachineRunModes.CMV
        elif "PS" in self.modecombobox.currentText():
            #self.label.setText("Mode : PS")
            self.runMode = MachineRunModes.PS

    def iedial_bipapChanged(self):
        self.elcd_bp.display(self.iedial_bipap.value())

    def rrdial_bipapChanged(self):
        self.rrlcd_bp.display(self.rrdial_bipap.value())

    def peepDialChanged(self):
        self.peeplcd.display(self.peepdial.value())
        self.strtx = "<E,10," + str(self.peepdial.value()) + ".0>\r\n"
        self.flag_sensorlimit_tx = True

    def peakDialChanged(self):
        self.peaklcd.display(self.peakdial.value())
        self.flag_sensorlimit_tx = False

    def lowpDialChanged(self):
        self.lowplcd.display(self.lowpdial.value())
        self.flag_sensorlimit_tx = False

    def himinitDialChanged(self):
        self.himinitlcd.display(self.himinitdial.value())
        self.flag_sensorlimit_tx = False

    def lowminitDialChanged(self):
        self.lowminitlcd.display(self.lowminitdial.value())
        self.flag_sensorlimit_tx = False

    def epapDialChanged(self):
        self.epaplcd.display(self.epapdial.value())

    def ipapDialChanged(self):
        self.ipaplcd.display(self.ipapdial.value())
        #self.flag_sensorlimit_tx = False
        #if self.workerThreadCreated:
            #self.generator.GenerateBiPAP(self.pparr, self.ipapdial.value())
            #self.worker.updateGcode(self.generator)


    def vtDialChanged(self):
        self.vt = (self.vtdial.value() * 50) + 200
        self.vtlcd.display(self.vt)
        self.settings_dict[r"vt"] = str(self.vt)
        self.SaveSettings()

    def ieDialChanged(self):
        #self.table.setItem(0,1, QTableWidgetItem(self.settings_dict[r"ie"]))
        self.ielcd.display(self.iedial.value())
        self.ie = self.iedial.value()
        self.settings_dict[r"ie"] = str(self.ie)
        self.SaveSettings()

    def rrDialChanged(self):
        self.rrlcd.display(self.rrdial.value())
        self.rr = self.rrdial.value()
        self.settings_dict[r"rr"] = str(self.rr)
        self.SaveSettings()

    def fioDialChanged(self):
        self.fiolcd.display(self.fiodial.value())
        self.fio2 = self.fiodial.value()
        self.settings_dict[r"fio2"] = str(self.fio2)
        self.SaveSettings()

    
    def ShowGcodeTable(self):
        codelist = self.generator.gcodestr.splitlines()
        rowcount = len(codelist)
        self.gcodetable.setRowCount(rowcount)
        self.gcodetable.setColumnCount(1)
        for i in range(rowcount):
            self.gcodetable.setItem(i, 0, QTableWidgetItem(codelist[i]))

    def CalculateSettings(self):
        del self.generator
        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2, self.vt_adjust)
        self.generator.GenerateCMV()

    def parseSensorData(self, data_stream):
        res = [0.0, 0.0, 0.0]
        lst = data_stream.split(',')
        pressure = 0.0
        if len(lst) >= 3:
            try:
                pressure = float(lst[0])
                res[0] = pressure
                pressure = float(lst[1])
                res[1] = pressure
                pressure = float(lst[2])
                res[2] = pressure
            except Exception as e:
                print('Exception Section (Parse Sensor Data):' + str(e))
                return None
        else:
            return None
        return res

    '''Peak detector for Lung Pressure'''
    from signals import SignalDetector
    lung_detector = SignalDetector()

    vol_detector = SignalDetector()

    flow_detector = SignalDetector()
    
    ttick = 0
    tsnap = 0

    eptick = 0
    epsnap = 0

    from signals import WaveShape
    over_pressure_detection_delay = 0
    dataList = []
    lung_wave = WaveShape()
    vol_wave = WaveShape()

    vtsnap = 0.0
    vtpick = 0.0
    tf = 0.0
    tfdata = deque()
    ttm = 0.0

    flow_sum:float = 0.0
    flow_average:float = 0.0
    flowavgcount:int = 0
    flowoffset:float = 0
    flow_offseted:float = 0.0
    
    zero_flow_count:int = 0
    flow_for_volume:int = 0

    deltaflowsum:float = 0.0

    flag_breath_in_ready = True
    lpzerocount = 0

    sensorDataString = ''

    lungPeakPressure = 0.0
    lungPapPressure = 0.0
    lungLowPressureCount = 0
    lungLowPressureDetected = False

    vt_adjust = 0
    vt_unmatch_count = 0
    
    breath_in_min_time = 1.8

    ipap_deviation = 0.0 ## Lung Pressure Diff from Target Pressure ipapdial
    changefactor = 0.0

    vol_peak = 0.0

    vol_deviation = 0.0
    vol_changefactor = 0.0

    def sensorData(self, data_stream):
        self.sensorDataString = data_stream

    def splitSensorData(self, data_stream):
        pass

    
    def GetChangeFactorFromDeviation(self, deviation):
        if deviation <= 2:
            return 1
        elif deviation <=3:
            return 2
        else:
            return 10

    def GetChangeFactorFromVolDeviation(self, deviation):
        if deviation <= 10:
            return 5
        elif deviation <=15:
            return 8
        else:
            return 12

    volume_band_plus = 0
    volume_band_minus = 0

    def LungSensorData(self, data_stream):
        print(data_stream)
        #Logging the data @ 100 data received
        vol_base = 0.0
        deltaflow:float = 0.0
        deltaflowoffset:float = 0.0

        lungpressure:float = 0.0

        volume:float = 0.0

        if not self.plot_run:
            return

        if self.over_pressure_detection_delay > 0:
            self.over_pressure_detection_delay -= 1
        
        '''
        try:
            self.dataList.append(data_stream)
            self.log_interval_count += 1
            if self.log_interval_count >= 100:
                self.log_interval_count = 0
                self.datalogger.writeBlock(self.dataList)
                self.dataList.clear()
        except Exception as e:
            print('Exception in Log: ' + str(e))
        '''
        
        self.sensorwatchtimer.setInterval(500)
        self.lst = data_stream.split(",")
        if len(self.lst) < 3:
            return

        try:
            lungpressure = float(self.lst[0])
            deltaflow = float(self.lst[2])
            volume = float(self.lst[5])
        except Exception as e:
            print(data_stream)
            return

        self.maxLen = 100  # max number of data points to show on graph
        if(len(self.lst) > 2):
            if len(self.lungpressuredata) > self.maxLen:
                self.lungpressuredata.popleft()  # remove oldest
            if len(self.lungpressurepeakdata) > self.maxLen:
                self.lungpressurepeakdata.popleft()
            if len(self.dvdata) > self.maxLen:
                self.dvdata.popleft()
            if len(self.dvdata_compressed) > self.maxLen:
                self.dvdata_compressed.popleft()
            if len(self.kalmandata) > self.maxLen:
                self.kalmandata.popleft()
            if len(self.volpeakdata) > self.maxLen:
                self.volpeakdata.popleft()
            if len(self.voldata) > self.maxLen:
                self.voldata.popleft()
            if len(self.flowdata) > self.maxLen:
                self.flowdata.popleft()
            if len(self.flowpeakdata) > self.maxLen:
                self.flowpeakdata.popleft()
            if len(self.pulseData) > self.maxLen:
                self.pulseData.popleft()
            if len(self.kalmanofpressuredata) > self.maxLen:
                self.kalmanofpressuredata.popleft()
            #if len(self.tfdata) > self.maxLen:
            #    self.tfdata.popleft()

            if len(self.tfdata) > self.maxLen:
                pass
                #self.tfdata.popleft()
            else:
                self.ttm += 0.1 ###incr
                self.tfdata.append(self.ttm)

            try:
                lungpressure = float(self.lst[0])
                try:
                    self.deriv_points.append([lungpressure, self.timesnap])
                except Exception as e:
                    print('Exception : deriv_points.append()')

                if len(self.deriv_points) >= 0:
                    self.lungpressurepeakdata.append(float(self.peakdial.value()))
                    self.lungpressuredata.append(lungpressure + float(self.peepdial.value()))
                    
                    ## Shift below 2 lines in breath in only logic
                    #self.lung_detector.Cycle(lungpressure)
                    #self.lung_wave.Cycle(lungpressure)

                    try:
                        self.pulseGen()
                        self.pulseData.append(self.pulse_state * 20)
                    except Exception as e:
                        print('Exception : pulseData.append()')

                    self.vtsnap = time.perf_counter() - self.vtsnap
                    self.tf = self.vtsnap
                    #self.tfdata.append(time.perf_counter()) #self.tf * 100)

                    self.vtsnap = time.perf_counter()

                if self.lung_wave.wave_in_buffer:
                    pass
                    #pprint.pprint(self.lung_wave.wvdata)
                    #print(str(max(self.lung_wave.wvdata)))
                try:
                    #self.peak_lung.setText('Lung Peak: ' + '{:03.2f}'.format(self.lung_detector.peak_value) + 'mb')
                    #self.peak_lung.setText('{:03.2f}'.format(self.lung_wave.GetMax() ) + 'mb')
                    if self.auxMode == MachineRunModes.BiPAP:
                        self.peak_lung.setText('{:03.2f}'.format(self.ipap ) + 'mb')
                    else:
                        self.peak_lung.setText('{:03.2f}'.format(self.lungPeakPressure ) + 'mb')
                except:
                    pass
                #if self.lung_detector.peak_value > 5:
                    #self.lungtimer.setInterval(3000)
                ''' Commented for testing '''

                deltaflow = float(self.lst[2])

                ##dflow = self.flowprocess.CalculateFlowConst(deltaflow)
                #-dflow = self.flowprocess.CalculateFlow(deltaflow)
                dflow = deltaflow
                ##dflow = float(self.lst[1]) - self.flow_average

                #print('Delta P : ' + str(deltaflow))
                #print('dflow : ' + str(dflow))
                
                if self.flowavgcount < 100:
                    self.flow_sum += dflow
                    self.flowavgcount += 1
                    vol_base = 0

                    self.deltaflowsum += deltaflow

                else:
                    self.flow_average = self.flow_sum / self.flowavgcount
                    self.flow_offseted = dflow - self.flow_average
                    #deltaflowoffset = self.flow_average
                    self.flow_for_volume = self.flow_offseted

                    deltaflowoffset = self.deltaflowsum / self.flowavgcount
                
                #print('Flow : ' + str(self.flow_offseted))
                if (self.flow_offseted < 0.3 and self.flow_offseted > -0.3) or not self.breathInState:
                    if self.zero_flow_count < 3:
                        self.zero_flow_count += 1
                    else:
                        self.flow_for_volume = 0
                else:
                    self.zero_flow_count = 0
                
                if len(self.deriv_points) >= 0: #useless logic
                    self.flowdata.append(self.flow_offseted) # * 1000 * 60)
                    #self.flowdata.append(deltaflow - deltaflowoffset)
                    
                    if self.flow_offseted > 0:
                        self.flow_detector.Cycle(self.flow_offseted)
                    else:
                        self.flow_detector.Cycle(0)
                    
                    try:
                        #self.peak_flow.setText('{:03.2f}'.format(self.flow_detector.peak_value) + 'L/Min')
                        self.peak_flow.setText('{:03.2f}'.format(self.epap) + 'mb')
                    except:
                        pass

                    self.flowpeakdata.append(1)

                    '''Volume data came from kalman of lungpressure'''
                    '''Now volume coming from flowprocess.Volume'''
                    ###self.kalmandata.append(self.kalman.Estimate(float(self.lst[0]) + float(self.peepdial.value())))
                    ####vol_base = self.kalman.Estimate(float(self.lst[0]))
                    if self.flow_for_volume != 0:
                        #vol_base = self.flowprocess.rootVolume(self.flow_offseted)
                        vol_base = self.flowprocess.Volume(self.flow_offseted)
                        if vol_base < 0:
                            vol_base = 0

                    else:
                        if vol_base > 50:
                            vol_base -= 50
                        else:
                            vol_base = 0
                        self.flowprocess.sum_of_volume = vol_base
                        self.flowprocess.sum_of_rmsVolume = vol_base

                    self.kalmandata.append(vol_base)
                    self.voldata.append(vol_base)
                    #if vol_base < 0:
                    #    vol_base = 0
                    #self.vol_detector.Cycle(vol_base)
                    #self.vol_detector.moving_average_cycle(vol_base)
                    ####self.volpeakdata.append(500.0)
                    #self.peak_vol.setText('{:03.2f}'.format(self.vol_detector.peak_value)  + 'ml')
                    
                    self.peak_vol.setText('{:03.2f}'.format(volume)  + 'ml')
                    #self.peak_vol.setText('{:03.2f}'.format(self.vol_detector.moving_average)  + 'ml')
                    #self.peak_vol.setText('{:03.2f}'.format(self.vol_peak)  + 'ml')



                    if lungpressure >= 0:
                        self.kalmanofpressuredata.append(self.kalmanpressure.Estimate(lungpressure ** 1.0))
                    else:
                        lungpressure = -lungpressure
                        self.kalmanofpressuredata.append(self.kalmanpressure.Estimate(lungpressure ** 1.0))

            except Exception as e:
                print("Exception in LungSensorData(...) : " + str(e) + ' - ' + data_stream)

            if len(self.deriv_points) == 0:
                self.timesnap = 0.0
            else:
                self.timesnap = time.perf_counter() - self.tic

            try:
                #self.deriv_points.append([(float(self.lst[0]) + float(self.peepdial.value())), self.timesnap])
                #self.deriv_points.append([(float(self.kalman.Estimate(float(self.lst[0])))), self.timesnap])

                lungpressure = float(self.lst[0])

                if len(self.deriv_points) > 3:
                    self.deriv_points.popleft()
                    '''
                    cannot remember its effect. seems not feasible output in case of peak detection could be delayed a bit.
                    self.dvdata.append(((self.deriv_points[2][0] - self.deriv_points[0][0]) / ((self.deriv_points[2][1] - self.deriv_points[0][1]) * 10000)))
                    '''
                    '''
                    Working code for derivative data from lung pressure data.
                    '''
                    self.dvdata.append(((self.deriv_points[2][0] - self.deriv_points[0][0]) / (0.2)))
                    self.dvdata_compressed.append(((self.deriv_points[2][0] - self.deriv_points[0][0]) / (1)))

                    '''
                    Following instruction will derive the data from the kalman of lung pressure.
                    '''
                    ''' Working code commented to see speed '''
                    #self.dvdata.append(((self.kalmandata[2] - self.kalmandata[0]) / (0.2)))

                    #self.dvdata.append(float(self.lst[1]))
                    
                    #self.dvdata.append(self.flowprocess.CalculateFlow(float(self.lst[1])))
                    #print("Flow -- " + str(dflow * 1000000))
                    #self.dvdata.append(dflow * 1000000)

                    ''' Working Code commented to check speed '''
                    
                    #self.voldata.append(self.flowprocess.sum_of_volume)
                    #self.dvdata.append(dflow)
                    #self.sumofvolume += self.flowprocess.CalculateFlow(float(self.lst[2]))
                    #self.voldata.append(self.sumofvolume)
                else:
                    self.dvdata.append(0.0)
                    self.dvdata_compressed.append(0.0)
            except Exception as e:
                print("Exception Section 0x05" + str(e) + ' - ' + data_stream)
                
            '''
            try:
                if len(self.deriv_points) >= 3:
                    if lungpressure > 0.2 and self.flag_breath_in_ready:
                        self.curve1.setPen(self.derivative_pen_in)
                        self.flag_breath_in_ready = False
                        self.lpzerocount = 0
                        if not self.breath_in_tick:
                            
                            if not self.flagStartPulse:
                                ##self.plottingBaseTimer.start(0.025)
                                self.pulse_state = 1
                                self.flagStartPulse = True

                            self.breath_in_tick = True
                            self.wave.playin()
                            self.lungtimer.setInterval(8000)
                            self.lung_wave.StartWave()
                            self.tsnap = time.perf_counter() - self.ttick
                            self.lbl_rr.setText('RR  : ' + '{:02f}'.format(60 / self.tsnap) + ' E->E : {:f}'.format(self.tsnap))
                            self.ttick = time.perf_counter()
                            self.eptick = self.ttick
                    elif self.dvdata[-1] < -10:
                        self.curve1.setPen(self.derivative_pen_out)
                        self.exhale_t_count += 1
                        #self.markerPeakPressure.setPos(self.ttm, lungpressure)
                        if self.breath_in_tick:
                            self.breath_in_tick = False
                            self.epsnap = time.perf_counter() - self.eptick
                            self.lbl_ep.setText('E->P: ' + '{:f}'.format(self.epsnap))
                            ###Reset the over pressure alarm when next peak is detcted###
                            if self.over_pressure_detection_delay == 0:
                                if self.lung_detector.peak_value > 5:
                                    self.label_alarm.setText("Alarm: ")

                    if lungpressure < 0.2:
                        if self.lpzerocount < 3:
                            self.lpzerocount += 1
                        else:
                            self.flag_breath_in_ready = True

            except Exception as e:
                print('Exception In Breath in / Breath out detection L-1319 : ' + str(e))
            '''
            '''
            try:
                if(len(self.deriv_points) >= 3):
                    if self.dvdata[-1] > 1:
                        self.curve1.setPen(self.derivative_pen_in)
                        self.inhale_t_count += 1
                        self.flag_idle = False
                        self.idle_count = 0
                        if not self.breath_in_tick:
                            self.breath_in_tick = True
                            self.wave.playin()
                            self.lungtimer.setInterval(8000)
                            self.lung_wave.StartWave()
                            self.tsnap = time.perf_counter() - self.ttick
                            self.lbl_rr.setText('RR  : ' + '{:02f}'.format(60 / self.tsnap) + ' E->E : {:f}'.format(self.tsnap))
                            self.ttick = time.perf_counter()
                            self.eptick = self.ttick
                    elif self.dvdata[-1] < -10:
                        self.curve1.setPen(self.derivative_pen_out)
                        self.exhale_t_count += 1
                        self.flag_idle = False
                        self.idle_count = 0
                        self.sumofvolume = 0.0
                        if self.breath_in_tick:
                            self.breath_in_tick = False
                            self.epsnap = time.perf_counter() - self.eptick
                            self.lbl_ep.setText('E->P: ' + '{:f}'.format(self.epsnap))
                            ### Reset the over pressure alarm when next peak is detcted ###
                            if self.over_pressure_detection_delay == 0:
                                if self.lung_detector.peak_value > 5:
                                    self.label_alarm.setText("Alarm: ")
                    else:
                        if not self.flag_idle:
                            self.idle_count += 1
                            if self.idle_count > 2:
                                ###print(f"Inhale {(self.inhale_t_count * 100) / 1000} :: Exhale {(self.exhale_t_count * 100) / 1000}")
                                self.flag_idle = True
                                self.idle_count = 3
                                self.inhale_t_count = 0
                                self.exhale_t_count = 0
            except Exception as e:
                print("Exception Section:0X02 : " + str(e) + ' - ' + data_stream)
            '''

            ipap_band_plus = self.ipapdial.value() + self.generator.ipap_tol
            ipap_band_minus = self.ipapdial.value() - self.generator.ipap_tol

            rising_edge_detection = False

            try:
                
                if self.flow_offseted > 0.5:
                    if not self.breathInState:
                        self.breath_in_min_time = ((60 / (self.rr * 1.2)) / (1 + self.ie)) * 1000
                        self.breathInState = True
                        self.breathInMinTimer.start(self.breath_in_min_time)
                    
                        self.curve1.setPen(self.derivative_pen_in)
                        self.inhale_t_count += 1
                        self.flag_idle = False
                        self.idle_count = 0

                        if not self.breath_in_tick:
                            self.breath_in_tick = True
                            self.wave.playin()
                            #self.lungtimer.setInterval(8000)
                            self.lung_wave.StartWave()
                            self.tsnap = time.perf_counter() - self.ttick
                            self.lbl_rr.setText('{:03.2f}'.format(60 / self.tsnap)) # + ' E->E : {:f}'.format(self.tsnap))
                            self.ttick = time.perf_counter()
                            self.eptick = self.ttick

                            self.vol_wave.StartWave()


                            if len(self.lungpressuredata) >= 3:
                                self.epap = self.lungpressuredata[len(self.lungpressuredata) - 3]

                    
                    # To detect peak lung pressure at breath in time only
                    self.lung_detector.Cycle(lungpressure)
                    self.lung_wave.Cycle(lungpressure)
                    self.lung_wave.zero_count = 0

                    self.vol_detector.Cycle(vol_base)
                    #self.vol_detector.moving_average_cycle(vol_base)
                    self.vol_wave.Cycle(vol_base)
                
                elif self.flow_offseted <= 0.5  and not self.breathInState:
                    self.curve1.setPen(self.derivative_pen_out)
                    self.exhale_t_count += 1
                    self.flag_idle = False
                    self.idle_count = 0
                    self.sumofvolume = 0.0
                    if self.breath_in_tick:
                        self.breath_in_tick = False
                        self.epsnap = time.perf_counter() - self.eptick
                        #self.lbl_ep.setText('1:{:02.2f}'.format(self.epsnap))
                        self.lbl_ep.setText('1:{:d}'.format(self.ie))
                        
                        ### Reset the over pressure alarm when next peak is detcted ###
                        if self.over_pressure_detection_delay == 0:
                            if self.lung_detector.peak_value > 5:
                                self.label_alarm.setText("Alarm: ")
                                self.lowp_alarm_enable = False

                        self.vol_peak = self.vol_wave.GetMax()
                        self.vol_detector.moving_average_cycle(self.vol_peak)

                        self.lungPeakPressure = self.lung_wave.GetMax()
                        self.ipap = self.lungPeakPressure - self.epap
                        if self.lungPeakPressure < 10:
                            if self.lungLowPressureCount < 2:
                                self.lungLowPressureCount += 1
                            else:
                                if self.workerThreadCreated:
                                    if not self.worker.flagStop:
                                        self.lungLowPressureDetected = True
                                        self.label_alarm.setText('Alarm : Low Pressure')
                                        self.lowp_alarm_enable = True
                                    else:
                                        self.lowp_alarm_enable = False
                                
                        else:
                            self.lungLowPressureCount = 0
                            self.lungLowPressureDetected = False
                            self.lungtimer.setInterval(8000)
                            self.breathfail_alarm_enable = False

                        ############################################################################
                        ## Auto adjust code for pressure or Bipap Mode
                        ############################################################################

                        if self.auxMode == MachineRunModes.BiPAP:
                            if self.workerThreadCreated:
                                if not self.worker.flagStop:
                                    if self.ipap < (self.ipapdial.value() - self.generator.ipap_tol):
                                        self.ipap_deviation = self.ipapdial.value() - self.ipap
                                        #self.changefactor = self.ipap_deviation * 0.5
                                        self.changefactor = self.GetChangeFactorFromDeviation(self.ipap_deviation)
                                        if self.changefactor < 1:
                                            self.changefactor = 1
                                        if (self.generator.xav + self.generator.xavv) < self.generator.xmax: #------------------
                                            if self.vt_unmatch_count < 0: ##Disable this logic. Pass to else:
                                                self.vt_unmatch_count += 1
                                            else:
                                                self.vt_adjust += self.changefactor #----------------
                                                self.vt_unmatch_count = 0
                                                self.generator.xavv = self.vt_adjust
                                                print('Adjusting Bipap ++ : ' + str(self.changefactor) + ' lpDiff-' + str(self.ipap_deviation))
                                                #self.settings_dict[r"vt"] = str(self.vt)
                                                self.SaveSettings()
                                    elif self.ipap > (self.ipapdial.value() + self.generator.ipap_tol):
                                        self.ipap_deviation = self.ipap - self.ipapdial.value()
                                        #self.changefactor = self.ipap_deviation * 0.5
                                        self.changefactor = self.GetChangeFactorFromDeviation(self.ipap_deviation)
                                        if self.changefactor < 1:
                                            self.changefactor = 1
                                        if (self.generator.xav - self.generator.xavv) > self.generator.Dt: #-------------------
                                            if self.vt_unmatch_count < 0: ##Disable this logic. Pass to else:
                                                self.vt_unmatch_count += 1
                                            else:
                                                self.vt_adjust -= self.changefactor #---------------------
                                                self.vt_unmatch_count = 0
                                                self.generator.xavv = self.vt_adjust
                                                print('Adjusting Bipap -- : ' + str(self.changefactor) + ' lpDiff-' + str(self.ipap_deviation))
                                                #self.settings_dict[r"vt"] = str(self.vt)
                                                self.SaveSettings()
                                    else:
                                        self.vt_unmatch_count = 0

                        elif self.auxMode == MachineRunModes.CMV:
                            if self.workerThreadCreated:
                                if not self.worker.flagStop:
                                    pass
                                    '''
                                    self.volume_band_plus = self.vt + self.generator.vol_tol
                                    self.volume_band_minus = self.vt - self.generator.vol_tol

                                    if self.vol_detector.moving_average < self.volume_band_minus:
                                        self.vol_deviation = self.vt - self.vol_detector.moving_average
                                        self.vol_changefactor = self.GetChangeFactorFromVolDeviation(self.vol_deviation)
                                        
                                        if (self.generator.xav + self.generator.xavv) < self.generator.xmax:
                                            self.vt_adjust += self.changefactor #----------------
                                            self.generator.xavv = self.vt_adjust
                                            print('Adjusting Vol ++ : ' + str(self.changefactor) + ' lpDiff-' + str(self.ipap_deviation))
                                            #self.settings_dict[r"vt"] = str(self.vt)
                                            self.SaveSettings()
                                    
                                    elif self.vol_detector.moving_average > self.volume_band_plus:
                                        self.vol_deviation = self.vol_detector.moving_average - self.vt
                                        self.vol_changefactor = self.GetChangeFactorFromVolDeviation(self.vol_deviation)

                                        if (self.generator.xav - self.generator.xavv) > self.generator.Dt:
                                            self.vt_adjust -= self.changefactor #---------------------
                                            self.generator.xavv = self.vt_adjust
                                            print('Adjusting Bipap -- : ' + str(self.changefactor) + ' lpDiff-' + str(self.ipap_deviation))
                                            #self.settings_dict[r"vt"] = str(self.vt)
                                            self.SaveSettings()
                                    else:
                                        pass
                                    '''


                else:
                    if not self.flag_idle:
                        self.idle_count += 1
                        if self.idle_count > 2:
                            ###print(f"Inhale {(self.inhale_t_count * 100) / 1000} :: Exhale {(self.exhale_t_count * 100) / 1000}")
                            self.flag_idle = True
                            self.idle_count = 3
                            self.inhale_t_count = 0
                            self.exhale_t_count = 0

                ### Low Pressure Detection

            except Exception as e:
                print("Exception Section:0X02 : " + str(e) + ' - ' + data_stream)

            self.tic = time.perf_counter()

            try:
                self.curve1.setData(self.tfdata, self.lungpressuredata)
                #self.curve2.setData(self.tfdata, self.lungpressurepeakdata)
                self.curve3.setData(self.tfdata, self.kalmanofpressuredata)
            except Exception as e:
                print('Exception SetData curve1 curve3 : ' + str(e))
                
            try:
                '''Assign volume data to volume plotter curve'''
                #(originally kalman data) self.volcurve.setData(self.kalmandata)
                self.volcurve.setData(self.tfdata, self.voldata)
                ###self.volpeakcurve.setData(self.tfdata, self.volpeakdata)
            except Exception as e:
                print('Exception SetData volcurve : ' + str(e))

            try:
                '''Assign Flowdata to flow plotter curve & dvdata to dvcurve'''
                self.flowcurve.setData(self.tfdata, self.flowdata)
            except Exception as e:
                print('Exception SetData flowcurve : ' + str(e))

            try:
                self.dvcurve.setData(self.tfdata, self.dvdata_compressed)
            except Exception as e:
                print('Exception SetData dvcurve : ' + str(e))

            try:
                self.flowpeakcurve.setData(self.tfdata, self.flowpeakdata)
            except Exception as e:
                print('Exception SetData flowpeakcurve : ' + str(e))


            try:
                '''Assign pulsedata to pulse curve'''
                self.pulseCurve.setData(self.tfdata, self.pulseData)
            except Exception as e:
                print('Exception SetData pulseCurve')
            
            try:
                if (lungpressure > float(self.peakdial.value())):
                    if self.sensorThreadCreated:
                        self.wave.playfile()
                        self.label_alarm.setText("Alarm: Over Pressure")
                        self.over_pressure_detection_delay = 10
                
                        #self.sensor.beep()
            except Exception as e:
                print("Exception section 0x06 : " + str(e) + ' - ' + data_stream)


    def write_info(self, data_stream):
        #rcount = self.txrxtable.rowCount()
        #self.txrxtable.insertRow(rcount)
        #self.txrxtable.setItem(rcount,0, QTableWidgetItem(data_stream))
        #self.txrxtable.scrollToBottom()
        #self.txrxtable.resizeColumnsToContents()
        #self.txrxtable.resizeRowsToContents()
        if data_stream == "StoppedOK":
            if self.primaryThreadCreated:
                self.primaryThread.exit()
                self.primaryThread.wait()
                self.primaryThreadCreated = False
                del self.primaryThread
                self.runloop.setEnabled(True)
        if "Endbipapinit" in data_stream:
            if self.bipap_init_threadcreated:
                self.bipapinitThread.exit()
                self.bipapinitThread.wait()
                self.bipap_init_threadcreated = False
                del self.bipapinitThread
                print("bipapinitThread Closed")

    def endBipap(self, pparr):
        self.pparr = pparr
        pprint.pprint(self.pparr)
        self.btnrunbploop.setEnabled(True)

class JsonSettings(object):
    def __init__(self , location):
        self.location = os.path.expandvars(location)
        #print(self.location)
        self.load(self.location)
        #pprint.pprint(self.db[r'Columns'])
    def load(self , location):
        if os.path.exists(location):
            self._load()
        else:
            print("location missing")
            self.dict = {}
        return True
    def dumptojson(self):
        try:
            json.dump(self.dict , open(self.location, "w+"))
            return True
        except:
            return False
    def _load(self):
        self.dict = json.load(open(self.location , "r"))

class MessageWindow(QWidget):
    def __init__(self, messages, parent = None):
        super(MessageWindow, self).__init__(parent)
        vbox = QVBoxLayout()
        ##label = QLabel("Alarms",  self)
        self.labels = []
        if len(messages) > 0:
            for text in messages:
                lbl = QLabel()
                lbl.setText(text)
                lbl.setStyleSheet('color: red;font: 75 26pt "MS Shell Dlg 2";')
                vbox.addWidget(lbl)

        self.setLayout(vbox)
                

    def closeEvent(self, event):
        pass
        #event.ignore()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    qtmodern.styles.dark(app)
    #qtmodern.styles.light(app)

    mw_class_instance = MainWindow()
    mw = qtmodern.windows.ModernWindow(mw_class_instance)
    mw.showFullScreen()
    sys.exit(app.exec_())

