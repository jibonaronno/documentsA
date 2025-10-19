
import enum

class MachineRunModes(enum.Enum):
    CMV = 1
    BiPAP = 2
    CPAP = 3
    PS = 4

class BipapReturns(enum.Enum):
    Continue = 1
    Stop = 2

class BipapLookup(object):
    def __init__(self):
        self.ipap = 8.0
    
    def setIpap(self, ipap=0.0):
        self.ipap = ipap

    def lookUp(self, pressure=0.0):
        if pressure > self.ipap:
            return True
        else:
            return False
