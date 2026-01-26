# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'cont.ui'
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

class Ui_ContDialog(object):
    def setupUi(self, ContDialog):
        ContDialog.setObjectName(_fromUtf8("ContDialog"))
        ContDialog.resize(182, 137)
        self.buttonBox = QtGui.QDialogButtonBox(ContDialog)
        self.buttonBox.setGeometry(QtCore.QRect(30, 100, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.label_3 = QtGui.QLabel(ContDialog)
        self.label_3.setGeometry(QtCore.QRect(10, 10, 71, 20))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.label_5 = QtGui.QLabel(ContDialog)
        self.label_5.setGeometry(QtCore.QRect(10, 40, 50, 13))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_7 = QtGui.QLabel(ContDialog)
        self.label_7.setGeometry(QtCore.QRect(10, 70, 81, 16))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.lineEdit = QtGui.QLineEdit(ContDialog)
        self.lineEdit.setGeometry(QtCore.QRect(70, 10, 101, 20))
        self.lineEdit.setObjectName(_fromUtf8("lineEdit"))
        self.comboBox = QtGui.QComboBox(ContDialog)
        self.comboBox.setGeometry(QtCore.QRect(70, 40, 101, 22))
        self.comboBox.setObjectName(_fromUtf8("comboBox"))
        self.comboBox_2 = QtGui.QComboBox(ContDialog)
        self.comboBox_2.setGeometry(QtCore.QRect(70, 70, 101, 22))
        self.comboBox_2.setEditable(True)
        self.comboBox_2.setObjectName(_fromUtf8("comboBox_2"))

        self.retranslateUi(ContDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), ContDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), ContDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(ContDialog)

    def retranslateUi(self, ContDialog):
        ContDialog.setWindowTitle(_translate("ContDialog", "Contact Properties", None))
        self.label_3.setText(_translate("ContDialog", "Comment:", None))
        self.label_5.setText(_translate("ContDialog", "Input", None))
        self.label_7.setText(_translate("ContDialog", "Name:", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    ContDialog = QtGui.QDialog()
    ui = Ui_ContDialog()
    ui.setupUi(ContDialog)
    ContDialog.show()
    sys.exit(app.exec_())

