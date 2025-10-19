import sys
import serial
import pprint
import time
import enum
import queue
from queue import Queue
from os.path import join, dirname, abspath
from qtpy.QtCore import Slot, QTimer, QThread, Signal, QObject, Qt, QMutex

import multiprocessing


class Gsender(multiprocessing.Process):
    def __init__(self, serialport):
        super().__init__()
        self.serialport = serialport
        self.ConnectPort()
        self.port = ''

    def ConnectPort(self):
        try:
            self.port = serial.Serial(self.serialport, baudrate=115200, timeout=0)
        except Exception as e:
            print(str(e))         


    def run(self):
        while True:
            pass
