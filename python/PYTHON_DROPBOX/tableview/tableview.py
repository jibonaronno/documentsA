''' pqt_tableview3.py
explore PyQT's QTableView Model
using QAbstractTableModel to present tabular data
allow table sorting by clicking on the header title

used the Anaconda package (comes with PyQt4) on OS X
(dns)
'''

import operator  # used for sorting
from PyQt4.QtCore import *
from PyQt4.QtGui import *

class MyWindow(QWidget):
    def __init__(self, dataList, header, *args):
        QWidget.__init__(self, *args)
        # setGeometry(x_pos, y_pos, width, height)
        self.setGeometry(70, 150, 420, 250)
        self.setWindowTitle("Click on the header to sort table")

        table_model = MyTableModel(self, dataList, header)
        table_view = QTableView()
        # bind cell click to a method reference
        table_view.clicked.connect(self.showSelection)

        table_view.setModel(table_model)
        # enable sorting
        table_view.setSortingEnabled(True)

        layout = QVBoxLayout(self)
        layout.addWidget(table_view)
        self.setLayout(layout)

    def showSelection(self, item):
        cellContent = item.data()
        print(cellContent)  # test
        sf = "You clicked on {}".format(cellContent)
        # display in title bar for convenience
        self.setWindowTitle(sf)


class MyTableModel(QAbstractTableModel):
    """
    keep the method names
    they are an integral part of the model
    """
    def __init__(self, parent, mylist, header, *args):
        QAbstractTableModel.__init__(self, parent, *args)
        self.mylist = mylist
        self.header = header

    def rowCount(self, parent):
        return len(self.mylist)

    def columnCount(self, parent):
        return len(self.mylist[0])

    def data(self, index, role):
        if not index.isValid():
            return None
        elif role != Qt.DisplayRole:
            return None
        return self.mylist[index.row()][index.column()]

    def headerData(self, col, orientation, role):
        if orientation == Qt.Horizontal and role == Qt.DisplayRole:
            return self.header[col]
        return None

    def sort(self, col, order):
        """sort table by given column number col"""
        self.emit(SIGNAL("layoutAboutToBeChanged()"))
        self.mylist = sorted(self.mylist,
            key=operator.itemgetter(col))
        if order == Qt.DescendingOrder:
            self.mylist.reverse()
        self.emit(SIGNAL("layoutChanged()"))


# you could process a CSV file to create this data
header = ['First Name', 'Last Name', 'Age', 'Weight']
# a list of (fname, lname, age, weight) tuples
dataList = [
('Ben', 'Dover', 36, 127),
('Foster', 'Krampf', 27, 234),
('Barry', 'Chaurus', 19, 315),
('Sede', 'Anowski', 59, 147),
('Carolus', 'Gabel', 94, 102),
('Michel', 'Zittus', 21, 175),
('Annie', 'Waters', 31, 114)
]

app = QApplication([])
win = MyWindow(dataList, header)
win.show()
app.exec_()
