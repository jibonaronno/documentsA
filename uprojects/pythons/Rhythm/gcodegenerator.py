import math
import sys
from os.path import join, dirname, abspath
from machinesetup import MachineSetup
import pprint

class GcodeGenerator(object):
    def __init__(self, vt, rr, ie, fio2, x_adj):
        self.vtfactor = 1.0
        self.vt = vt
        self.rr = rr
        self.ie = ie
        self.fio2 = fio2
        self.x_adj = x_adj
        self.ACC=1000
        self.xmax = 75 #60
        self.xamb = 40 #12
        self.xrect = 30
        self.xcon_offset = 5
        self.vtmax = 5000

        self.gcodebipap = ""
        self.bipapstep = 0
        self.gcodebipap_back = ""

        self.machinesetup = MachineSetup()
        self.ACC = self.machinesetup.ACC
        self.xmax = self.machinesetup.xmax
        self.xamb = self.machinesetup.xamb
        self.xrect = self.machinesetup.xrect
        self.xcon_offset = self.machinesetup.xcon_offset
        self.vtmax = self.machinesetup.vtmax
        self.motor_i_min = self.machinesetup.motor_i_min
        self.presmm = self.machinesetup.presmm
        self.postsmm = self.machinesetup.postsmm
        self.home_sense = self.machinesetup.home_sense
        self.ipap_tol = self.machinesetup.ipap_tol
        self.vol_tol = self.machinesetup.vol_tol
        print(str(self.ACC) + "," + str(self.xmax) + "," + str(self.xamb) + "," + str(self.xrect) + "," + str(self.xcon_offset) + "," + str(self.vtmax))
        self.calib_dict = {250:63.0, 300:68.0, 350:71.0, 400:73.0, 450:77.0, 500:86.0, 550:100.0}

        #self.calib_dict = {250:103.0, 300:108.0, 350:111.0, 400:113.0, 450:125.0, 500:126.0, 550:140.0}

    def getAxisdistanceFromIpap(self, pparr, ipap):
        try:
            if len(pparr) > 0:
                for itm in pparr:
                    if ipap == int(float(itm[1])) or ipap < int(float(itm[1])):
                        return itm[0]
            return -1
        except Exception as e:
            print("pospressure table is empty")
            pprint.pprint(e)
            return -1

    def ComputeBipap(self, pparr, ipap):
        xmax = 5
        xmax = self.getAxisdistanceFromIpap(pparr, ipap)
        print(f"Axis Distance :: {xmax}")
        if xmax == -1:
            self.ComputeCMV()
            print("Failed ComputeBipap()")
        else:
            self.ComputeMotion(xmax)
            print("ComputeMotion(xmax=" + str(xmax) + ") @ IPAP :: " + str(ipap) )

    def ComputeMotion(self, xmax_bp):
        self.Dt = self.xmax - self.xrect
        
        self.xav = self.xrect * (self.vt / self.vtmax)
        '''xav will come from table as below'''
        self.xav = self.calib_dict[self.vt]

        self.Dp = xmax_bp #self.Dt + self.xav
        self.TDMS = 0

        self.Kie =  1/self.ie
        self.BCT = 60*(1-0.24) / self.rr
        self.Ti = self.BCT / (1 + (1 / self.Kie))
        self.Th = self.BCT - self.Ti
        
        self.midpart_ti=(1-self.ACC*self.Ti*self.Ti)/2
        self.lastpart_ti=self.xav*self.xav/4
        self.identifier_ti=math.sqrt(self.midpart_ti*self.midpart_ti-4*self.lastpart_ti)
        self.sol1_ti=(-1*self.midpart_ti+self.identifier_ti)/2
        self.sol2_ti=(-1*self.midpart_ti-self.identifier_ti)/2

        if self.sol1_ti>self.xav:
            if self.sol2_ti>self.xav:
                self.dsmall_ti=0.1
            else:
                self.dsmall_ti=self.sol2_ti
        else:
            self.dsmall_ti=self.sol1_ti  
               
        #print(self.identifier_ti)
        self.midpart_th=(1-self.ACC*self.Th*self.Th)/2
        self.lastpart_th=self.xav*self.xav/4
        self.identifier_th=math.sqrt(self.midpart_th*self.midpart_th-4*self.lastpart_th)
        self.sol1_th=(-1*self.midpart_th+self.identifier_th)/2
        self.sol2_th=(-1*self.midpart_th-self.identifier_th)/2

        if self.sol1_th>self.xav:
            if self.sol2_th>self.xav:
                self.dsmall_th=0.1
            else:
                self.dsmall_th=self.sol2_th
        else:
            self.dsmall_th=self.sol1_th 

        #self.ACC_inhale = (4 * self.xav) / (self.Ti * self.Ti)
        #self.ACC_exhale = (4 * self.xav) / (self.Th * self.Th)
        #self.Vi = self.ACC_inhale * (self.Ti / 2) * 60
        #self.Vh = self.ACC_exhale * (self.Th / 2) * 60
        self.vimax=math.sqrt(2*self.dsmall_ti*self.ACC)
        self.vhmax=math.sqrt(2*self.dsmall_th*self.ACC)
        self.ViAvg = self.vimax * 60
        #print(self.ViAvg)
        self.Vi = self.ViAvg
        self.VhAvg = self.vhmax* 60
        self.Vh = self.VhAvg

    xavv = 0
    
    def ComputeCMV(self):
        self.xavv = self.x_adj
        self.Dt = self.xmax - self.xrect
        #self.xav = self.calib_dict[self.vt]
        #self.xav = self.xrect * (self.vt / self.vtmax) * self.vtfactor
        try:
            self.xav = self.calib_dict[self.vt] + self.xavv
            print('Dict : ' + str(self.calib_dict[self.vt]))
        except Exception as e:
            print('ComputeCMV - ' + str(e))
            #self.xav = self.xavv

        #if self.xavv != 0:
            #self.xav = self.xrect * ((self.vt + self.x_adj) / self.vtmax) * self.vtfactor
        
        #Previous Dp self.Dp = self.Dt + self.xav
        self.Dp = self.xav
        self.TDMS = 0.5

        self.Kie =  1/self.ie
        self.BCT = 60*(1-0.32) / self.rr
        self.Ti = self.BCT / (1 + (1 / self.Kie))
        self.Th = self.BCT - self.Ti
        
        self.midpart_ti=(1-self.ACC*self.Ti*self.Ti)/2
        self.lastpart_ti=self.xav*self.xav/4
        self.identifier_ti=math.sqrt(self.midpart_ti*self.midpart_ti-4*self.lastpart_ti)
        self.sol1_ti=(-1*self.midpart_ti+self.identifier_ti)/2
        self.sol2_ti=(-1*self.midpart_ti-self.identifier_ti)/2

        if self.sol1_ti > self.xav:
            if self.sol2_ti > self.xav:
                self.dsmall_ti=0.1
            else:
                self.dsmall_ti=self.sol2_ti
        else:
            self.dsmall_ti=self.sol1_ti  
               
        #print(self.identifier_ti)
        self.midpart_th=(1-self.ACC*self.Th*self.Th)/2
        self.lastpart_th=self.xav*self.xav/4
        self.identifier_th=math.sqrt(self.midpart_th*self.midpart_th-4*self.lastpart_th)
        self.sol1_th=(-1*self.midpart_th+self.identifier_th)/2
        self.sol2_th=(-1*self.midpart_th-self.identifier_th)/2

        if self.sol1_th>self.xav:
            if self.sol2_th>self.xav:
                self.dsmall_th=0.1
            else:
                self.dsmall_th=self.sol2_th
        else:
            self.dsmall_th=self.sol1_th 

        #self.ACC_inhale = (4 * self.xav) / (self.Ti * self.Ti)
        #self.ACC_exhale = (4 * self.xav) / (self.Th * self.Th)
        #self.Vi = self.ACC_inhale * (self.Ti / 2) * 60
        #self.Vh = self.ACC_exhale * (self.Th / 2) * 60
        self.vimax=math.sqrt(2*self.dsmall_ti*self.ACC)
        self.vhmax=math.sqrt(2*self.dsmall_th*self.ACC)
        self.ViAvg = self.vimax * 60
        #print(self.ViAvg)
        self.Vi = self.ViAvg
        self.VhAvg = self.vhmax* 60
        self.Vh = self.VhAvg


    def ComputeCMV2(self):
        self.xavv = self.x_adj
        self.Dt = self.xmax - self.xrect
        initial_x = self.calib_dict[self.vt] #self.calib_dict[450]
        #self.xav = self.calib_dict[self.vt]
        #self.xav = self.xrect * (self.vt / self.vtmax) * self.vtfactor
        try:
            self.xav = initial_x + self.xavv
            print('Dict : ' + str(initial_x))
        except Exception as e:
            print('ComputeCMV - ' + str(e))
            #self.xav = self.xavv

        #if self.xavv != 0:
            #self.xav = self.xrect * ((self.vt + self.x_adj) / self.vtmax) * self.vtfactor
        
        self.Dp = self.Dt + self.xav
        # Mod self.Dp = self.xav
        self.TDMS = 0.5

        self.Kie =  1/self.ie
        #self.BCT = 60*(1-(-0.5)) / self.rr
        self.BCT = 60*(1-0.32) / self.rr
        self.Ti = self.BCT / (1 + (1 / self.Kie))
        self.Th = self.BCT - self.Ti

        print('Ti-{:f} Th-{:f} BCT-{:f}'.format(self.Ti, self.Th, self.BCT))
        
        self.midpart_ti=(1-self.ACC*self.Ti*self.Ti)/2
        self.lastpart_ti=self.xav*self.xav/4
        self.identifier_ti=math.sqrt(self.midpart_ti*self.midpart_ti-4*self.lastpart_ti)
        self.sol1_ti=(-1*self.midpart_ti+self.identifier_ti)/2
        self.sol2_ti=(-1*self.midpart_ti-self.identifier_ti)/2

        if self.sol1_ti > self.xav:
            if self.sol2_ti > self.xav:
                self.dsmall_ti=0.1
            else:
                self.dsmall_ti=self.sol2_ti
        else:
            self.dsmall_ti=self.sol1_ti  
               
        #print(self.identifier_ti)
        self.midpart_th=(1-self.ACC*self.Th*self.Th)/2
        self.lastpart_th=self.xav*self.xav/4
        self.identifier_th=math.sqrt(self.midpart_th*self.midpart_th-4*self.lastpart_th)
        self.sol1_th=(-1*self.midpart_th+self.identifier_th)/2
        self.sol2_th=(-1*self.midpart_th-self.identifier_th)/2

        if self.sol1_th>self.xav:
            if self.sol2_th>self.xav:
                self.dsmall_th=0.1
            else:
                self.dsmall_th=self.sol2_th
        else:
            self.dsmall_th=self.sol1_th 

        #self.ACC_inhale = (4 * self.xav) / (self.Ti * self.Ti)
        #self.ACC_exhale = (4 * self.xav) / (self.Th * self.Th)
        #self.Vi = self.ACC_inhale * (self.Ti / 2) * 60
        #self.Vh = self.ACC_exhale * (self.Th / 2) * 60
        self.vimax=math.sqrt(2*self.dsmall_ti*self.ACC)
        self.vhmax=math.sqrt(2*self.dsmall_th*self.ACC)
        self.ViAvg = self.vimax * 60
        #print(self.ViAvg)
        self.Vi = self.ViAvg
        self.VhAvg = self.vhmax* 60
        self.Vh = self.VhAvg


    def GenerateCMV(self):
        self.ComputeCMV2()
        self.gcodeinit = "G21\r\nG80\r\nG90\r\nM92 X" + str(self.presmm) +" Y"+ str(self.presmm) +"\r\nG28 X0Y0 F500\r\nM92 X" + str(self.postsmm) + " Y" + str(self.postsmm) + "\r\nM906 X"+ str(self.motor_i_min) + " Y" + str(self.motor_i_min) +"\r\nM201 X"+str(self.ACC)+" Y"+str(self.ACC)
        self.gcodeprimary = "G21\r\nG80\r\nG90\r\nM92 X"+ str(self.presmm) +" Y"+ str(self.presmm) + "\r\nM914 X" + str(self.home_sense) + " Y" + str(self.home_sense) +"\r\nG28 X0Y0 F500\r\nM92 X"+ str(self.postsmm) +" Y"+ str(self.postsmm) + "\r\nM201 X"+str(self.ACC)+" Y"+str(self.ACC) + "\r\nM906 X"+ str(self.motor_i_min) + " Y" + str(self.motor_i_min) + "\r\nG01 X" + str(int(self.Dp)) + " Y" + str(int(self.Dp)) + " F500\r\n" + "G01 X" + str(int(self.Dt))+" Y"+str(int(self.Dt))+" F500\r\n"
        #self.gcodeprimary = "G21\r\nG80\r\nG90\r\nM92 X"+ str(self.presmm) +" Y"+ str(self.presmm) +"\r\nG28 X0Y0 F500\r\nM92 X"+ str(self.postsmm) +" Y"+ str(self.postsmm) + "\r\nM201 X"+str(self.ACC)+" Y"+str(self.ACC) + "\r\nG01 X" + str(int(self.Dp)) + " Y" + str(int(self.Dp)) + " F500\r\n" + "G01 X" + str(int(self.Dt))+" Y"+str(int(self.Dt))+" F500\r\n"
        
        self.gcodestr =  "M107\r\nG01 X" + str(int(self.Dp))+" Y"+str(int(self.Dp))+" F"+str(int(self.ViAvg))+"\r\nM106 S255\r\nG04 P"+ str(self.TDMS) +"\r\n" +"G01 X"+str(int(self.Dt))+" Y"+str(int(self.Dt))+" F"+str(int(self.VhAvg))+"\r\n" #+"G04 P"+str(self.TDMS)+"\r\n"
        #self.gcodestr =  "G01 X" + str(int(self.Dp))+" Y"+str(int(self.Dp))+" F"+str(int(self.ViAvg))+"\r\n" +"G01 X"+str(int(self.Dt))+" Y"+str(int(self.Dt))+" F"+str(int(self.VhAvg))+"\r\n"

        #print(self.gcodeinit)
        #print("\r\n")
        ##print("Gcode Primary : ")
        ##print(self.gcodeprimary)
        #self.gcodestr = "M201 X" + str(int(self.ACC_inhale)) + " Y" + str(int(self.ACC_exhale)) + "\r\n" + " G01 X" + str(int(self.Dp))+" Y"+str(int(self.Dp))+" F"+str(int(self.Vi))+"\r\n"+ "M201 X"+ str(int(self.ACC_exhale)) + " Y"+ str(int(self.ACC_exhale)) + "\r\n" +" G01 X"+str(int(self.Dt))+" Y"+str(int(self.Dt))+" F"+str(int(self.Vh))+"\r\n" #+"G04 P"+str(self.TDMS)+"\r\n"
        #with open('primary.gcode', 'w') as writer:
            #writer.write(self.gcodeprimary)
        

    def GenerateBiPAP(self, pparr, ipap):
        self.ComputeBipap(pparr, ipap)
        self.gcodeinit = "G21\r\nG80\r\nG90\r\nM92 X80 Y80\r\nG28 X0Y0 F500\r\nM92 X800 Y800\r\nM201 X"+str(self.ACC)+" Y"+str(self.ACC)
        self.gcodeprimary = "G21\r\nG80\r\nG90\r\nG28 X0Y0 F500\r\nM92 X800 Y800\r\nM201 X"+str(self.ACC)+" Y"+str(self.ACC)+"\r\nG01 X" + str(int(self.Dp)) + " Y" + str(int(self.Dp)) + " F500\r\n" + "G01 X" + str(int(self.Dt))+" Y"+str(int(self.Dt))+" F500\r\n"
        self.gcodestr =  "M107\r\nG01 X" + str(int(self.Dp))+" Y"+str(int(self.Dp))+" F"+str(int(self.ViAvg))+"\r\nM106 S255\r\n" +"G01 X"+str(int(self.Dt))+" Y"+str(int(self.Dt))+" F"+str(int(self.VhAvg))+"\r\n" #+"G04 P"+str(self.TDMS)+"\r\n"

