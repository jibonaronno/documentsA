# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'PWM.ui'
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

class Ui_PWMDialog(object):
    def setupUi(self, PWMDialog):
        PWMDialog.setObjectName(_fromUtf8("PWMDialog"))
        PWMDialog.resize(217, 140)
        self.buttonBox = QtGui.QDialogButtonBox(PWMDialog)
        self.buttonBox.setGeometry(QtCore.QRect(40, 100, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.doubleSpinBox = QtGui.QDoubleSpinBox(PWMDialog)
        self.doubleSpinBox.setGeometry(QtCore.QRect(80, 40, 101, 22))
        self.doubleSpinBox.setDecimals(1)
        self.doubleSpinBox.setSingleStep(0.2)
        self.doubleSpinBox.setProperty("value", 50.0)
        self.doubleSpinBox.setObjectName(_fromUtf8("doubleSpinBox"))
        self.label_6 = QtGui.QLabel(PWMDialog)
        self.label_6.setGeometry(QtCore.QRect(10, 40, 61, 16))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.label_9 = QtGui.QLabel(PWMDialog)
        self.label_9.setGeometry(QtCore.QRect(190, 40, 20, 20))
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.comboBox = QtGui.QComboBox(PWMDialog)
        self.comboBox.setGeometry(QtCore.QRect(80, 70, 101, 22))
        self.comboBox.setObjectName(_fromUtf8("comboBox"))
        self.label_5 = QtGui.QLabel(PWMDialog)
        self.label_5.setGeometry(QtCore.QRect(20, 70, 41, 16))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_4 = QtGui.QLabel(PWMDialog)
        self.label_4.setGeometry(QtCore.QRect(20, 10, 71, 20))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.lineEdit = QtGui.QLineEdit(PWMDialog)
        self.lineEdit.setGeometry(QtCore.QRect(80, 10, 101, 20))
        self.lineEdit.setObjectName(_fromUtf8("lineEdit"))

        self.retranslateUi(PWMDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), PWMDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), PWMDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(PWMDialog)

    def retranslateUi(self, PWMDialog):
        PWMDialog.setWindowTitle(_translate("PWMDialog", "PWM", None))
        self.label_6.setText(_translate("PWMDialog", "Duty Cycle", None))
        self.label_9.setText(_translate("PWMDialog", "%", None))
        self.label_5.setText(_translate("PWMDialog", "Output", None))
        self.label_4.setText(_translate("PWMDialog", "Comment:", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    PWMDialog = QtGui.QDialog()
    ui = Ui_PWMDialog()
    ui.setupUi(PWMDialog)
    PWMDialog.show()
    sys.exit(app.exec_())

