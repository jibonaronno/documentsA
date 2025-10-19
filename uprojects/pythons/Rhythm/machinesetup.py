import math
import sys
from os.path import join, dirname, abspath
import json
import os

class JsonMachineSetup(object):
    def __init__(self , location):
        self.location = os.path.expandvars(location)
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

class MachineSetup(object):
    def __init__(self):
        self.jsn = JsonMachineSetup("machinesetup.json")
        self.ACC = int(self.jsn.dict['ACC'])
        self.xmax = int(self.jsn.dict['xmax'])
        self.xamb = int(self.jsn.dict['xamb'])
        self.xrect = int(self.jsn.dict['xrect'])
        self.xcon_offset = int(self.jsn.dict['xcon_offset'])
        self.vtmax = int(self.jsn.dict['vtmax'])
        self.motor_i_min = int(self.jsn.dict['motor_i_min'])
        self.presmm = int(self.jsn.dict['pre_step_mm'])
        self.postsmm = int(self.jsn.dict['post_step_mm'])
        self.home_sense = int(self.jsn.dict['home_sense'])
        self.ipap_tol = int(self.jsn.dict['ipap_tol'])

        self.vol_tol = int(self.jsn.dict['vol_tol'])

    def save(self):
        self.jsn.dict['ACC'] = str(self.ACC)
        self.jsn.dict['xmax'] = str(self.xmax)
        self.jsn.dict['xamb'] = str(self.xamb)
        self.jsn.dict['xrect'] = str(self.xrect)
        self.jsn.dict['xcon_offset'] = str(self.xcon_offset)
        self.jsn.dumptojson()