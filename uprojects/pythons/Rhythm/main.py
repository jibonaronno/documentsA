#!/usr/bin/python3
import sys
from os.path import join, dirname, abspath
import serial
import serial.tools.list_ports as port_list
from qtpy import uic
from qtpy.QtCore import Slot, QTimer, QThread, Signal, QObject, Qt
from qtpy.QtWidgets import QApplication, QMainWindow, QMessageBox, QAction, QDialog, QTableWidgetItem
from pyqtgraph import PlotWidget
import pyqtgraph as pg
from collections import deque
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QGroupBox, QTableWidget

import os
import numpy as np
import random
import qtmodern.styles
import qtmodern.windows
import time
import json
import pprint

_UI = join(dirname(abspath(__file__)), 'VentUI.ui')

class PrimaryThread(QObject):
    signal = Signal(str)

    def __init__(self, s, codegen):
        self.s = s
        #self.json = JsonSettings("settings.json")
        self.codegen = codegen #GcodeGenerator(int(self.json.dict['vt']), int(self.json.dict['rr']), int(self.json.dict['ie']), int(self.json.dict['fio2']))
        self.codegen.Generate()
        self.codelist = self.codegen.gcodeprimary.splitlines()
        self.flagStop = False
        super().__init__()

    def Stop(self):
        self.flagStop = True

    @Slot()
    def run(self):
        try:
            lst = []
            for line in self.codelist:
                if self.flagStop:
                    break
                #self.s.reset_input_buffer()
                self.s.write((str(line) + "\r\n").encode("utf-8"))
                time.sleep(0.5)
                in_waiting = self.s.in_waiting
                while in_waiting == 0:
                    time.sleep(1)
                    in_waiting = self.s.in_waiting
                    
                jMessage = ""
                while self.s.in_waiting:
                    #print(self.s.readline().decode('ascii'))
                    lst = self.s.readlines()
                    for itm in lst:
                        jMessage += itm.decode('ascii')
                        #jMessage += self.s.readline().decode('ascii')
                    if "busy" in jMessage:
                        time.sleep(1)
                        continue
                self.signal.emit(str(line) + " - " + jMessage)
            self.signal.emit("Stopped")
        except serial.SerialException as ex:
            print("Error In SerialException" + ex.strerror)
            self.signal.emit("Stopped")
        except Exception as e:
            pprint.pprint(e)
            self.signal.emit("Stopped")


class WorkerThread(QObject):
    signal = Signal(str)

    def __init__(self, s, codegen):
        self.s = s
        self.json = JsonSettings("settings.json")
        self.codegen = codegen #GcodeGenerator(int(self.json.dict['vt']), int(self.json.dict['rr']), int(self.json.dict['ie']), int(self.json.dict['fio2']))
        self.codegen.Generate()
        self.codelist = self.codegen.gcodestr.splitlines()
        #pprint.pprint(self.codelist)
        self.linecount = len(self.codelist)
        #for idxx in range(self.linecount):
        #    print(self.codelist[idxx])
        #self.idx = 0
        self.flagStop = False
        super().__init__()

    def Stop(self):
        self.flagStop = True

    def updateGcode(self, codegen):
        self.codegen = codegen
        self.codegen.Generate()
        self.codelist = self.codegen.gcodestr.splitlines()

    @Slot()
    def run(self):
        lst = []
        while 1:
            if self.flagStop:
                break
            try:
                for line in self.codelist:
                    if self.flagStop:
                        break
                    self.s.write((str(line)+"\r\n").encode('utf-8'))
                    time.sleep(0.5)
                    in_waiting = self.s.in_waiting
                    while in_waiting == 0:
                        time.sleep(1)
                        in_waiting = self.s.in_waiting
                        
                    jMessage = ""
                    while "ok" not in jMessage:
                        while self.s.in_waiting:
                            #print(self.s.readline().decode('ascii'))
                            lst = self.s.readlines()
                            for itm in lst:
                                jMessage += itm.decode('ascii')
                    self.signal.emit(str(line) + " - " + jMessage)
            except serial.SerialException as ex:
                print("Error In SerialException" + ex.strerror)

            # doFunc(self.signal, jMessage)

class SensorThread(QObject):
    signal = Signal(str)
    def __init__(self, s):
        self.s = s
        self.flagStop = False
        self.jMessage = ""
        super().__init__()

    def Stop(self):
        self.flagStop = True

    @Slot()
    def run(self):
        lst = []
        while 1:
            if self.flagStop:
                break
            try:
                jMessage = self.s.readline().decode('ascii')
                self.signal.emit(jMessage)
                #in_waiting = self.s.in_waiting
                #while in_waiting == 0:
                    #time.sleep(0.1)
                    #in_waiting = self.s.in_waiting
                #jMessage = ""
                #while self.s.in_waiting:
                    #print(self.s.readline().decode('ascii'))
                    #lst = self.s.readlines()
                    #for itm in lst:
                        #jMessage += itm.decode('ascii')
                        #print(jMessage)
                #self.signal.emit(str(line) + " - " + jMessage)
            except serial.SerialException as ex:
                print("Error In SerialException" + ex.strerror)

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        #self.verticalLayout_2 = QVBoxLayout()
        self.tableHeaders = ['VT', 'I:E', 'RR', 'FIO2']
        self.widget = uic.loadUi(_UI, self)
        window_title = "Rhythm"
        self.json = JsonSettings("settings.json")
        self.settings_dict = self.json.dict
        pprint.pprint(self.settings_dict)
        self.table = QTableWidget(self)
        self.table.setRowCount(2)
        self.table.setColumnCount(5)
        self.table.setHorizontalHeaderLabels(self.tableHeaders)
        self.table.setItem(0,0, QTableWidgetItem(self.settings_dict[r"vt"]))
        self.table.setItem(0,1, QTableWidgetItem(self.settings_dict[r"ie"]))
        self.table.setItem(0,2, QTableWidgetItem(self.settings_dict[r"rr"]))
        self.table.setItem(0,3, QTableWidgetItem(self.settings_dict[r"fio2"]))
        #self.table.itemChanged.connect(self.SaveSettings)
        self.vt = int(self.settings_dict[r"vt"])
        self.rr = int(self.settings_dict[r"rr"])
        self.ie = int(self.settings_dict[r"ie"])
        self.fio2 = int(self.settings_dict[r"fio2"])
        self.verticalLayout_2.addWidget(self.table)

        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2)

        self.motion_table = QTableWidget(self)
        self.motion_table_headers = ['variables', 'values']
        self.motion_table.setColumnCount(2)
        self.motion_table.setRowCount(10)
        self.motion_table.setHorizontalHeaderLabels(self.motion_table_headers)
        self.motion_table.hide()

        self.dat = deque()
        self.datpeak = deque()

        self.lungpressure_line_pen = pg.mkPen(200, 100, 0)
        self.plotter = PlotWidget()
        self.plotter.showGrid(x=True, y=True, alpha=None)
        self.curve1 = self.plotter.plot(0,0,"lungpressure", 'b')
        self.curve2 = self.plotter.plot(0,0,"peakpressure", pen = self.lungpressure_line_pen)
        
        #self.motion_table.setSizeAdjustPolicy(QtWidget.QAbstractScrollArea.AdjustToContents)
        self.CalculateSettings()
        self.verticalLayout_2.addWidget(self.motion_table)
        self.verticalLayout_2.addWidget(self.plotter)
        self.motion_table.hide()

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
        self.hbox.addWidget(self.txrxtable)
        #self.hbox.addLayout

        self.peepdial.valueChanged.connect(self.peepDialChanged)
        self.peeplcd.display(self.peepdial.value())
        self.peakdial.valueChanged.connect(self.peakDialChanged)
        self.peaklcd.display(self.peakdial.value())
        self.ipapdial.valueChanged.connect(self.ipapDialChanged)
        self.ipaplcd.display(self.ipapdial.value())
        self.vtdial.valueChanged.connect(self.vtDialChanged)
        self.vtlcd.display(self.vtdial.value())
        self.iedial.valueChanged.connect(self.ieDialChanged)
        self.ielcd.display(self.iedial.value())
        self.rrdial.valueChanged.connect(self.rrDialChanged)
        self.rrlcd.display(self.rrdial.value())
        self.fiodial.valueChanged.connect(self.fioDialChanged)
        self.fiolcd.display(self.fiodial.value())

        self.s = ""
        self.s2 = ""
        self.ports = list(port_list.comports())

        self.primaryThreadCreated = False
        self.workerThreadCreated = False
        self.sensorThreadCreated = False
        self.serialPortOpen = False
        self.serialSensorOpen = False

    def update_param_table(self):
        self.table.setItem(0,0, QTableWidgetItem(self.settings_dict[r"vt"]))
        self.table.setItem(0,1, QTableWidgetItem(self.settings_dict[r"ie"]))
        self.table.setItem(0,2, QTableWidgetItem(self.settings_dict[r"rr"]))
        self.table.setItem(0,3, QTableWidgetItem(self.settings_dict[r"fio2"]))

    def peepDialChanged(self):
        self.peeplcd.display(self.peepdial.value())

    def peakDialChanged(self):
        self.peaklcd.display(self.peakdial.value())

    def ipapDialChanged(self):
        self.ipaplcd.display(self.ipapdial.value())

    def vtDialChanged(self):
        self.vtlcd.display(self.vtdial.value())
        self.vt = self.vtdial.value()
        self.settings_dict[r"vt"] = str(self.vt)
        self.update_param_table()
        self.SaveSettings()

    def ieDialChanged(self):
        self.table.setItem(0,1, QTableWidgetItem(self.settings_dict[r"ie"]))
        self.ielcd.display(self.iedial.value())
        self.ie = self.iedial.value()
        self.settings_dict[r"ie"] = str(self.ie)
        self.update_param_table()
        self.SaveSettings()

    def rrDialChanged(self):
        self.rrlcd.display(self.rrdial.value())
        self.rr = self.rrdial.value()
        self.settings_dict[r"rr"] = str(self.rr)
        self.update_param_table()
        self.SaveSettings()

    def fioDialChanged(self):
        self.fiolcd.display(self.fiodial.value())
        self.fio2 = self.fiodial.value()
        self.settings_dict[r"fio2"] = str(self.fio2)
        self.update_param_table()
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
        ###self.json = JsonSettings("settings.json")
        ###self.settings_dict = self.json.dict
        #self.vt = int(self.settings_dict[r"vt"])
        #self.rr = int(self.settings_dict[r"rr"])
        #self.ie = int(self.settings_dict[r"ie"])
        #self.fio2 = int(self.settings_dict[r"fio2"])
        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2)
        self.motion_table.setItem(0,0, QTableWidgetItem('Dp'))
        self.motion_table.setItem(0,1, QTableWidgetItem(str(self.generator.Dp)))
        self.motion_table.setItem(1,0, QTableWidgetItem('Dr'))
        self.motion_table.setItem(1,1, QTableWidgetItem(str(self.generator.Dr)))
        self.motion_table.setItem(2,0, QTableWidgetItem('Dt'))
        self.motion_table.setItem(2,1, QTableWidgetItem(str(self.generator.Dt)))
        self.motion_table.setItem(3,0, QTableWidgetItem('Ti'))
        self.motion_table.setItem(3,1, QTableWidgetItem(str(self.generator.Ti)))
        self.motion_table.setItem(4,0, QTableWidgetItem('Th'))
        self.motion_table.setItem(4,1, QTableWidgetItem(str(self.generator.Th)))
        self.motion_table.setItem(5,0, QTableWidgetItem('Vi'))
        self.motion_table.setItem(5,1, QTableWidgetItem(str(self.generator.Vi)))
        self.motion_table.setItem(6,0, QTableWidgetItem('Vh'))
        self.motion_table.setItem(6,1, QTableWidgetItem(str(self.generator.Vh)))

    def sensorData(self, data_stream):
        #print(data_stream.split(','))
        lst = data_stream.split(",")
        self.maxLen = 400  # max number of data points to show on graph
        if(len(lst) > 1):
            if len(self.dat) > self.maxLen:
                self.dat.popleft()  # remove oldest
            if len(self.datpeak) > self.maxLen:
                self.datpeak.popleft()
            self.datpeak.append(float(self.peakdial.value()))
            self.dat.append(float(lst[1]))
            self.curve1.setData(self.dat)
            self.curve2.setData(self.datpeak)

    def write_info(self, data_stream):
        rcount = self.txrxtable.rowCount()
        self.txrxtable.insertRow(rcount)
        self.txrxtable.setItem(rcount,0, QTableWidgetItem(data_stream))
        self.txrxtable.scrollToBottom()
        self.txrxtable.resizeColumnsToContents()
        self.txrxtable.resizeRowsToContents()
        if data_stream == "Stopped":
            if self.primaryThreadCreated:
                self.primaryThread.exit()
                self.primaryThread.wait()
                self.primaryThreadCreated = False
                del self.primaryThread

        #elif data_stream == "Loop":
        #    self.primaryThread.exit() ###
        #    self.worker = WorkerThread(self.s, self.generator)
        #    self.workerThread = QThread()
        #    self.workerThread.started.connect(self.worker.run)
        #    self.worker.signal.connect(self.write_info)
        #    self.worker.moveToThread(self.workerThread)
        #    self.workerThread.start()
        #    self.workerThreadCreated = True
        #    print("Starting Worker Thread")

        #if data_stream == "Stopped":
        #    self.worker = WorkerThread(self.s)
        #    self.workerThread = QThread()
        #    self.workerThread.started.connect(self.worker.run)
        #    self.worker.signal.connect(self.write_info)
        #    self.worker.moveToThread(self.workerThread)
        #    self.workerThread.start()
        #    print("Starting Thread")

    @Slot()
    def on_gengcode_clicked(self):
        self.CalculateSettings()
        self.generator.Generate()
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
        if not self.workerThreadCreated:
            if not self.primaryThreadCreated:
                self.primary = PrimaryThread(self.s, self.generator)
                self.primaryThread = QThread()
                self.primaryThread.started.connect(self.primary.run)
                self.primary.signal.connect(self.write_info)
                self.primary.moveToThread(self.primaryThread)
                self.primaryThread.start()
                self.primaryThreadCreated = True
                print("Starting Primary Thread")
        if self.serialSensorOpen:
            if not self.sensorThreadCreated:
                self.sensor = SensorThread(self.s2)
                self.sensorThread = QThread()
                self.sensorThread.started.connect(self.sensor.run)
                self.sensor.signal.connect(self.sensorData)
                self.sensor.moveToThread(self.sensorThread)
                self.sensorThread.start()
                self.sensorThreadCreated = True
                print("Starting Sensor Thread ...")

    @Slot()
    def on_runloop_clicked(self):
        if not self.primaryThreadCreated:
            if not self.workerThreadCreated:
                self.worker = WorkerThread(self.s, self.generator)
                self.workerThread = QThread()
                self.workerThread.started.connect(self.worker.run)
                self.worker.signal.connect(self.write_info)
                self.worker.moveToThread(self.workerThread)
                self.workerThread.start()
                self.workerThreadCreated = True
                print("Starting Worker Thread")

    @Slot()
    def on_disconnect_clicked(self):
        if self.serialPortOpen:
            if self.workerThreadCreated:
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
            self.s.close()
            if self.serialSensorOpen:
                self.s2.close()
            self.serialPortOpen = False
            self.serialSensorOpen = False

    @Slot()
    def on_connect_clicked(self):
        try:
            if not self.serialPortOpen:
                print("Serial Port Name : " + self.portsList.currentText())
                self.s = serial.Serial(self.portsList.currentText(), baudrate=115200, timeout=1)
                #self.s.open()
                time.sleep(1)
                self.serialPortOpen = True
                #self.s.write("\r\n\r\n") # Hit enter a few times to wake the Printrbot
                #time.sleep(2)   # Wait for Printrbot to initialize
                while self.s.in_waiting:
                    self.s.readline()
                    #print(self.s.readline().decode("ascii"))
                #self.s.flushInput()  # Flush startup text in serial input
                #monitoringPort
            if not self.serialSensorOpen:
                self.s2 = serial.Serial(self.monitoringPort.currentText(), baudrate=115200, timeout=1)
                self.serialSensorOpen = True
            
        except serial.SerialException as ex:
            self.serialPortOpen = False
            print(ex.strerror)
            print("Error Opening Serial Port..........................................")
           
    @Slot()
    def on_btnCPAP_clicked(self):
        if self.btnCPAP.isChecked():
            #self.btnCPAP.toggle()
            self.btnCPAP.setStyleSheet('QPushButton {background-color: #7F7F7F}')
        else:
            self.btnCPAP.setStyleSheet('QPushButton {background-color: #404040}')

    def SaveSettings(self):
        ###self.json = JsonSettings("settings.json")
        ###self.settings_dict = self.json.dict
        self.json.dict[r'vt'] = str(self.vt)
        self.json.dict[r'ie'] = str(self.ie)
        self.json.dict[r'rr'] = str(self.rr)
        self.json.dict[r'fio2'] = str(self.fio2)
        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2)
        self.generator.Generate()
        if self.workerThreadCreated:
            self.worker.updateGcode(self.generator)
        pprint.pprint(self.generator.gcodestr)
        #self.json.dumptojson()
        ###self.vt = int(self.settings_dict[r"vt"])
        ###self.rr = int(self.settings_dict[r"rr"])
        ###self.ie = int(self.settings_dict[r"ie"])
        ###self.fio2 = int(self.settings_dict[r"fio2"])
        self.CalculateSettings()
        ###print(str(self.vt) + ", "+str(self.ie)+", "+str(self.rr)+", "+str(self.fio2)+"\r\n")
        ###pprint.pprint(self.json.dict)

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

class GcodeGenerator(object):
    def __init__(self, vt, rr, ie, fio2):
        self.xmax = 64
        self.xamb = 30
        self.xrect = 20
        self.vtmax = 800
        self.xavmax = self.xmax - self.xrect
        self.vt = vt
        self.rr = rr
        self.ie = ie
        self.fio2 = fio2
        self.Dt = self.xmax - self.xrect
        #self.xav = self.xavmax * (self.vt / self.vtmax)
        self.xav = self.xrect * (self.vt / self.vtmax)
        self.Dp = self.Dt + self.xav
        self.Dr = self.xrect
        #self.Dt = self.Dp - self.Dr
        self.TDMS = 100

        self.vmax = 200
        self.Ti = 60 / ((1 + self.ie) * self.rr)
        self.Th = self.Ti * self.ie
        #self.Vi = (self.xrect * 60) / self.Ti
        self.Vi = (self.xav / self.Ti) * 60
        self.Vh = (self.xav * 60) / self.Th
    
    def Compute(self):
        self.xmax = 64
        self.xamb = 30
        self.xrect = 20
        self.vtmax = 800
        self.xavmax = self.xmax - self.xrect
        self.Dt = self.xmax - self.xrect
        #self.xav = self.xavmax * (self.vt / self.vtmax)
        self.xav = self.xrect * (self.vt / self.vtmax)
        self.Dp = self.Dt + self.xav
        self.Dr = self.xrect
        #self.Dt = self.Dp - self.Dr
        self.TDMS = 100

        self.vmax = 200
        self.Ti = 60 / ((1 + self.ie) * self.rr)
        self.Th = self.Ti * self.ie
        #self.Vi = (self.xrect * 60) / self.Ti
        self.Vi = (self.xav / self.Ti) * 60
        self.Vh = (self.xav * 60) / self.Th
    def Generate(self):
        self.Compute()
        self.gcodeprimary = "G21\r\nG80\r\nM92 X160 Y160\r\nG90\r\nG28 X0Y0 F500\r\nG01 X" + str(int(self.Dp)) + " Y" + str(int(self.Dp)) + " F500\r\n" + "G01 X" + str(int(self.Dt))+" Y"+str(int(self.Dt))+" F500\r\n"
        self.gcodestr = "G01 X" + str(int(self.Dp))+" Y"+str(int(self.Dp))+" F"+str(int(self.Vi))+"\r\n"+"G01 X"+str(int(self.Dt))+" Y"+str(int(self.Dt))+" F"+str(int(self.Vh))+"\r\n" #+"G04 P"+str(self.TDMS)+"\r\n"
        with open('primary.gcode', 'w') as writer:
            writer.write(self.gcodeprimary)

if __name__ == '__main__':
    app = QApplication(sys.argv)

    qtmodern.styles.dark(app)

    mw_class_instance = MainWindow()
    mw = qtmodern.windows.ModernWindow(mw_class_instance)
    mw.show()
    sys.exit(app.exec_())
