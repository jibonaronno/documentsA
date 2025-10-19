#PyQT Help by Codersarts
#If you have any problem with python with any cross-platform toolkit then contact codersarts 

import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5 import QtWidgets, uic


class MainWindow(QtWidgets.QMainWindow):
   count = 0
	
   def __init__(self, parent = None):
      super(MainWindow, self).__init__(parent)
      self.mdi = QMdiArea()
      self.setCentralWidget(self.mdi)
      bar = self.menuBar()
		
      file = bar.addMenu("Subwindow")
      file.addAction("window1")
      file.addAction("text1")
      file.addAction("text2")
      file.triggered[QAction].connect(self.click)
      self.setWindowTitle("Multiple window using MDI")
		
   def click(self, q):
       print ("New sub window")

       if q.text() == "window1":
          MainWindow.count = MainWindow.count+1
          sub = QMdiSubWindow()
          sub.setWidget(QTextEdit())
          sub.setWindowTitle("subwindow"+str(MainWindow.count))
          self.mdi.addSubWindow(sub)
          sub.show()
                    
       if q.text() == "text1":
          self.mdi.cascadeSubWindows()
                    
       if q.text() == "text2":
          self.mdi.tileSubWindows()
		
def main():
    app = QApplication(sys.argv)
    ex = MainWindow()
    ex.show()
    sys.exit(app.exec_())
	
if __name__ == '__main__':
    main()
    