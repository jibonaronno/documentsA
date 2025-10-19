
import math
import sys
from os.path import join, dirname, abspath
import json
import os
from flowsetup import JsonFlowSetup
import pprint
import math
from collections import deque

class FlowProcess(object):
    def __init__(self):
        self.sum_of_volume = 0.0
        try:
            config = JsonFlowSetup("flow.json")
            self.D_inlet = float(config.dict["D_inlet"])
            self.D_orifice = float(config.dict["D_orifice"])
            self.P_air = float(config.dict["P_air"])
            self.kcal = float(config.dict["kcal"])
            self.diameter_ratio = self.D_orifice / self.D_inlet
            self.orifice_area = (math.pi * (self.D_orifice * self.D_orifice)) / 4
            self.inlet_area = (math.pi * (self.D_inlet * self.D_inlet)) / 4
            self.CDD = self.orifice_area / self.inlet_area
            self.Korifice = self.orifice_area * math.sqrt(2/(self.P_air * (1-(self.diameter_ratio ** 4)))) * self.kcal

        except Exception as e:
            print("error in flowprocess")
            print(str(e))

        self.flow = 0.0        

    def CalculateFlowConst(self, deltap):
        if deltap < 0:
            deltap = -deltap
            return -math.sqrt((math.pi ** 2) * ((12 / 1000) ** 4) / 1.225 * 100 * deltap) * 1000
        else:
            return math.sqrt((math.pi ** 2) * ((12 / 1000) ** 4) / 1.225 * 100 * deltap) * 1000

    def CalculateFlow(self, deltap):
        result = 0.0
        d_result = 0.0
        try:
            #if(deltap > 0):
            if True:
                #return self.CDD * self.Korifice * math.sqrt(deltap * 100)
                result = (self.CDD ** 2) * (self.Korifice ** 2) * (deltap * 100)
                if result > 0:
                    self.flow = math.sqrt(result)
                    self.Volume(self.flow)
                    return math.sqrt(result) * 60000
                elif result < 0:
                    d_result = -result
                    self.flow = -math.sqrt(d_result)
                    self.Volume(self.flow)
                    return -math.sqrt(d_result) * 60000
                else:
                    self.flow = 0.0
                    return 0.0
            else:
                return 0.0
        except Exception as e:
            print("Exception : flowprocess::CalculateFlow(...)")
            print(str(e))
            return self.flow

    def sumofVolumes(self):
        pass

    flow_arr = deque()
    sum_of_rmsVolume = 0.0
    
    def rootVolume(self, flow):
        rmsVolume = 0.0

        self.flow_arr.append(flow)
        if len(self.flow_arr) > 2:
            self.flow_arr.popleft()
            rmsVolume = math.sqrt((((self.flow_arr[0] + self.flow_arr[1]) / 2) ** 2) * 6.25)

            if self.flow_arr[0] < 0:
                self.sum_of_rmsVolume -= rmsVolume
            else:
                self.sum_of_rmsVolume += rmsVolume
            return self.sum_of_rmsVolume
        else:
            return 0.0


    def Volume(self, flow):
        self.sum_of_volume += flow
        return self.sum_of_volume
