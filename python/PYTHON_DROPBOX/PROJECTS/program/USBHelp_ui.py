# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'USBHelp.ui'
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

class Ui_USBDialog(object):
    def setupUi(self, USBDialog):
        USBDialog.setObjectName(_fromUtf8("USBDialog"))
        USBDialog.resize(539, 316)
        self.buttonBox = QtGui.QDialogButtonBox(USBDialog)
        self.buttonBox.setGeometry(QtCore.QRect(200, 280, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.textBrowser = QtGui.QTextBrowser(USBDialog)
        self.textBrowser.setGeometry(QtCore.QRect(10, 10, 521, 261))
        self.textBrowser.setObjectName(_fromUtf8("textBrowser"))

        self.retranslateUi(USBDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), USBDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), USBDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(USBDialog)

    def retranslateUi(self, USBDialog):
        USBDialog.setWindowTitle(_translate("USBDialog", "USB udev rules instructions", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    USBDialog = QtGui.QDialog()
    ui = Ui_USBDialog()
    ui.setupUi(USBDialog)
    USBDialog.show()
    sys.exit(app.exec_())

