from qtpy.QtCore import Slot, QTimer, QThread, Signal, QObject, Qt
from PyQt5.QtCore import QBuffer, QByteArray, QIODevice, Qt
from PyQt5.QtMultimedia import QSound
from collections import deque

class WaveMapper(QObject):
    def __init__(self):
        QObject.__init__(self)
        # format = QAudioFormat()
        # format.setChannelCount(1)
        # format.setSampleRate(22050)
        # format.setSampleSize(16)
        # format.setCodec("audio/pcm")
        # format.setByteOrder(QAudioFormat.LittleEndian)
        # format.setSampleType(QAudioFormat.SignedInt)
        # self.output = QAudioOutput(format, self)
        # self.frequency = 100
        # self.volume = 15000
        # self.buffer = QBuffer()
        # self.data = QByteArray()
        # self.timer = QTimer()
        # self.timer.timeout.connect(self.PlayTimeOut)
        # self.melodylist = [[800, 100],[1200, 100],[500, 100]]

        self.qsnd = QSound("beep.wav")
        self.qsndin = QSound("bin.wav")
        self.qbeep = QSound('bfault.wav')

    def playBeep(self):
        
        self.qbeep.play()

    def playstart(self):
        pass
        # self.melodylen = len(self.melodylist)
        # self.changeFrequency(self.melodylist[self.melodylen-1][0])
        # self.createData()
        # self.timer.start(1)

    def PlayTimeOut(self):
        pass
        # if self.timer.isActive:
        #     self.timer.stop()
        # if self.melodylen:
        #     self.changeFrequency(self.melodylist[self.melodylen-1][0])
        #     self.createData()
        #     self.play()
        #     self.timer.start(self.melodylist[self.melodylen-1][1])
        #     self.melodylen -= 1
            #print(str(self.melodylen) + " , " + str(self.melodylist[self.melodylen-1][0]) + " , " + str(self.melodylist[self.melodylen-1][1]))

    def changeFrequency(self, value=0):
        pass
            # self.frequency = 100 + (value * 2)
            # s = "pitch = {} Hz".format(self.frequency)

    def play(self):
        pass
        # if self.output.state() == QAudio.ActiveState:
        #     self.output.stop()
        # if self.buffer.isOpen():
        #     self.buffer.close()
        # self.createData()
        # self.buffer.setData(self.data)
        # self.buffer.open(QIODevice.ReadOnly)
        # self.buffer.seek(0)
        # self.output.start(self.buffer)

    def playfile(self):
        self.qsnd.play()

    def playin(self):
        self.qsndin.play()

    def createData(self):
        pass
        '''
        create 2 seconds of data with 22050 samples per second,
        each sample being 16 bits (2 bytes)
        '''
        '''
        self.data.clear()
        #for k in range(1 * 22050):
        for k in range(int(22050 / 8)):
            t = k / 22050.0
            value = int(self.volume * sin(2 * pi * self.frequency * t))
            self.data.append(struct.pack("<h", value))
        '''

    def changeVolume(self, value):
        self.volume = value

    def BeepBeep(self):
        pass
    '''
        self.changeFrequency(2000)
        self.changeVolume(1000)
        self.play()
        '''

    def Beep(self):
        #Disable warnings (optional)
        ##GPIO.setwarnings(False)
        #Select GPIO mode
        ##GPIO.setmode(GPIO.BCM)
        #Set buzzer - pin 23 as output
        buzzer=23 
        ##GPIO.setup(buzzer,GPIO.OUT)
        #Run forever loop
        ##GPIO.output(buzzer,GPIO.HIGH)
        #sleep(0.5) # Delay in seconds
        ##GPIO.output(buzzer,GPIO.LOW)