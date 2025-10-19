import sys
import serial
import pprint
import time
import enum
import queue
from queue import Queue
from os.path import join, dirname, abspath
from qtpy.QtCore import Slot, QTimer, QThread, Signal, QObject, Qt, QMutex

class GcodeStates(enum.Enum):
    WAIT_FOR_TIMEOUT = 1
    GCODE_SENT = 2
    READY_TO_SEND = 3

class BipapInitializationThread(QObject):
    signal = Signal(str)
    ppsignal = Signal(list)

    def __init__(self, serialPort, codegen, que):
        self.pressureque = que
        self.serialPort = serialPort
        self.position_pressure_list = []
        #self.json = JsonSettings("settings.json")
        self.codegen = codegen #GcodeGenerator(int(self.json.dict['vt']), int(self.json.dict['rr']), int(self.json.dict['ie']), int(self.json.dict['fio2']))
        self.codegen.GenerateCMV()
        self.codelist = self.codegen.gcodeinit.splitlines()
        self.flagStop = False
        self.variableDt = self.codegen.Dt
        self.ustr = ""
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
                #self.serialPort.reset_input_buffer()
                self.serialPort.write((str(line) + "\r\n").encode("utf-8"))
                time.sleep(0.5)
                in_waiting = self.serialPort.in_waiting
                while in_waiting == 0:
                    time.sleep(1)
                    in_waiting = self.serialPort.in_waiting
                    
                jMessage = ""
                while self.serialPort.in_waiting:
                    #print(self.serialPort.readline().decode('ascii'))
                    lst = self.serialPort.readlines()
                    for itm in lst:
                        try:
                            jMessage += itm.decode('ascii')
                        except:
                            pass
                        #jMessage += self.serialPort.readline().decode('ascii')
                    if "busy" in jMessage:
                        time.sleep(1)
                        continue
                self.signal.emit(str(line) + " - " + jMessage)

            while self.variableDt < self.codegen.Dp:
                if self.flagStop:
                    break
                try:
                    self.ustr = "G01 X"+str(self.variableDt) + " Y"+str(self.variableDt)+"\r\n"
                    self.serialPort.write((self.ustr.encode("utf-8")))
                    
                    if self.pressureque.qsize() > 0:
                        self.pressureque.get(False)
                    time.sleep(0.12)
                    in_waiting = self.serialPort.in_waiting
                    #while in_waiting == 0:
                        #time.sleep(0.1)
                        #in_waiting = self.serialPort.in_waiting
                        #self.serialPort.reset_input_buffer()
                    while self.pressureque.qsize() <= 0:
                        pass

                    if self.pressureque.qsize() > 0:
                        pressure = self.pressureque.get(False)
                        if "\n" in pressure:
                            pass
                        else:
                            self.position_pressure_list.append([self.variableDt, pressure])
                            self.variableDt += 1

                except serial.SerialException as ex:
                    print("Error In SerialException During Bipap Pushing" + str(ex.strerror))
                    self.signal.emit("Endbipapinit")
                except Exception as e:
                    print("Error In Exception During Bipap Pushing")
                    pprint.pprint(e)
                    self.signal.emit("Endbipapinit")
            
            self.ppsignal.emit(self.position_pressure_list)

            self.ustr = "G01 X"+str(self.codegen.Dt) + " Y"+str(self.codegen.Dt)+"\r\n"
            self.serialPort.write((self.ustr.encode("utf-8")))
            pprint.pprint(self.position_pressure_list)
            print("pressure list from thread")

            self.signal.emit("Endbipapinit")
        except serial.SerialException as ex:
            print("Error In SerialException" + str(ex.strerror))
            self.signal.emit("Stopped")
        except Exception as e:
            print('Error From Bipap run..')
            pprint.pprint(e)
            self.signal.emit("Stopped")

class PrimaryThread(QObject):
    signal = Signal(str)

    def __init__(self, serialPort, codegen):
        self.serialPort = serialPort
        #self.json = JsonSettings("settings.json")
        self.codegen = codegen #GcodeGenerator(int(self.json.dict['vt']), int(self.json.dict['rr']), int(self.json.dict['ie']), int(self.json.dict['fio2']))
        self.codegen.GenerateCMV()
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
                #self.serialPort.reset_input_buffer()
                self.serialPort.write((str(line) + "\r\n").encode("utf-8"))
                time.sleep(0.5)
                in_waiting = self.serialPort.in_waiting
                while in_waiting == 0:
                    time.sleep(1)
                    in_waiting = self.serialPort.in_waiting
                    
                jMessage = ""
                while self.serialPort.in_waiting:
                    #print(self.serialPort.readline().decode('ascii'))
                    lst = self.serialPort.readlines()
                    for itm in lst:
                        try:
                            jMessage += itm.decode('ascii')
                        except:
                            pass
                        #jMessage += self.serialPort.readline().decode('ascii')
                    if "busy" in jMessage:
                        time.sleep(1)
                        continue
                self.signal.emit(str(line) + " - " + jMessage)
            self.signal.emit("StoppedOK")
        except serial.SerialException as ex:
            print("Error In SerialException" + ex.strerror)
            self.signal.emit("Stopped")
        except Exception as e:
            pprint.pprint(e)
            self.signal.emit("Stopped")

class BipapThread(QObject):
    signal = Signal(str)
    def __init__(self, serl, codegen, que):
        self.pressureque = que
        self.serl = serl
        self.codegen = codegen
        self.codegen.GenerateCMV()
        self.codelist = self.codegen.gcodestr.splitlines()
        self.linecount = len(self.codelist)
        self.flagStop = False
        self.pause = True
        self.gcode_exec_state = GcodeStates.READY_TO_SEND
        self.gcode_move_count = 0
        self.presentPosition = (0,0)
        self.Tic = 0
        self.Toc = 0
        self.xyIncr = self.codegen.Dt
        self.gstr = ""
        self.sremsg = ""
        self.serialmutex = QMutex()
        self.startdelay = -1
        super().__init__()

    def gcodestep(self):
        self.gstr = "G01 X" + str(self.xyIncr) + " Y" + str(self.xyIncr) + " F1000\r\n"
        if self.xyIncr < self.codegen.xmax:
            self.xyIncr += 1

    def Stop(self):
        self.flagStop = True

    def updateGcode(self, codegen):
        self.codegen = codegen
        self.codegen.GenerateCMV()
        self.codelist = self.codegen.gcodestr.splitlines()

    def StartMoving(self):
        self.pause = False

    def StartMovingAfter(self, delay):
        self.startdelay = delay

    def StopMoving(self):
        self.pause = True
        self.xyIncr = self.codegen.Dt

    @Slot()
    def run(self):
        lst = []
        while 1:
            if self.flagStop:
                break
            try:
                if not self.pause:
                    if self.gcode_exec_state == GcodeStates.READY_TO_SEND:
                        self.gcodestep()
                        self.serialmutex.lock()
                        self.serl.write(self.gstr.encode("utf-8"))
                        self.serialmutex.unlock()
                        self.gcode_move_count += 1
                        if self.gcode_move_count >= 130:
                            #self.pause = True
                            self.gcode_move_count = 0
                        else:
                            self.gcode_exec_state = GcodeStates.WAIT_FOR_TIMEOUT
                            self.Tic = time.perf_counter()
                    if self.gcode_exec_state == GcodeStates.WAIT_FOR_TIMEOUT:
                        if (time.perf_counter() - self.Tic) >= 0.15:
                            #print("Gcode Executed\r\n")
                            self.gcode_exec_state = GcodeStates.READY_TO_SEND
                elif self.startdelay > 0:
                    time.sleep(self.startdelay)
                    self.startdelay = -1
                    self.pause = False
            except serial.SerialException as ex:
                print("Error In SerialException" + str(ex.strerror))

class EncoderThread(QObject):
    signal_pass_encoder = Signal(str)
    def __init__(self, serialport):
        self.rec_bytecount = 0
        self.line = []
        self.rec_data = ""
        self.flagStop = False
        self.serialport = serialport
        #self.thread = QThread()
        #self.thread.started.connect(self.run)
        #self.signal_pass_encoder.connect(callback)
        #self.moveToThread(self.thread)
        #self.thread.start()
        super().__init__()

    def Stop(self):
        self.flagStop = True

    @Slot()
    def run(self):
        while True:
            if self.flagStop:
                break
            else:
                jMessage = ""
                in_waiting = self.serialport.in_waiting
                while in_waiting == 0:
                    time.sleep(0.05)
                    in_waiting = self.serialport.in_waiting
                try:
                    lst = self.serialport.readlines()
                except:
                    pass
                for itm in lst:
                    try:
                        jMessage = itm.decode('ascii')
                        self.signal_pass_encoder.emit(jMessage)
                    except:
                        pass

'''
                for char in self.serialport.read():
                    self.line.append(chr(char))
                    if chr(char) == '\n':
                        self.rec_data = "".join(self.line)
                        self.line.clear()
                        self.signal_pass_encoder.emit(self.rec_data)
                        #print(self.rec_data)
'''

'''
class WorkerThread(QObject):
    signal = Signal(str)
    def __init__(self, serialPort, codegen, commandque:Queue):
        self.serialPort = serialPort
        self.codegen = codegen
        self.commandque = commandque
        self.codelist = self.codegen.gcodestr.splitlines()
        self.linecount = len(self.codelist)
        self.flagexit = False
        self.flagStop = False
        super().__init__()
        self.respondQue = Queue()

    def Stop(self):
        self.flagStop = True

    def Resume(self):
        self.flagStop = False

    def updateGcode(self, codegen):
        self.codegen = codegen
        self.codelist = self.codegen.gcodestr.splitlines()

    @Slot()
    def run(self):
        lst = []
        while 1:
            if self.flagStop:
                time.sleep(1)
                if self.respondQue.qsize() <= 0:
                    self.respondQue.put("stopped")
                continue
            if self.commandque.qsize() > 0:
                if self.commandque.get() == "exit":
                    self.flagexit = True
                    break
            try:
                for line in self.codelist:
                    self.serialPort.write((str(line)+"\r\n").encode('utf-8'))
                    time.sleep(0.1)
                    in_waiting = self.serialPort.in_waiting
                    while in_waiting == 0:
                        time.sleep(0.5) #1
                        in_waiting = self.serialPort.in_waiting

                    jMessage = ""
                    while "ok" not in jMessage:
                        while self.serialPort.in_waiting:
                            lst = self.serialPort.readlines()
                            for itm in lst:
                                jMessage += itm.decode('ascii')
                    self.signal.emit(str(line) + " - " + jMessage)
                    
            except serial.SerialException as ex:
                print("Error In SerialException" + str(ex))
'''

class WorkerThread(QObject):
    signal = Signal(str)
    def __init__(self, serialPort, codegen, commandque:Queue):
        self.serialport = serialPort
        self.codegen = codegen
        self.commandque = commandque
        self.codelist = self.codegen.gcodestr.splitlines()
        self.linecount = len(self.codelist)
        self.flagexit = False
        self.flagStop = False
        super().__init__()
        self.respondQue = Queue()

    def Stop(self):
        self.flagStop = True

    def Resume(self):
        self.flagStop = False

    def updateGcode(self, codegen):
        self.codegen = codegen
        self.codelist = self.codegen.gcodestr.splitlines()

    @Slot()
    def run(self):
        jMessage:str = ""
        unit:bytes = b''
        itm:str = ''
        in_waiting:int = 0
        while 1:
            if self.flagStop:
                time.sleep(1)
                if self.respondQue.qsize() <= 0:
                    self.respondQue.put("stopped")
                continue
            if self.commandque.qsize() > 0:
                if self.commandque.get() == "exit":
                    self.flagexit = True
                    break
            try:
                for line in self.codelist:
                    self.serialport.write((str(line)+"\r\n").encode('utf-8'))
                    time.sleep(0.5)

                    jMessage = ''
                    
                    while 'ok' not in jMessage:
                        try:
                            in_waiting = self.serialport.in_waiting
                        except Exception as e:
                            print('Ex:0X17 : ' + str(e))
                        
                        '''
                        while in_waiting == 0:
                            time.sleep(0.05)
                            try:
                                in_waiting = self.serialport.in_waiting
                            except Exception as e:
                                print('Ex:0x18 : ' + str(e))
                        '''
                        try:
                            while in_waiting == 0:
                                time.sleep(0.02)
                                in_waiting = self.serialport.in_waiting
                            unit = self.serialport.read(in_waiting)
                        except Exception as e:
                            print('Ex in sensor Thread readline() 392 : ' + str(e))
                
                        if len(unit) > 0:
                            try:
                                itm += unit.decode('ascii')
                            except:
                                pass
                        #else:
                        #    time.sleep(0.1)

                        if b'\n' in unit:
                            jMessage = itm #.decode('ascii')
                            itm = ''
                            self.signal.emit(str(line) + " - " + jMessage)

                            if 'ok' not in jMessage:
                                pass
                                #time.sleep(0.01)
                    
            except serial.SerialException as ex:
                print("Error In SerialException WorkerThread L- 410 : " + str(ex))


class BipapWorkerThread(QObject):
    signal = Signal(str)
    def __init__(self, serialPort, codegen, commandque:Queue):
        self.serialPort = serialPort
        self.codegen = codegen
        self.commandque = commandque
        self.codelist = self.codegen.gcodestr.splitlines()
        self.linecount = len(self.codelist)
        self.flagexit = False
        self.flagStop = False
        super().__init__()
        self.respondQue = Queue()

    def Stop(self):
        self.flagStop = True

    def Resume(self):
        self.flagStop = False

    def updateGcode(self, codegen):
        self.codegen = codegen
        self.codelist = self.codegen.gcodestr.splitlines()

    @Slot()
    def run(self):
        lst = []
        while 1:
            if self.flagStop:
                time.sleep(1)
                if self.respondQue.qsize() <= 0:
                    self.respondQue.put("stopped")
                continue
            if self.commandque.qsize() > 0:
                if self.commandque.get() == "exit":
                    self.flagexit = True
                    break
            try:
                for line in self.codelist:
                    self.serialPort.write((str(line)+"\r\n").encode('utf-8'))
                    time.sleep(0.1)
                    in_waiting = self.serialPort.in_waiting
                    while in_waiting == 0:
                        time.sleep(0.5) #1
                        in_waiting = self.serialPort.in_waiting

                    jMessage = ""
                    while "ok" not in jMessage:
                        while self.serialPort.in_waiting:
                            lst = self.serialPort.readlines()
                            for itm in lst:
                                try:
                                    jMessage += itm.decode('ascii')
                                except:
                                    pass
                    self.signal.emit(str(line) + " - " + jMessage)
                    
            except serial.SerialException as ex:
                print("Error In SerialException" + str(ex))

class SensorThread(QObject):
    signal = Signal(str)
    plst = []
    def __init__(self, serialPort, que):
        self.pressureque = que
        self.serialport = serialPort
        self.flagStop = False
        self.jMessage = ""
        self._beep = False
        self.flag_sensorlimit_tx = False
        self.strdata = ""
        super().__init__()

    def Stop(self):
        self.flagStop = True

    def beep(self):
        self._beep = True

    def txsensordata(self, strdata):
        self.strdata = strdata
        self.flag_sensorlimit_tx = True

    @Slot()
    def run(self):
        in_waiting = ''
        jMessage = ""
        unit = ''
        itm = ''
        while 1:
            if self.flagStop:
                break
            try:
                in_waiting = self.serialport.in_waiting
            except Exception as e:
                print('Ex:0X07 : ' + str(e))
                
            while in_waiting == 0:
                time.sleep(0.01)
                try:
                    in_waiting = self.serialport.in_waiting
                except Exception as e:
                    print('Ex:0x08 : ' + str(e))
            try:
                unit = self.serialport.read(in_waiting)
            except Exception as e:
                print('Ex in sensor Thread readline() 527 : ' + str(e))
            
            if len(unit) > 0:
                try:
                    itm += unit.decode('ascii')
                except:
                    pass

            if b'\n' in unit:
                jMessage = itm #.decode('ascii')
                itm = ''
                #jMessage += ',' + str(time.perf_counter())
                self.plst = jMessage.split(",")
                self.signal.emit(jMessage)
                if self.pressureque.qsize() <= 0:
                    self.pressureque.put(self.plst[0])

            if self.flag_sensorlimit_tx:
                self.flag_sensorlimit_tx = False
                self.serialport.write(self.strdata.encode('utf-8'))
                time.sleep(0.5)
