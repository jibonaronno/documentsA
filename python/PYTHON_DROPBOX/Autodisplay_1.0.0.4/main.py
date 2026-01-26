


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
from sampledialog import Ui_sampleDiag

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s


class mainWindowUI(QMainWindow):#mainwindow inheriting from QMainWindow here.

    def __init__(self):
        super(mainWindowUI, self).__init__()
        #QDialog.__init__(self)
        self.ui = Ui_main_window()
        self.ui.setupUi(self)
        self.signalConnection()
        self.ui.menubar.hide()
        #self.ui.toolBar.hide()
        self.statusBar().showMessage('Ready')

    def showOpenFileDialog(self):
        #open_dialog = QtGui.QFileDialog()
        #open_dialog.getOpenFileNameAndFilter(self, 'Open File', '*.csv')
        fname = QtGui.QFileDialog.getOpenFileNameAndFilter(self, 'Open file', '.', '*.py')
        self.statusBar().showMessage(fname[0]+' -- '+fname[1])

    def signalConnection(self):
        #self.connect(self.ui.actionToolNew, QtCore.SIGNAL("triggered()"), lambda: self.showSampleDialog())
        self.ui.actionToolNew.triggered.connect(self.showOpenFileDialog)

    def showSampleDialog(self):
        diag = QtGui.QDialog()
        ui = Ui_sampleDiag()
        ui.setupUi(diag)
        #resp = diag.show() #does not work properly
        diag.exec_()

if __name__=='__main__':
    app = QApplication(sys.argv)#makes a QtGui thing
    window = mainWindowUI()
    window.show()
    sys.exit(app.exec_())