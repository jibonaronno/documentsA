#Codersarts python Assignment Help by top rated Expert

#If you need any help then contact to codersarts offcial website

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5 import QtWidgets, uic

class SubWindow(QWidget):
    def __init__(self, parent = None):
        super(SubWindow, self).__init__(parent)
        label = QLabel("Sub Window",  self)

    def closeEvent(self, event):
        event.ignore()

class MainWindow(QWidget):
    def __init__(self, parent = None):
        super(MainWindow, self).__init__(parent)
        openButton = QPushButton("Open Sub Window",  self)
        openButton.clicked.connect(self.openSub)


    def openSub(self):
        self.sub = SubWindow()
        self.sub.show()


    def closeEvent(self,event):
        widgetList = QApplication.topLevelWidgets()
        numWindows = len(widgetList)
        if numWindows > 1:
            event.accept()
        else:
            event.ignore()

app = QApplication(sys.argv)
mainWin =MainWindow()
mainWin.show()
sys.exit(app.exec_())
