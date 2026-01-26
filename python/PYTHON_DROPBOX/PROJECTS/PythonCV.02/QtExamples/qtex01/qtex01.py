__author__      = "Saulius Lukse"
__copyright__   = "Copyright 2016, kurokesu.com"
__version__ = "0.1"
__license__ = "GPL"


from PyQt5 import QtCore, QtGui, uic
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget
import sys
import cv2
import numpy as np
import threading
import time
import queue as Queue


running = False
capture_thread = None
form_class = uic.loadUiType("simple.ui")[0]
q = Queue.Queue()
 

def grab(cam, queue, width, height, fps):
    global running
    capture = cv2.VideoCapture(cam)
    capture.set(cv2.CAP_PROP_FRAME_WIDTH, width)
    capture.set(cv2.CAP_PROP_FRAME_HEIGHT, height)
    capture.set(cv2.CAP_PROP_FPS, fps)

    while(running):
        frame = {}        
        capture.grab()
        retval, img = capture.retrieve(0)
        frame["img"] = img

        if queue.qsize() < 10:
            queue.put(frame)
        else:
            print(queue.qsize())

class OwnImageWidget(QWidget):
    def __init__(self, parent=None):
        super(OwnImageWidget, self).__init__(parent)
        self.image = None

    def setImage(self, image):
        self.image = image
        sz = image.size()
        self.setMinimumSize(sz)
        self.update()

    def paintEvent(self, event):
        qp = QtGui.QPainter()
        qp.begin(self)
        if self.image:
            qp.drawImage(QtCore.QPoint(0, 0), self.image)
        qp.end()



class MyWindowClass(QMainWindow, form_class):
    def __init__(self, parent=None):
        QMainWindow.__init__(self, parent)
        self.setupUi(self)

        self.startButton.clicked.connect(self.start_clicked)
        
        self.window_width = self.ImgWidget.frameSize().width()
        self.window_height = self.ImgWidget.frameSize().height()
        self.ImgWidget = OwnImageWidget(self.ImgWidget)       

        #self.timer = QtCore.QTimer(self)
        #self.timer.timeout.connect(self.update_frame)
        #self.timer.start(1)


    def start_clicked(self):
        image = np.zeros((200, 200, 3), np.uint8)

        cv2.line(image, (0,199), (199, 0), (0,0,255), 2)

        cv2.rectangle(image,(20,20),(60,60),(255,0,0),1)

        cv2.circle(image,(80,80),10,(0,255,0),-1)

        cv2.ellipse(image,(99,99),(40,20),0,0,360,(128,128,128),-1)

        points = np.array([[100,5],[125,30],[175,20],[185,10]], np.int32)
        points = points.reshape((-1,1,2))
        cv2.polylines(image,[points],True,(255,255,0))

        cv2.putText(image,'Test',(80,180), cv2.FONT_HERSHEY_DUPLEX , 1, (255,0,255))

        self.update_frame(image)
        
        #global running
        #running = True
        #capture_thread.start()
        #self.startButton.setEnabled(False)
        #self.startButton.setText('Starting...')


    def update_frame(self, imge):
        #if not q.empty():
        self.startButton.setText('Camera is live')
        #frame = q.get()
        #img = frame["img"]

        img = imge

        img_height, img_width, img_colors = img.shape
        scale_w = float(self.window_width) / float(img_width)
        scale_h = float(self.window_height) / float(img_height)
        scale = min([scale_w, scale_h])

        if scale == 0:
            scale = 1
        
        img = cv2.resize(img, None, fx=scale, fy=scale, interpolation = cv2.INTER_CUBIC)
        #img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        height, width, bpc = img.shape
        bpl = bpc * width
        image = QtGui.QImage(img.data, width, height, bpl, QtGui.QImage.Format_RGB888)
        self.ImgWidget.setImage(image)

    def closeEvent(self, event):
        global running
        running = False



#capture_thread = threading.Thread(target=grab, args = (0, q, 1920, 1080, 30))

app = QApplication(sys.argv)
w = MyWindowClass(None)
w.setWindowTitle('Kurokesu PyQT OpenCV USB camera test panel')
w.show()
app.exec_()
