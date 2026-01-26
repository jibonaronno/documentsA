# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ardIOnote.ui'
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

class Ui_ardIOnoteDialog(object):
    def setupUi(self, ardIOnoteDialog):
        ardIOnoteDialog.setObjectName(_fromUtf8("ardIOnoteDialog"))
        ardIOnoteDialog.resize(289, 167)
        self.buttonBox = QtGui.QDialogButtonBox(ardIOnoteDialog)
        self.buttonBox.setGeometry(QtCore.QRect(30, 120, 171, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.label = QtGui.QLabel(ardIOnoteDialog)
        self.label.setGeometry(QtCore.QRect(20, 10, 271, 101))
        palette = QtGui.QPalette()
        brush = QtGui.QBrush(QtGui.QColor(170, 0, 0))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.WindowText, brush)
        brush = QtGui.QBrush(QtGui.QColor(170, 0, 0))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.WindowText, brush)
        brush = QtGui.QBrush(QtGui.QColor(106, 104, 100))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.WindowText, brush)
        self.label.setPalette(palette)
        font = QtGui.QFont()
        font.setPointSize(12)
        self.label.setFont(font)
        self.label.setObjectName(_fromUtf8("label"))

        self.retranslateUi(ardIOnoteDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), ardIOnoteDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), ardIOnoteDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(ardIOnoteDialog)

    def retranslateUi(self, ardIOnoteDialog):
        ardIOnoteDialog.setWindowTitle(_translate("ardIOnoteDialog", "Changing Hardware Error.", None))
        self.label.setText(_translate("ardIOnoteDialog", "There are IO, PWM ,or ADC\n"
"numbers higher than\n"
"this hardwar supports.\n"
"\n"
"Please remove those elements \n"
"before choosing this hardware. ", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    ardIOnoteDialog = QtGui.QDialog()
    ui = Ui_ardIOnoteDialog()
    ui.setupUi(ardIOnoteDialog)
    ardIOnoteDialog.show()
    sys.exit(app.exec_())

