"""
Waltech Ladder Maker is distributed under the MIT License. 

Copyright (c) 2014 Karl Walter.  karl (at) waltech.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""
from PyQt4 import QtCore, QtGui
from PyQt4.QtGui import QApplication, QDialog
import re
##006##
#all the element dialogs
from coil_ui import Ui_CoilDialog
from cont_ui import Ui_ContDialog
from edge_ui import Ui_EdgeDialog
from timer_ui import Ui_TimerDialog
from counter_ui import Ui_CounterDialog
from compair_ui import Ui_CompairDialog
from USBHelp_ui import Ui_USBDialog
from IOHelp_ui import Ui_IODialog
from ardIOnote_ui import Ui_ardIOnoteDialog
from math_ui import Ui_MathDialog
#from move_ui import Ui_MoveDialog
from ADC_ui import Ui_ADCDialog
from PWM_ui import Ui_PWMDialog
from wrongVersion_ui import Ui_wrongVersionDialog


##007##
class CoilDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_CoilDialog()
        self.ui.setupUi(self)
        cellNum[0]
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
        #what is in dialog:
        #   comboBox:   IO list
        #   comboBox_2: name
        #   lineEdit:   comment
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeNamelistCoil(self.ui.comboBox_2)
        cellSearch(grid,cellNum,self.currentHW).makeIOlist(self.ui.comboBox,False)
        cellSearch(grid,cellNum,self.currentHW).fillComment(self.ui.lineEdit)
            

       
class ContDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_ContDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
        #connect signalls buttons, texts other stuff here
         #what is in dialog:
        #   comboBox:   IO list
        #   comboBox_2: name
        #   lineEdit:   comment
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeNamelistCont(self.ui.comboBox_2)
        cellSearch(grid,cellNum,self.currentHW).makeIOlist(self.ui.comboBox,True)
        cellSearch(grid,cellNum,self.currentHW).fillComment(self.ui.lineEdit)
           
class EdgeDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_EdgeDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
         #what is in dialog:
        #   lineEdit:   comment
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).fillComment(self.ui.lineEdit)
        
class TimerDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_TimerDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
        #connect signalls buttons, texts other stuff here
         #what is in dialog:
        #   spinBox:   setPoint
        #   comboBox_2: name
        #   lineEdit:   comment
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeNamelistCoil(self.ui.comboBox_2)
        cellSearch(grid,cellNum,self.currentHW).fillComment(self.ui.lineEdit)
        cellSearch(grid,cellNum,self.currentHW).fillSpinBox(self.ui.doubleSpinBox)
        
class CounterDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_CounterDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
         #what is in dialog:
        #   spinBox:   setPoint
        #   comboBox_2: name
        #   lineEdit:   comment
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeNamelistCoil(self.ui.comboBox_2)
        cellSearch(grid,cellNum,self.currentHW).fillComment(self.ui.lineEdit)
        cellSearch(grid,cellNum,self.currentHW).fillSpinBox(self.ui.spinBox)
        

class CompairDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, tool, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_CompairDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
        self.elType = tool
        
        if self.elType == "Equals": self.ui.label_8.setText('=')
        if self.elType == "Greater": self.ui.label_8.setText('>')
        if self.elType == "Lessthan": self.ui.label_8.setText('<')
        if self.elType == "GreaterOrEq": self.ui.label_8.setText('>=')
        if self.elType == "LessOrEq": self.ui.label_8.setText('<=')
        
         
         
         #what is in dialog:
        
        #   comboBox_A: first value
        #   comboBox_B: second value
        #   spinBox_A: first constane
        #   spinBox_B: second constant
        
        #preload comboboxes:
        #self,combobox,thingBeingFilled)
        cellSearch(grid,cellNum,self.currentHW).makeNamelistComp(self.ui.comboBox_A,"source_A", self.elType )
        cellSearch(grid,cellNum,self.currentHW).makeNamelistComp(self.ui.comboBox_B,"source_B", self.elType)
        if self.grid[self.cellNum[0]][self.cellNum[1]].const_A != None:
            self.ui.spinBox_A.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].const_A)
        if self.grid[self.cellNum[0]][self.cellNum[1]].const_B != None:
            self.ui.spinBox_B.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].const_B)   

class MathDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW,tool, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_MathDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
        self.elType = tool
         #what is in dialog:
        
        #   comboBox_A: first value
        #   comboBox_B: second value
        #   spinBox_A: first constane
        #   spinBox_B: second constant
        
        #preload comboboxes:

        cellSearch(grid,cellNum,self.currentHW).makeNamelistCoil(self.ui.comboBox_2)
        
        cellSearch(grid,cellNum,self.currentHW).makeNamelistComp(self.ui.comboBox_A,"source_A", self.elType )
        cellSearch(grid,cellNum,self.currentHW).makeNamelistComp(self.ui.comboBox_B,"source_B", self.elType)
        if self.grid[self.cellNum[0]][self.cellNum[1]].const_A != None:
            self.ui.spinBox_A.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].const_A)
        if self.grid[self.cellNum[0]][self.cellNum[1]].const_B != None:
            self.ui.spinBox_B.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].const_B)   
        
##needs to be used instead of combine with math:
class MoveDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_MoveDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
         #what is in dialog:
        
        #   comboBox_A: first value
        #   comboBox_B: second value
        #   spinBox_A: first constane
        #   spinBox_B: second constant
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeNamelistComp(self.ui.comboBox_A)
        cellSearch(grid,cellNum,self.currentHW).makeNamelistComp(self.ui.comboBox_B)

class PWMDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_PWMDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
         #what is in dialog:
        
        #   lineEdit: comment
        #   comboBox: output pin
        #   doubleSpinBox: Duty Cycle (setpoint)
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeIOlist(self.ui.comboBox,"PWM")
        if self.grid[self.cellNum[0]][self.cellNum[1]].setPoint != None:
            self.ui.doubleSpinBox.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].setPoint)

class ADCDialog(QtGui.QDialog):
    def __init__(self, grid, cellNum, currentHW, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_ADCDialog()
        self.ui.setupUi(self)
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
         #what is in dialog:
        #   lineEdit: comment
        #   comboBox: input pin
        #   comboBox_2: Name
        
        #preload comboboxes:
        cellSearch(grid,cellNum,self.currentHW).makeNamelistCont(self.ui.comboBox_2)
        cellSearch(grid,cellNum,self.currentHW).makeIOlist(self.ui.comboBox,"ADC")

class ArduinoUnoIOHelpDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_IODialog()
        self.ui.setupUi(self)
 
        with open ("ArdUnoIO.html", 'r') as myfile:
            helpHtml=myfile.read()
        self.ui.textBrowser.setHtml(helpHtml)
        
class ArduinoNanoIOHelpDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_IODialog()
        self.ui.setupUi(self)
        with open ("ArdNanoIO.html", 'r') as myfile:
            helpHtml=myfile.read()
        self.ui.textBrowser.setHtml(helpHtml)
        
class ArduinoMegaIOHelpDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_IODialog()
        self.ui.setupUi(self)
 
        with open ("ArdMegaIO.html", 'r') as myfile:
            helpHtml=myfile.read()
        self.ui.textBrowser.setHtml(helpHtml)
        

class AboutHelpDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_IODialog()
        self.ui.setupUi(self)
        self.ui.textBrowser.setWindowTitle('About')#doesn't work
        with open ("About.html", 'r') as myfile:
            helpHtml=myfile.read()
        self.ui.textBrowser.setHtml(helpHtml)
        

class ThreeParallelsDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        self.ui = Ui_IODialog()
        self.ui.setupUi(self)
        with open ("parallels.html", 'r') as myfile:
            helpHtml=myfile.read()
        self.ui.textBrowser.setHtml(helpHtml)

        
class USBHelpDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
        
         
        self.ui = Ui_USBDialog()
        self.ui.setupUi(self)
        with open ("usb.html", 'r') as myfile:
            helpHtml=myfile.read()
        self.ui.textBrowser.setHtml(helpHtml)
        
class ardIODialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
            
        self.ui = Ui_ardIOnoteDialog()
        self.ui.setupUi(self)
     
class wrongVersionDialog(QtGui.QDialog):
    def __init__(self, parent=None):
        QDialog.__init__(self)# Constructs a dialog with parent parent. self being ImageDailog
        # Set up the UI from Designer:
            
        self.ui = Ui_wrongVersionDialog()
        self.ui.setupUi(self)   


class cellSearch(): #Functions for pre-filling the boxes in the Popup dialogs
    def __init__(self,grid,cellNum,currentHW):#bring in all the things being sent down here
        self.grid = grid
        self.cellNum = cellNum
        self.currentHW = currentHW
        
    def makeSharedNameList(self,elType):# elType is a string like "Coil" 
    #scan the grid for names != None, put in comboBox
        shareNameList = []
        allNameList = []
        biggestName = 0
        #fill up a list of all names not of this type:
        for i in range(len(self.grid)):
            for j in range(len(self.grid[i])):
                if self.grid[i][j].variableName != None:
                    varName = self.grid[i][j].variableName
                    allNameList.append(varName)
                    if  elType not in self.grid[i][j].MTorElement:
                        shareNameList.append(varName)
                    
        #go through allNameList and find default name num:
        for i in range(len(allNameList)):
            if "Name_" == allNameList[i][:5]:
                try:#this will skip if the thing after Name_ is not a number
                    nameNum =int(str(allNameList[i][5:]))
                except: pass
                else:
                    if nameNum>biggestName: biggestName =nameNum
                    
        defaultName = "Name_"+str(biggestName+1)#increment by 1
        shareNameList.insert(0,defaultName)#add to beginning of list
        
        
        #check if already named (editing instead of new element)
        if self.grid[self.cellNum[0]][self.cellNum[1]].variableName != None:
            shareNameList.pop(0)
            shareNameList.insert(0,self.grid[self.cellNum[0]][self.cellNum[1]].variableName)#replace Name_ above with real name
  
        return shareNameList
        
    def makeSourceNameList(self,thisThing,elType):# thisThing: the name of the variable for the combobox
        # thisThing : "source_A", "const_A", "source_B", "const_B"
        if thisThing == "source_A": thingVar = self.grid[self.cellNum[0]][self.cellNum[1]].source_A
        if thisThing == "const_A": thingVar = self.grid[self.cellNum[0]][self.cellNum[1]].const_A
        if thisThing == "source_B": thingVar = self.grid[self.cellNum[0]][self.cellNum[1]].source_B
        if thisThing == "const_B": thingVar = self.grid[self.cellNum[0]][self.cellNum[1]].const_B
        print "$$$ thingVar: ",thingVar
        #scan the grid for names != None, put in comboBox
        shareNameList = []
        allNameList = []
        biggestName = 0
        #fill up a list of all names not of this type:
        for i in range(len(self.grid)):
            for j in range(len(self.grid[i])):
                if self.grid[i][j].variableName != None:
                    varName = self.grid[i][j].variableName
                    allNameList.append(varName)
                    if  elType not in self.grid[i][j].MTorElement:
                        shareNameList.append(varName)
        shareNameList.insert(0,"Constant")#default first thing
        if thingVar != None:#right clicked, editing
            #shareNameList.pop(0)
            print"$$$putting in last name"
            shareNameList.insert(0,thingVar)
        return shareNameList
        
    def makeSixteenNameList(self,elType):# thisThing: the name of the variable for the combobox
        shareNameList = []
        allNameList = []
        biggestName = 0
        #fill up a list of all names not of this type and not 8 bit:
        for i in range(len(self.grid)):
            for j in range(len(self.grid[i])):
                if self.grid[i][j].variableName != None:
                    varName = self.grid[i][j].variableName
                    allNameList.append(varName)
                    if  elType not in self.grid[i][j].MTorElement and \
                            "coil" not in self.grid[i][j].MTorElement and\
                            "coil" not in self.grid[i][j].MTorElement :    
                        shareNameList.append(varName)
        shareNameList.insert(0,"Constant")#default first thing
        if thingVar != None:#right clicked, editing
            #shareNameList.pop(0)
            print"$$$putting in last name"
            shareNameList.insert(0,thingVar)
        return shareNameList
    
    ##009##    
    #usage example: cellSearch(grid,cellNum).makeNamelist(self.ui.comboBox_2)
    #looks in the cells and CellNum and makes a list for the combobox passed to it     
    def makeNamelistCoil(self,combobox): 
        #scan the grid for names != None, put in comboBox
        shareNameList = self.makeSharedNameList("Coil")
        combobox.addItems(shareNameList)#put list in combobox
    
    def makeNamelistCont(self,combobox): 
        #scan the grid for names != None, put in comboBox
        shareNameList = self.makeSharedNameList("cont")
        combobox.addItems(shareNameList)#put list in combobox 
        
    def makeNamelistComp(self,combobox,thisThing,elType): #fills nams for comparison operators
        shareNameList = self.makeSourceNameList(thisThing,elType)
        combobox.addItems(shareNameList)#put list in combobox      
        
    def makeIOlist(self,combobox,inpt):
        #set the items in cmbobox:
        
        if self.currentHW == "Waltech":
            if inpt == True:
                list1=["Internal","in_1", "in_2", "in_3", "in_4", "in_5", "in_6", "in_7", "in_8", "in_9", "in_10", "in_11", "in_12"]
            else:
                list1=["Internal","out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7", "out_8","out_9", "out_10", "out_11", "out_12"]
        
        if self.currentHW == "ArduinoUno":
            if inpt == True:
                list1=["Internal","in_1", "in_2", "in_3", "in_4", "in_5"]
            elif inpt == "PWM":
                 list1=["pwm_1", "pwm_2"]
            elif inpt == "ADC":
                 list1=["adc_1", "adc_2", "adc_3", "adc_4",]
            else:
                list1=["Internal","out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7"]
                
        if self.currentHW == "ArduinoNano":
            if inpt == True:
                list1=["Internal","in_1", "in_2", "in_3", "in_4", "in_5"]
            elif inpt == "PWM":
                 list1=["pwm_1", "pwm_2"]
            elif inpt == "ADC":
                 list1=["adc_1", "adc_2", "adc_3", "adc_4",]
            else:
                list1=["Internal","out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7"]        
                
        if self.currentHW == "ArduinoMega":
            if inpt == True:
                list1=["Internal","in_1", "in_2", "in_3", "in_4", "in_5", "in_6", "in_7", "in_8", "in_9", "in_10", "in_11", "in_12", "in_13", "in_14", "in_15", "in_16", "in_17", "in_18", "in_19", "in_20", "in_21", "in_22"]
            elif inpt == "PWM":
                 list1=["pwm_1", "pwm_2", "pwm_3", "pwm_4", "pwm_5", "pwm_6", "pwm_7", "pwm_8"]
            elif inpt == "ADC":
                 list1=["adc_1", "adc_2", "adc_3", "adc_4", "adc_5", "adc_6", "adc_7", "adc_8"]
            else:
                list1=["Internal","out_1", "out_2", "out_3", "out_4", "out_5", "out_6", "out_7", "out_8","out_9", "out_10", "out_11", "out_12", "out_13", "out_14", "out_15", "out_16", "out_17", "out_18", "out_19", "out_20", "out_21", "out_22"]
        toPop=[]
        if inpt != "PWM":
            #scan grid and remove any matching IO's
            for i in range(len(self.grid)):
                for j in range(len(self.grid[i])):
                    if self.grid[i][j].ioAssign != None and self.grid[i][j].ioAssign != "Internal":
                        #scan list1 for a match, pop it, and go back and look for another in grid
                        for k in range(len(list1)):
                            if list1[k]== self.grid[i][j].ioAssign:
                                list1.pop(k)
                                break
        #add Internal if it is not in list:
        ##007.5##
        """
        if len(list1) >1 and list1[1] != "Internal" and \
                self.grid[self.cellNum[0]][self.cellNum[1]].MTorElement != "PWM" and\
                self.grid[self.cellNum[0]][self.cellNum[1]].MTorElement != "ADC":
            list1.insert(0,"Internal")
        """
        if len(list1) >1 and list1[1] != "Internal":
            list1.insert(0,"Internal")
        #check if already assigned (editing instead of new element)
        if self.grid[self.cellNum[0]][self.cellNum[1]].ioAssign != None:
            #list1.pop(0)
            list1.insert(0,self.grid[self.cellNum[0]][self.cellNum[1]].ioAssign)
            
        #make current I/O the default item 0
        #list1.insert(0,self.grid[self.cellNum[0]][self.cellNum[1]].ioAssign)
        combobox.addItems(list1)
        
    def fillComment(self,lineEdit):#puts comment back
        if self.grid[self.cellNum[0]][self.cellNum[1]].comment != None:
            lineEdit.setText(self.grid[self.cellNum[0]][self.cellNum[1]].comment)  
    
    def fillSpinBox(self,spinBox):
        if self.grid[self.cellNum[0]][self.cellNum[1]].setPoint != None:
            spinBox.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].setPoint)
            
    def fillSpinBoxTimer(self,spinBox):
        if self.grid[self.cellNum[0]][self.cellNum[1]].setPoint != None:
            spinBox.setValue(self.grid[self.cellNum[0]][self.cellNum[1]].setPoint/100)       
    
 
