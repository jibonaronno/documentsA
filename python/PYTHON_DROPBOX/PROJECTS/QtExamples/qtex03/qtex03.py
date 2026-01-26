__author__      = "Saulius Lukse"
__copyright__   = "Copyright 2016, kurokesu.com"
__version__ = "0.1"
__license__ = "GPL"


from PyQt4 import QtCore, QtGui, uic
import sys
#import cv2
#import numpy as np

form_class = uic.loadUiType("simple.ui")[0]

class OwnImageWidget(QtGui.QWidget):
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



class MyWindowClass(QtGui.QMainWindow, form_class):
    def __init__(self, parent=None):
        QtGui.QMainWindow.__init__(self, parent)
        self.setupUi(self)

        self.startButton.clicked.connect(self.start_clicked)
        self.scene = QtGui.QGraphicsScene()
        self.graphicsView.setScene(self.scene)

        self.linearGradient = QtGui.QLinearGradient(-100, -100, 150, 150)
        self.linearGradient.setColorAt(0.0, QtCore.Qt.white)
        self.linearGradient.setColorAt(0.2, QtCore.Qt.green)
        self.linearGradient.setColorAt(1.0, QtCore.Qt.black)

        self.rect = self.scene.addRect(-100, -100, 150, 150, QtGui.QPen(QtCore.Qt.black, 5), QtGui.QBrush(self.linearGradient))
        self.rect.setFlag(QtGui.QGraphicsItem.ItemIsMovable)

        self.pix = QtGui.QPixmap.fromImage(QtGui.QImage('sample.svg'))
        self.pixmap = self.scene.addPixmap(self.pix)
        self.pixmap.setFlag(QtGui.QGraphicsItem.ItemIsMovable)

    def start_clicked(self):
        pen = QtGui.QPen(QtCore.Qt.black)
        pass

    '''
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
    '''

    def update_frame(self, imge):
        self.startButton.setText('Camera is live')
        img = imge
        img_height, img_width, img_colors = img.shape
        scale_w = 180 #float(self.window_width) / float(img_width)
        scale_h = 180 #float(self.window_height) / float(img_height)
        scale = min([scale_w, scale_h])
        if scale == 0:
            scale = 1
        #img = cv2.resize(img, None, fx=scale, fy=scale, interpolation = cv2.INTER_CUBIC)
        #img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        height, width, bpc = img.shape
        bpl = bpc * width
        image = QtGui.QImage(img.data, width, height, bpl, QtGui.QImage.Format_RGB888)
        #self.ImgWidget.setImage(image)

    def closeEvent(self, event):
        pass

app = QtGui.QApplication(sys.argv)
w = MyWindowClass(None)
w.setWindowTitle('Kurokesu PyQT OpenCV USB camera test panel')
w.show()
app.exec_()
