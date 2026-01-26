# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'IOHelp.ui'
#
# Created: Mon Sep 15 16:35:13 2014
#      by: PyQt4 UI code generator 4.10.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_IODialog(object):
    def setupUi(self, IODialog):
        IODialog.setObjectName(_fromUtf8("IODialog"))
        IODialog.resize(539, 316)
        self.buttonBox = QtGui.QDialogButtonBox(IODialog)
        self.buttonBox.setGeometry(QtCore.QRect(200, 280, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.textBrowser = QtGui.QTextBrowser(IODialog)
        self.textBrowser.setGeometry(QtCore.QRect(10, 10, 521, 261))
        self.textBrowser.setObjectName(_fromUtf8("textBrowser"))

        self.retranslateUi(IODialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), IODialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), IODialog.reject)
        QtCore.QMetaObject.connectSlotsByName(IODialog)

    def retranslateUi(self, IODialog):
        IODialog.setWindowTitle(_translate("IODialog", "I/O diagram", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    IODialog = QtGui.QDialog()
    ui = Ui_IODialog()
    ui.setupUi(IODialog)
    IODialog.show()
    sys.exit(app.exec_())

