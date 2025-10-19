
import sys
from os.path import join, dirname, abspath
import serial
#import serial.tools.list_ports as port_list
#from serial.tools import *
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
import json
import pprint

from gcodegenerator import GcodeGenerator
from dispatchers import PrimaryThread, WorkerThread, SensorThread, BipapThread
from wavegenerator import WaveMapper
from startdialog import StartDialog
from math import pi, sin
from PyQt5.QtMultimedia import *
import struct
#import RPi.GPIO as GPIO
from time import sleep

class DetectDevices(object):
    def __init__(self):
        self.ports = []
        self.usbports = []
        self.selected_ports = []
        self.MarlinPort = ["NA"]
        self.SensorPort = ["NA"]
        self.EncoderPort = ["NA"]

    def listPorts(self):
        from serial.tools.list_ports import comports
        self.ports = list(comports())
        return self.ports

    def listUsbPorts(self):
        self.listPorts()
        self.usbports.clear()
        if len(self.ports) > 0:
            for port in self.ports:
                if 'USB' in port[2]:
                    self.usbports.append(port)
                    #print('USB Detected : ' + port[2])

    def printPorts(self):
        self.listPorts()
        if len(self.ports) > 0:
            for port in self.ports:
                print(port[0])
                #for itm in port:
                    #print(itm)

    def printUsbPorts(self):
        self.listUsbPorts()
        if len(self.usbports) > 0:
            for port in self.usbports:
                print(port[0])


    def detectCustomBoards(self):
        uart_lines = []
        skip_loop = False
        self.listUsbPorts()
        print(f"Number of USB Ports : {len(self.usbports)}")
        print('waiting 5 seconds')
        time.sleep(5)
        if len(self.usbports) > 0:
            for port in self.usbports:
                uart_lines = self.connectAndRead(port)
                for line in uart_lines:
                    if b'Marlin' in line:
                        self.MarlinPort = port
                        skip_loop = True
                        break
                
                if skip_loop:
                    skip_loop = False
                    continue

                for line in uart_lines:
                    if b'Encoder Board' in line:
                        self.EncoderPort = port
                        skip_loop = True
                        break

                if skip_loop:
                    skip_loop = False
                    continue
                
                self.SensorPort = port


    def connectAndRead(self, port):
        xlines = []
        print(f"Opening Port : {port[0]}")
        indx = 0
        try:
            uart = serial.Serial(port[0], baudrate=115200, timeout=1)
            time.sleep(1.5)
            #while uart.in_waiting:
            while indx < 10:
                indx += 1
                line = uart.readline()
                #print(line.decode('ascii'))
                #time.sleep(0.2)
                xlines.append(line)
                if len(xlines) > 10:
                    break
            if len(xlines) > 0:
                return xlines
            else:
                return ["NONE"]
        
        except Exception as e:
            print(f"Error Connect Or Reading Serial Port:{port[0]} " + str(e))
            return None

class AutoDetectMarlin(QObject):
    def __init__(self):
        pass
