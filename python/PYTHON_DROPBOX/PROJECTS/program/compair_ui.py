# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'compair.ui'
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

class Ui_CompairDialog(object):
    def setupUi(self, CompairDialog):
        CompairDialog.setObjectName(_fromUtf8("CompairDialog"))
        CompairDialog.resize(227, 144)
        self.buttonBox = QtGui.QDialogButtonBox(CompairDialog)
        self.buttonBox.setGeometry(QtCore.QRect(50, 110, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.label_5 = QtGui.QLabel(CompairDialog)
        self.label_5.setGeometry(QtCore.QRect(30, 10, 41, 16))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_7 = QtGui.QLabel(CompairDialog)
        self.label_7.setGeometry(QtCore.QRect(150, 10, 51, 16))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.comboBox_A = QtGui.QComboBox(CompairDialog)
        self.comboBox_A.setGeometry(QtCore.QRect(0, 30, 101, 22))
        self.comboBox_A.setObjectName(_fromUtf8("comboBox_A"))
        self.comboBox_B = QtGui.QComboBox(CompairDialog)
        self.comboBox_B.setGeometry(QtCore.QRect(120, 30, 101, 22))
        self.comboBox_B.setEditable(False)
        self.comboBox_B.setObjectName(_fromUtf8("comboBox_B"))
        self.label_8 = QtGui.QLabel(CompairDialog)
        self.label_8.setGeometry(QtCore.QRect(110, 10, 16, 16))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.spinBox_A = QtGui.QSpinBox(CompairDialog)
        self.spinBox_A.setGeometry(QtCore.QRect(0, 80, 101, 22))
        self.spinBox_A.setMinimum(-32767)
        self.spinBox_A.setMaximum(32767)
        self.spinBox_A.setObjectName(_fromUtf8("spinBox_A"))
        self.spinBox_B = QtGui.QSpinBox(CompairDialog)
        self.spinBox_B.setGeometry(QtCore.QRect(120, 80, 101, 22))
        self.spinBox_B.setMinimum(-32767)
        self.spinBox_B.setMaximum(32767)
        self.spinBox_B.setProperty("value", 0)
        self.spinBox_B.setObjectName(_fromUtf8("spinBox_B"))
        self.label_6 = QtGui.QLabel(CompairDialog)
        self.label_6.setGeometry(QtCore.QRect(20, 60, 51, 16))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.label_9 = QtGui.QLabel(CompairDialog)
        self.label_9.setGeometry(QtCore.QRect(140, 60, 51, 16))
        self.label_9.setObjectName(_fromUtf8("label_9"))

        self.retranslateUi(CompairDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), CompairDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), CompairDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(CompairDialog)

    def retranslateUi(self, CompairDialog):
        CompairDialog.setWindowTitle(_translate("CompairDialog", "Comparison Operator", None))
        self.label_5.setText(_translate("CompairDialog", "Source", None))
        self.label_7.setText(_translate("CompairDialog", "Source", None))
        self.label_8.setText(_translate("CompairDialog", "= ", None))
        self.label_6.setText(_translate("CompairDialog", "Constant", None))
        self.label_9.setText(_translate("CompairDialog", "Constant", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    CompairDialog = QtGui.QDialog()
    ui = Ui_CompairDialog()
    ui.setupUi(CompairDialog)
    CompairDialog.show()
    sys.exit(app.exec_())

