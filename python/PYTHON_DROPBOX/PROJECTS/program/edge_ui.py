# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'edge.ui'
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

class Ui_EdgeDialog(object):
    def setupUi(self, EdgeDialog):
        EdgeDialog.setObjectName(_fromUtf8("EdgeDialog"))
        EdgeDialog.resize(180, 88)
        self.buttonBox = QtGui.QDialogButtonBox(EdgeDialog)
        self.buttonBox.setGeometry(QtCore.QRect(20, 40, 121, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName(_fromUtf8("buttonBox"))
        self.label_3 = QtGui.QLabel(EdgeDialog)
        self.label_3.setGeometry(QtCore.QRect(10, 10, 71, 20))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.lineEdit = QtGui.QLineEdit(EdgeDialog)
        self.lineEdit.setGeometry(QtCore.QRect(70, 10, 101, 20))
        self.lineEdit.setObjectName(_fromUtf8("lineEdit"))

        self.retranslateUi(EdgeDialog)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("accepted()")), EdgeDialog.accept)
        QtCore.QObject.connect(self.buttonBox, QtCore.SIGNAL(_fromUtf8("rejected()")), EdgeDialog.reject)
        QtCore.QMetaObject.connectSlotsByName(EdgeDialog)

    def retranslateUi(self, EdgeDialog):
        EdgeDialog.setWindowTitle(_translate("EdgeDialog", "Edge Trigger Properties", None))
        self.label_3.setText(_translate("EdgeDialog", "Comment:", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    EdgeDialog = QtGui.QDialog()
    ui = Ui_EdgeDialog()
    ui.setupUi(EdgeDialog)
    EdgeDialog.show()
    sys.exit(app.exec_())

