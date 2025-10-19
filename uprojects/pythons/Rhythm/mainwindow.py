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
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QGroupBox

import math
import os
import numpy as np
import random
import qtmodern.styles
import qtmodern.windows
import time
import pprint

from gcodegenerator import GcodeGenerator
from startdialog import StartDialog
from time import sleep

_UI = join(dirname(abspath(__file__)), 'VentUI.ui')

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        startdlg = StartDialog(None)
        self.widget = uic.loadUi(_UI, self)
        window_title = "Rhythm"
        self.setWindowTitle(window_title)

        self.vt = self.vtdial.value()
        self.ie = self.iedial.value()
        self.rr = self.rrdial.value()
        self.fio2 = self.fiodial.value()

        self.generator = GcodeGenerator(self.vt, self.rr, self.ie, self.fio2)

        self.lungpressuredata = deque()
        self.lungpressurepeakdata = deque()
        self.peeppressuredata = deque()
        self.peeppressurepeakdata = deque()

        self.dvdata = deque()
        self.deriv_points = deque()
        self.timesnap = 0.0
        self.tic = 0.0

        self.lungpressure_line_pen = pg.mkPen(200, 100, 0)
        self.plotter = PlotWidget()
        self.plotter.showGrid(x=True, y=True, alpha=None)
        self.plotter.setTitle("Pressure")
        self.curve1 = self.plotter.plot(0,0,"lungpressure", 'b')
        self.curve2 = self.plotter.plot(0,0,"peakpressure", pen = self.lungpressure_line_pen)

        self.derivative_pen = pg.mkPen(200, 200, 10)
        self.derivative_pen_in = pg.mkPen(10, 200, 10)
        self.derivative_pen_out = pg.mkPen(10, 200, 200)
        #self.dvcurve = self.plotter.plot(0,0,"dvcurve", pen = self.derivative_pen)

        self.inhale_t_count = 0
        self.inhale_t = 0
        self.exhale_t = 0
        self.exhale_t_count = 0
        self.flag_idle = True
        self.idle_count = 0

        #self.dvcurve.setPen()

        self.flowplotter = PlotWidget()
        self.flowplotter.showGrid(x=True, y=True, alpha=None)
        self.flowplotter.setTitle("Flow")

        self.dvcurve = self.flowplotter.plot(0,0,"dvcurve", pen = self.derivative_pen)

        self.volplotter = PlotWidget()
        self.volplotter.showGrid(x=True, y=True, alpha=None)
        self.volplotter.setTitle("Volume")
        
        self.CalculateSettings()
        self.verticalLayout_2.addWidget(self.plotter)
        self.verticalLayout_2.addWidget(self.flowplotter)
        self.verticalLayout_2.addWidget(self.volplotter)
        #self.flowplotter.hide()
        self.volplotter.hide()

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

        #self.vtdial.setStyleSheet("{ background-color: rgb(20,20,20) }")

        self.serialMarlin = ""
        self.serialSensor = ""
        self.ports = list(port_list.comports())

        self.marlinPortOpen = False
        self.sensorPortOpen = False
        self.gengcode.hide()
        self.childrenMakeMouseTransparen()

        self.flag_sensorlimit_tx = True
        self.sensorLimitTimer = QTimer(self)
        self.sensorLimitTimer.timeout.connect(self.checkSensorLimitChanged)

        self.ComPorts = {'Marlin':'NA', 'Sensor':'NA'}
        self.selected_ports = []

        self.sensorLimitTimer.start(1000)

    @Slot()
    def on_btnmachinesetup_clicked(self):
        pass

    @Slot()
    def on_btnsavemachinesetup_clicked(self):
        pass

    def checkSensorLimitChanged(self):
        pass


    def childrenMakeMouseTransparen(self):
        self.label_13.setAttribute(Qt.WA_TransparentForMouseEvents, True)
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

    def peepDialChanged(self):
        pass

    def peakDialChanged(self):
        pass

    def lowpDialChanged(self):
        pass

    def himinitDialChanged(self):
        pass

    def lowminitDialChanged(self):
        pass

    def ipapDialChanged(self):
        pass

    def vtDialChanged(self):
        pass

    def ieDialChanged(self):
        pass

    def rrDialChanged(self):
        pass

    def fioDialChanged(self):
        pass

    
    def ShowGcodeTable(self):
        pass

    def CalculateSettings(self):
        pass

    @Slot()
    def on_gengcode_clicked(self):
        pass

    @Slot()
    def on_scanPorts_clicked(self):
        pass

    @Slot()
    def on_btninit_clicked(self):
        pass

    @Slot()
    def on_runloop_clicked(self):
        pass

    @Slot()
    def on_disconnect_clicked(self):
        pass

    @Slot()
    def on_btnalarmpage_clicked(self):
        pass

    @Slot()
    def on_startpush_clicked(self):
        pass

    @Slot()
    def on_connect_clicked(self):
        pass

    @Slot()
    def on_gcodeshow_clicked(self):
        pass

    @Slot()
    def on_alarm_clicked(self):
        pass

if __name__ == '__main__':
    app = QApplication(sys.argv)
    qtmodern.styles.dark(app)
    mw_class_instance = MainWindow()
    mw = qtmodern.windows.ModernWindow(mw_class_instance)
    mw.showFullScreen()
    sys.exit(app.exec_())
