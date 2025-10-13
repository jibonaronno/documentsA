import numpy as np
import cv2
import subprocess
import os
import pprint
from picamera import PiCamera
from time import sleep
from datetime import datetime

class SerialModem(object):
    def __init__(self):
        self.p = None
        self.sts = None
        pass

    def Dialin(self):
        try:
            self.p = subprocess.Popen(["sudo", "pon",  "rnet"])
            self.sts = os.waitpid(self.p.pid, 0)
            print(self.sts)
        except Exception as e:
            print(str(e))

    def Hangup(self):
        try:
            self.p = subprocess.Popen(["sudo", "poff",  "rnet"])
            self.sts = os.waitpid(self.p.pid, 0)
            print(self.sts)
        except Exception as e:
            print(str(e))

