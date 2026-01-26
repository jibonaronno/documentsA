


#import popupDialogs
import copy
import sys
import os
import time
import re
import pickle #for saving the file
from PyQt4 import QtCore, QtGui
from PyQt4 import QtSvg
from PyQt4.QtGui import QApplication, QDialog, QMainWindow, QActionGroup
from PyQt4.QtGui import QPrinter, QPainter
from PyQt4.QtCore import Qt
from PyQt4.Qt import QFont
from PyQt4.Qt import QString
from PyQt4.Qt import QStringList

from main_window import Ui_main_window

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s


class mainWindowUI(QMainWindow):#mainwindow inheriting from QMainWindow here.

    def __init__(self):
        QDialog.__init__(self)
        self.ui = Ui_main_window()
        self.ui.setupUi(self)

    def signalConnection(self):
        self.ui.actionToolNew.connect()

    def showSampleDialog(self, strMsg):
        pass

if __name__=='__main__':
    app = QApplication(sys.argv)#makes a QtGui thing
    window = mainWindowUI()
    window.show()
    sys.exit(app.exec_())