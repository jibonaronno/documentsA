# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main_window.ui'
#
# Created by: PyQt4 UI code generator 4.11.4
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

class Ui_main_window(object):
    def setupUi(self, main_window):
        main_window.setObjectName(_fromUtf8("main_window"))
        main_window.setWindowModality(QtCore.Qt.NonModal)
        main_window.resize(1054, 821)
        self.centralwidget = QtGui.QWidget(main_window)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.verticalLayout_2 = QtGui.QVBoxLayout(self.centralwidget)
        self.verticalLayout_2.setObjectName(_fromUtf8("verticalLayout_2"))
        main_window.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(main_window)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1054, 21))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        self.menuFile = QtGui.QMenu(self.menubar)
        self.menuFile.setObjectName(_fromUtf8("menuFile"))
        main_window.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(main_window)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        main_window.setStatusBar(self.statusbar)
        self.toolBar = QtGui.QToolBar(main_window)
        self.toolBar.setObjectName(_fromUtf8("toolBar"))
        main_window.addToolBar(QtCore.Qt.TopToolBarArea, self.toolBar)
        self.action_New_Page = QtGui.QAction(main_window)
        self.action_New_Page.setObjectName(_fromUtf8("action_New_Page"))
        self.action_Save = QtGui.QAction(main_window)
        self.action_Save.setObjectName(_fromUtf8("action_Save"))
        self.actionToolNew = QtGui.QAction(main_window)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8("svg/plus-button.svg")), QtGui.QIcon.Normal, QtGui.QIcon.On)
        self.actionToolNew.setIcon(icon)
        self.actionToolNew.setObjectName(_fromUtf8("actionToolNew"))
        self.actionToolSave = QtGui.QAction(main_window)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(_fromUtf8("svg/check.svg")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionToolSave.setIcon(icon1)
        self.actionToolSave.setObjectName(_fromUtf8("actionToolSave"))
        self.actionToolDelete = QtGui.QAction(main_window)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(_fromUtf8("svg/cancel.svg")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.actionToolDelete.setIcon(icon2)
        self.actionToolDelete.setObjectName(_fromUtf8("actionToolDelete"))
        self.menuFile.addAction(self.action_New_Page)
        self.menuFile.addAction(self.action_Save)
        self.menubar.addAction(self.menuFile.menuAction())
        self.toolBar.addAction(self.actionToolNew)
        self.toolBar.addAction(self.actionToolSave)
        self.toolBar.addAction(self.actionToolDelete)

        self.retranslateUi(main_window)
        QtCore.QMetaObject.connectSlotsByName(main_window)

    def retranslateUi(self, main_window):
        main_window.setWindowTitle(_translate("main_window", "AutoBinder", None))
        self.menuFile.setTitle(_translate("main_window", "&File", None))
        self.toolBar.setWindowTitle(_translate("main_window", "toolBar", None))
        self.action_New_Page.setText(_translate("main_window", "&New Page", None))
        self.action_Save.setText(_translate("main_window", "&Save", None))
        self.actionToolNew.setText(_translate("main_window", "ToolNew", None))
        self.actionToolNew.setToolTip(_translate("main_window", "New Page", None))
        self.actionToolSave.setText(_translate("main_window", "ToolSave", None))
        self.actionToolSave.setToolTip(_translate("main_window", "Save", None))
        self.actionToolDelete.setText(_translate("main_window", "ToolDelete", None))
        self.actionToolDelete.setToolTip(_translate("main_window", "Delete Page", None))

