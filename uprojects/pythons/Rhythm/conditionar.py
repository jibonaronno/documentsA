

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
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QHBoxLayout, QGroupBox, QPushButton

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
from scipy.signal import butter,filtfilt
from filterlp import LowpassFilter

class StreamData(object):

    vol_base = 0.0
    deltaflow:float = 0.0
    deltaflowoffset:float = 0.0
    lungpressure:float = 0.0
    plot_run = True
    lst = []
    lines = []
    cntr = 0

    def __init__(self, step_duration):
        self.stepDuration = step_duration
        self.maxlength = 500
        self.pressure_stream = deque()
        self.flow_stream = deque()
        self.volume_stream = deque()
        self.ttm = 0.0
        self.tfdata = deque()
        self.lpf = LowpassFilter()
        self.filtered = []

    def push(self, data_stream):
        lungpressure = 0.0
        deltaflow = 0.0
        if not self.plot_run:
            return
        self.lines = data_stream.split('\n')
        if len(self.lines) > 0:
            for line in self.lines:
                self.lst = line.split(',')
                if len(self.lst) >= 3:
                    try:
                        lungpressure = float(self.lst[0])
                        deltaflow = float(self.lst[2])
                        self.pressure_stream.append(lungpressure)
                        self.flow_stream.append(deltaflow)
                        

                        if len(self.pressure_stream) > self.maxlength:
                            self.pressure_stream.popleft()
                            self.flow_stream.popleft()
                            self.filtered = self.lpf.butter_lowpass_filter(self.pressure_stream, cutoff=1, fs=10, order=2)

                        if len(self.tfdata) < self.maxlength:
                            self.ttm += self.stepDuration
                            self.tfdata.append(self.ttm)

                    except Exception as e:
                        print(data_stream + ' : ' + str(e))

                    if self.cntr < 10:
                        self.cntr += 1
                    else:
                        self.cntr = 0
                        print('{:f} :: {:f}'.format(lungpressure, deltaflow))
                else:
                    pass #print('sensor data stream length missmatch : ' + str(len(self.lst)))
