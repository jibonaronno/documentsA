# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'move.ui'
#
# Created: Mon Sep 15 16:35:14 2014
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

class Ui_MoveDialog(object):
    def setupUi(self, MoveDialog):
        MoveDialog.setObjectName(_fromUtf8("MoveDialog"))
        MoveDialog.resize(227, 144)
        self.buttonBox = QtGui.QDialogButtonBox(MoveDialog)
        self.buttonBox.setGeometry(QtCore.QRect(50, 110, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.label_5 = QtGui.QLabel(MoveDialog)
        self.label_5.setGeometry(QtCore.QRect(30, 10, 41, 16))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_7 = QtGui.QLabel(MoveDialog)
        self.label_7.setGeometry(QtCore.QRect(150, 10, 51, 16))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.comboBox_A = QtGui.QComboBox(MoveDialog)
        self.comboBox_A.setGeometry(QtCore.QRect(0, 30, 101, 22))
        self.comboBox_A.setObjectName(_fromUtf8("comboBox_A"))
        self.comboBox_B = QtGui.QComboBox(MoveDialog)
        self.comboBox_B.setGeometry(QtCore.QRect(120, 30, 101, 22))
        self.comboBox_B.setEditable(False)
        self.comboBox_B.setObjectName(_fromUtf8("comboBox_B"))
        self.label_8 = QtGui.QLabel(MoveDialog)
        self.label_8.setGeometry(QtCore.QRect(110, 10, 16, 16))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.spinBox_A = QtGui.QSpinBox(MoveDialog)
        self.spinBox_A.setGeometry(QtCore.QRect(0, 80, 101, 22))
        self.spinBox_A.setMinimum(-32767)
        self.spinBox_A.setMaximum(32767)
        self.spinBox_A.setObjectName(_fromUtf8("spinBox_A"))
        self.spinBox_B = QtGui.QSpinBox(MoveDialog)
        self.spinBox_B.setGeometry(QtCore.QRect(120, 80, 101, 22))
        self.spinBox_B.setMinimum(-32767)
        self.spinBox_B.setMaximum(32767)
        self.spinBox_B.setProperty("value", 0)
        self.spinBox_B.setObjectName(_fromUtf8("spinBox_B"))
        self.label_6 = QtGui.QLabel(MoveDialog)
        self.label_6.setGeometry(QtCore.QRect(20, 60, 51, 16))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.label_9 = QtGui.QLabel(MoveDialog)
        self.label_9.setGeometry(QtCore.QRect(140, 60, 51, 16))
        self.label_9.setObjectName(_fromUtf8("label_9"))

        self.retranslateUi(MoveDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), MoveDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), MoveDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(MoveDialog)

    def retranslateUi(self, MoveDialog):
        MoveDialog.setWindowTitle(_translate("MoveDialog", "Move", None))
        self.label_5.setText(_translate("MoveDialog", "Source", None))
        self.label_7.setText(_translate("MoveDialog", "Source", None))
        self.label_8.setText(_translate("MoveDialog", "= ", None))
        self.label_6.setText(_translate("MoveDialog", "Constant", None))
        self.label_9.setText(_translate("MoveDialog", "Constant", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    MoveDialog = QtGui.QDialog()
    ui = Ui_MoveDialog()
    ui.setupUi(MoveDialog)
    MoveDialog.show()
    sys.exit(app.exec_())

