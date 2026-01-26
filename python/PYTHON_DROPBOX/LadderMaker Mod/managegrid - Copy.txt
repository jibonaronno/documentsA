"""
Waltech Ladder Maker is distributed under the MIT License. 

Copyright (c) 2014 Karl Walter.  karl (at) waltech.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""



from PyQt4 import QtCore, QtGui
##010##
class cellStruct():
    def __init__(self, midPointX, midPointY, MTorElement, rungOrOR,\
                variableName, ioAssign, comment, setPoint,\
                 branch, node, brchST, brchE, nodeST, nodeE,\
                 source_A, source_B, const_A, const_B, functType):
        self. midPointX = midPointX
        self. midPointY = midPointY
        self. MTorElement = MTorElement 
        self. rungOrOR = rungOrOR
        self. variableName = variableName 
        self. ioAssign = ioAssign
        self. comment = comment
        self. setPoint = setPoint
        self. branch = branch
        self. node = node
        self. brchST = brchST
        self. brchE = brchE
        self. nodeST = nodeST
        self. nodeE = nodeE
        self. source_A = source_A  
        self. source_B = source_B 
        self. const_A = const_A
        self. const_B = const_B
        self. functType = functType
        self.baseRungOrOR = "Rung"
        self.baseBlockIndex = -1
        self.blockIndex = -1
        
        
        
class ManageGrid():
    def __init__(self,grid,scene,Tools,items):#bring in all the things being sent down here
        self.grid = grid
        self.scene = scene
        self.Tools = Tools
        self.items = items
        self.brnch_node_item_text = QtGui.QGraphicsTextItem()
        self.cell_mtorele_text = QtGui.QGraphicsTextItem()
        self.blockindex_text = QtGui.QGraphicsTextItem()
        self.branchST_text = QtGui.QGraphicsTextItem()
        self.branchE_text = QtGui.QGraphicsTextItem()
        self.nodeE_text = QtGui.QGraphicsTextItem()
        self.nodeST_text = QtGui.QGraphicsTextItem()

        self.debugShowMTorEle = False
        self.debugShowrungOrOR = True
        self.debugShowBranchNode = True
        self.debugShowBlockIndex = False
        self.debugShowBranchST = True
        self.debugShowBranchE = True
        self.debugShowNodeE = True
        self.debugShowNodeST = True
#cell infos:
#midPointX, midPointY, MTorElement, rungOrOR, variableName, ioAssign, comment):        
    def totalRedraw(self):
        cellNum = [0, 0]
        height = len(self.grid)
        width = len(self.grid[0]) #just check the legnth of first row
        self.scene.clear()#blank everything in scene
        
        #self.items[0] = QtGui.QGraphicsTextItem() #put back itemOne for position highlight
        #self.items[1] = QtGui.QGraphicsRectItem()
        rowToDraw = 0
        while rowToDraw != height:#draw all the lines for the rungs:
            for j in range(0, width):
                #<<<< draw rung cell lines >>>>>
                if self.grid[rowToDraw][j].rungOrOR == "Rung":  
                    self.scene.addLine(j*60, rowToDraw*60, (j+1)*60, rowToDraw*60) #(x1, y1, x2, y2)
                    
                #<<<< OR lines:>>>>  
                if self.grid[rowToDraw][j].rungOrOR == "OR":
                    
                    # draw horizontal balnkOr line:
                    if self.grid[rowToDraw][j].MTorElement != "MT":
                        self.scene.addLine(j*60, rowToDraw*60, (j+1)*60, rowToDraw*60)
                        
                # >>>>OR uprights:,<<<<<<
                    # left is MT:
                    # IN RungOrOR == OR When Present Cell is not "MT" #AND When Previous Cell is "MT"
                    if j-1>-1\
                            and self.grid[rowToDraw][j].MTorElement != "MT"\
                            and self.grid[rowToDraw][j-1].MTorElement == "MT":
                        # Draw Vertical Line At Left When Left Cell is "MT"
                        self.scene.addLine((j*60), (rowToDraw*60)-60, (j*60), (rowToDraw*60))

                    # Far left spot:(always gets upright
                    if self.grid[rowToDraw][j].MTorElement != "MT" and j == 0:
                        # Draw Vertical Line At Left When Present Cell is At Start Position
                        self.scene.addLine((j*60), (rowToDraw*60)-60, (j*60), (rowToDraw*60))

                    # right is MT:
                    if j+1<width\
                            and self.grid[rowToDraw][j].MTorElement != "MT"\
                            and self.grid[rowToDraw][j+1].MTorElement == "MT":
                        # Draw Vertical Line At Right When Right Cell is "MT"
                        self.scene.addLine(((j+1)*60), (rowToDraw*60)-60, ((j+1)*60), (rowToDraw*60)) 

                    # NESTED OR CONNECTION:
                    # look down and see if gonna need an upright to connect to below:
                    # only check on MT OR spots:
                    if self.grid[rowToDraw][j].MTorElement != "blankOR"\
                                    and self.grid[rowToDraw][j].rungOrOR == "OR":
                    #if self.grid[rowToDraw][j].rungOrOR == "OR":
                        foundBOr = 0                   
                        for k in range (1,height-rowToDraw):
                            if self.grid[rowToDraw+k][j].rungOrOR == "Rung":
                                break
                            if self.grid[rowToDraw+k][j].MTorElement != "MT":
                                foundBOr = k
                                break
                        # check if there is a blank OR to the right of blankOR found above:
                        if j+1<width and foundBOr>0\
                                    and self.grid[rowToDraw+foundBOr][j+1].MTorElement == "MT"\
                                    and self.grid[rowToDraw][j+1].MTorElement == "MT":
                            self.scene.addLine(((j+1)*60), (rowToDraw*60)-60, ((j+1)*60), (rowToDraw*60))
                            
                            
                        #check if there is a blank OR to the left of blankOR found above:
                        if j-1>=0 and foundBOr>0\
                                    and self.grid[rowToDraw+foundBOr][j-1].MTorElement == "MT"\
                                    and self.grid[rowToDraw][j-1].MTorElement == "MT":
                            self.scene.addLine(((j)*60), (rowToDraw*60)-60, ((j)*60), (rowToDraw*60))
                            
                        # special case: far left: check if there is a blank OR to the left of blankOR found above:
                        if j-1==-1 and foundBOr>0:
                            self.scene.addLine(((j)*60), (rowToDraw*60)-60, ((j)*60), (rowToDraw*60))
                            
                            
            #<<<< draw ends >>>>>
            if self.grid[rowToDraw][0].rungOrOR == "Rung":
                self.scene.addLine(-6, rowToDraw*60, 0, rowToDraw*60)#left filler        
            #draw the ends:   
            self.scene.addLine(-6, (rowToDraw*60)-30, -6, (rowToDraw*60)+30)#left
            self.scene.addLine((width*60) , (rowToDraw*60)-30, (width*60) , (rowToDraw*60)+30)#right
            rowToDraw = rowToDraw +1# go on to next one (seel while above)
        #ears for to cause resizing to be a bit wider
        self.scene.addLine(-9, -30, -6, -30)
        self.scene.addLine((width*60), -30, (width*60)+3, -30)

        #<<<<put  all elemts back >>>>>
        for i in range(height):
            for j in range(width):
                cellNum[0] = i
                cellNum[1] = j
                if self.grid[i][j].MTorElement != "MT" and self.grid[i][j].MTorElement !="blankOR":
                    #find which tool
                    numTools = len(self.Tools.toolList)
                    toolToPlace = 0#index of tool
                    for k in range(numTools):
                        if self.Tools.toolList[k].toolName == self.grid[i][j].MTorElement:
                            toolToPlace = k
                    cellNum = [i,j,None,None]
                    self.placeIcon(cellNum, toolToPlace)
                    #put in name and comment
                    self.placeText(cellNum)

                self.placeTextExtra(cellNum)
    

     
    def Delete (self,cellNum):
        #MTorElement, rungOrOR, variableName, ioAssign, comment
        height = len(self.grid)
        width = len(self.grid[0])
        print "DELETING"
        delRow = True #becomes false if not all MT
        for j in range(width):
            if  self.grid[cellNum[0]][j].MTorElement != "MT":
                delRow = False #found an element
        if cellNum[0] != height -1 and self.grid[cellNum[0]+1][cellNum[1]].rungOrOR != "Rung":
            delRow = False # has an OR below. 
        if delRow == False: # delete element, not row.
            if self.grid[cellNum[0]][cellNum[1]].rungOrOR == "Rung": 
                self.grid[cellNum[0]][cellNum[1]].MTorElement = "MT"
            if self.grid[cellNum[0]][cellNum[1]].rungOrOR == "OR":
                self.grid[cellNum[0]][cellNum[1]].MTorElement = "blankOR"   
            ##011##
            self.grid[cellNum[0]][cellNum[1]].variableName = None
            self.grid[cellNum[0]][cellNum[1]].ioAssign = None
            self.grid[cellNum[0]][cellNum[1]].comment = None
            self.grid[cellNum[0]][cellNum[1]].setPoint = None
            self.grid[cellNum[0]][cellNum[1]].source_A = None
            self.grid[cellNum[0]][cellNum[1]].const_A = None
            self.grid[cellNum[0]][cellNum[1]].source_B = None
            self.grid[cellNum[0]][cellNum[1]].const_B = None
            self.grid[cellNum[0]][cellNum[1]].functType = None
        else:
            self.removeRung(cellNum[0])  
        self.totalRedraw()
             
    def insertRung(self,row):
        width = len(self.grid[0]) #just check the legnth of first row
        if width<10: width = 10
        Y=row*60#get Y of rung to be displaced
        self.grid.insert(row,[])#insert a rung
        for i in range(width):#fill with mt cells : for in range 0 to width
            self.grid[row].append(cellStruct(i*60, Y, "MT","Rung", None, None, None, None, False, False, False, False, False, False,None,None,None,None,None))
        #shift Y values down on grid below
        height = len(self.grid)
        for i in range(row,height):
            for j in range(width):
                #print i,j
                self.grid[i][j].midPointY = self.grid[i][j].midPointY + 60
        self.changeRectangle()
        self.totalRedraw()
        
    def insertBlankOR(self,cellNum):
        row = cellNum[0]
        height = len(self.grid)
        width = len(self.grid[0]) #just check the legnth of first row
        if width<10: width = 10
        Y=row*60#get Y of rung to be displaced
        #if there is already an OR row here, don't make another
        isOrBranch = False
        if row<height:
            for j in range(width): #check cells on row for "OR"
                if self.grid[row][j].rungOrOR == "OR":
                    isOrBranch = True
                    break
        if isOrBranch == False: 
            self.grid.insert(row,[])#insert a rung
            for i in range(width):#fill with mt cells : for in range 0 to width
                self.grid[row].append(cellStruct(i*60, Y, "MT","OR", None, None, None,None, False, False, False, False, False, False, None, None, None, None,None))
            #shift Y values down on grid below
            height = len(self.grid)
            for i in range(row,height):
                for j in range(width):
                    self.grid[i][j].midPointY = self.grid[i][j].midPointY + 60

        self.changeRectangle()

    def resetRung(self, row):
        width = len(self.grid[0])
        for j in range(width):
            self.grid[row][j].MTorElement = "MT"
            self.grid[row][j].rungOrOR = "Rung"
            self.grid[row][j].variableName = None
            self.grid[row][j].ioAssign = None
            self.grid[row][j].comment = None
            self.grid[row][j].setPoint = None
            self.grid[row][j].branch = False
            self.grid[row][j].node = False
            self.grid[row][j].brchST = False
            self.grid[row][j].brchE = False
            self.grid[row][j].nodeST = False
            self.grid[row][j].nodeE = False
            self.grid[row][j].source_A = None
            self.grid[row][j].source_B = None
            self.grid[row][j].const_A = None
            self.grid[row][j].const_B = None
            self.grid[row][j].functType = None
        self.changeRectangle()
        
    def removeRung(self,row):
        self.grid.pop(row)
        height = len(self.grid)
        width = len(self.grid[0])
        for i in range(row,height):
            for j in range(width):
                self.grid[i][j].midPointY = self.grid[i][j].midPointY- 60
        """
        #report array:
        height = len(self.grid)
        width = len(self.grid[0])
        for i in range(height):
            print("row %d:" %i)
            for j in range(width):
                print("%d:%d,%d " %(j,self.grid[i][j].midPointX,self.grid[i][j].midPointY))
        """ 
        self.changeRectangle()     
        #self.totalRedraw()
        
    def Widen(self,cellNum):
        width = len(self.grid[0])
        height = len(self.grid)
        thisRow = cellNum[0]
        thisSpot = cellNum[1]
        rungOrOR = self.grid[thisRow][0].rungOrOR#check type in this row
        X = self.grid[thisRow][cellNum[1]].midPointX
        Y = self.grid[thisRow][cellNum[1]].midPointY
        widenSpot = [] #will contain the position to widen  
        for i in range(height): #go through annd find all associated rows.
            connectedToThisRung = True #assume connected to start   
            #if i is a rung, and thisRow is a rung, then not connected, except when i is thisRow
            if self.grid[i][0].rungOrOR == "Rung" and rungOrOR == "Rung" and thisRow!=i:connectedToThisRung = False
            #if i is a Rung and thisRow is below: look down and see if thisRow is below, w/o a rung between
            if self.grid[i][0].rungOrOR == "Rung" and thisRow>i:
                for k in range(i+1,thisRow):#see if there is  rung between  (range includes thisRow?)
                    if self.grid[k][0].rungOrOR != "OR": connectedToThisRung = False
            #if i is a Rung, and thisRow is above, then not connected
            if self.grid[i][0].rungOrOR == "Rung" and i>thisRow: connectedToThisRung = False 
            #if i is a OR and thisRow is above: look up and see if thisRow is above w/out a rung between
            if self.grid[i][0].rungOrOR == "OR" and i<thisRow:
                for k in range(i,thisRow+1,-1):#see if there is  rung between 
                    if self.grid[k][0].rungOrOR != "OR": connectedToThisRung = False
            #if i is a OR and thisRow is below and is an OR : look down and see if thisRow is below w/out a rung between
            if self.grid[i][0].rungOrOR == "OR" and self.grid[thisRow][0].rungOrOR == "OR" and thisRow>i:
                for k in range(i,thisRow):#see if there is  rung between  (range includes thisRow? no)
                    if self.grid[k][0].rungOrOR != "OR": connectedToThisRung = False
            #if i is a OR and thisRow is below and is a Rung: then not connected
            if self.grid[i][0].rungOrOR == "OR" and self.grid[thisRow][0].rungOrOR == "Rung" and thisRow>i:
                connectedToThisRung = False                  
            #if i is a OR, if thisrow is not a Rung look down and see if thisRow is below w/out a rung betwee
            if self.grid[i][0].rungOrOR == "OR" and rungOrOR == "OR" and thisRow>i:
                for k in range(i,thisRow):#see if there is  rung between  (range includes thisRow?)
                    if self.grid[k][0].rungOrOR != "OR": connectedToThisRung = False
                    
            if connectedToThisRung == True: # widenSpot holds the position to be inserted
                widenSpot.append(thisSpot)
            else: 
                widenSpot.append(width-1) 
        for n in range(height): #go through again and apply above.  inserts BEHIND
            X = self.grid[n][widenSpot[n]].midPointX
            Y = self.grid[n][widenSpot[n]].midPointY
            if self.grid[n][widenSpot[n]].MTorElement != "MT" and self.grid[n][widenSpot[n]].rungOrOR == "OR": 
                A = "blankOR"
            #if self.grid[n][widenSpot[n]].MTorElement == "blankOR": A = "blankOR"
            else: A = "MT"
            B= self.grid[n][widenSpot[n]].rungOrOR
            self.grid[n].insert(widenSpot[n],cellStruct(X, Y, A, B, None, None, None,None, False, False, False, False, False, False, None, None, None, None,None))
            for p in range(widenSpot[n]+1,width+1):
                self.grid[n][p].midPointX = self.grid[n][p].midPointX + 60#add 60 to widenSpot +1 to width+1
        
        self.changeRectangle()
        

    def resetBlankOR(self):
        delORrow = True
        rowToDel = None
        height = len(self.grid)
        width = len(self.grid[0])
        for i in range(height):
            if self.grid[i][0].rungOrOR=="OR": #is an OR row
                delORrow = True
                for j in range(width):
                    if self.grid[i][j].MTorElement != "MT":
                        delORrow = False # found an element
                if delORrow == True:
                    rowToDel = i # no elements found on OR row
        if rowToDel != None: # checked all, and found an OR row with all MT
            self.resetRung(rowToDel) # delete row

    def removeBlankOR(self):
        delORrow = True
        rowToDel = None
        height = len(self.grid)
        width = len(self.grid[0])
        for i in range(height):
            if self.grid[i][0].rungOrOR=="OR": #is an OR row
                for j in range(width):
                    if  self.grid[i][j].MTorElement != "MT":
                        delORrow = False #found an element
                if delORrow == True: rowToDel = i #no elements found on OR row
        if rowToDel != None:#checked all, and found an OR row with all MT
            self.removeRung(rowToDel)#delete row

    def addColToOthers(self,cellNum,width):
        thisrung = cellNum[0]
        for i in range(len(self.grid)):#add on to each of other rungs  at  right
            rungOrOR = self.grid[i][0].rungOrOR#check type in this row
            if i != thisrung:#dont apply to row with widen spot
                Y = self.grid[i][0].midPointY
                self.grid[i].insert(width-1,cellStruct((width-1)*60, Y, "MT",rungOrOR, None, None, None, False, False, False, False, False, False, None, None, None, None,None))#add one cell at width to others
                self.grid[i][width].midPointX = self.grid[i][width].midPointX + 60 #add 60 to width+1 of others
    
    def Shrink(self,cellNum):
        # see if greater than 10 wide
        width = len(self.grid[0])
        height = len(self.grid)
        extraSpots = True
        spareSpot = []
        for i in range(height):#fill sparespots with None to start with
            spareSpot.append(None)
        #check all rows for spare spots:
        for i in range(height):
            #check each spot and see if it is shrinkabe:
            for j in range(width-2,-1,-1):
                testCellNum = i,j
                shrinkable = self.checkShrinkable(testCellNum, height, width)
                if shrinkable == True:
                    spareSpot[i] = j
                    #if i is a Rung and not the last one and OR is below: apply sparespot to OR Rows 
                    if (self.grid[i][j].rungOrOR == "Rung"\
                            and i+1 != height \
                            and self.grid[i+1][0].rungOrOR == "OR"):
                        print "apply sparespot to or rows"
                        for k in range (i+1, height):
                            if self.grid[k][0].rungOrOR == "Rung":# hit rung below
                                break
                            spareSpot[k] = j #apply the spare spot to rows below
                    break
        #check sparespots:
        for i in range(height):
            if spareSpot[i] == None: extraSpots = False
        print "allcheck:", spareSpot
            
        # now check the specific spot clicked:
        if extraSpots == True :# don't check if no other spots
            shrinkable = self.checkShrinkable(cellNum, height, width)
            i = cellNum[0]
            j = cellNum[1]
            if shrinkable == True:
                spareSpot[i] = j
                #if i is a Rung and not the last one and OR is below: apply sparespot to OR Rows 
                if (self.grid[i][j].rungOrOR == "Rung"\
                        and i+1 != height \
                        and self.grid[i+1][0].rungOrOR == "OR"):
                    print "apply sparespot to or rows"
                    for k in range (i+1, height):
                        if self.grid[k][0].rungOrOR == "Rung":# hit rung below
                            break
                        spareSpot[k] = j #apply the spare spot to rows below 
            else:
                spareSpot[i] = None
        print "this check:",spareSpot
        #check sparespots:
        for i in range(height):
            if spareSpot[i] == None: extraSpots = False
        print extraSpots
        if extraSpots == True:
             for i in range(height):
                    self.grid[i].pop(spareSpot[i])#delete cell
                    for j in range (spareSpot[i],width-1):
                        self.grid[i][j].midPointX = self.grid[i][j].midPointX - 60 #sub 60 from spots to right
        
        self.changeRectangle()
 
        
    def checkShrinkable(self,cellNum, height, width):
        i = cellNum[0]
        j = cellNum[1]
        spotIsSpare = False
        if j == width-1: return spotIsSpare
        if width <= 10:  return spotIsSpare       
        #if i is a Rung and has an MT and is the last one:
        if self.grid[i][j].rungOrOR == "Rung"\
                and self.grid[i][j].MTorElement == "MT" \
                and i+1 == height : 
            spotIsSpare = True
                    
        #if i is a Rung and has an MT and is not the last one and there is a rung below:
        if self.grid[i][j].rungOrOR == "Rung"\
                and self.grid[i][j].MTorElement == "MT" \
                and i+1 != height\
                and  self.grid[i+1][0].rungOrOR == "Rung":  
            spotIsSpare = True
                
        #if i is a Rung and not the last one and OR is below: look down 
        if (self.grid[i][j].rungOrOR == "Rung"\
                and self.grid[i][j].MTorElement == "MT" \
                and i+1 != height \
                and self.grid[i+1][0].rungOrOR == "OR"):
                            
            #print "testing spot", i,j
            #look down and see if there is an MT OR
            for k in range (i+1, height):
                if self.grid[k][0].rungOrOR == "Rung":# hit rung below
                    print k,j, "hit rung"
                    break
                #check if there is an MT or in this spot, and if there is an MT beside it
                elif self.grid[k][j].MTorElement == "MT":
                    if j==0:#on left, can shrink
                        print k,j, "on left, shrinkable"
                        spotIsSpare = True
                    elif self.grid[k][j+1].MTorElement == "MT" or self.grid[k][j-1].MTorElement == "MT":
                        print k,j, "an MT beside"
                        spotIsSpare = True
        return spotIsSpare
    
    def reportCellInfo(self):
        self.findBranchesAndNodes()
        height = len(self.grid)
        width = len(self.grid[0]) #just check the legnth of first row
        for i in range(height):
            for j in range(width):
                a = self.grid[i][j].MTorElement
                b = self.grid[i][j].rungOrOR
                
                txt = self.scene.addText(("%s\n%s" %(a,b)),QtGui.QFont("Arial",8))
                txt.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-88)
                txt.setDefaultTextColor (QtGui.QColor("lightgrey"))    
                if self.grid[i][j].branch ==True:
                    c = "branch  " +str(i)+","+str(j)
                    txt = self.scene.addText(("%s" %(c)),QtGui.QFont("Arial",6))
                    txt.setPos(self.grid[i][j].midPointX-13,self.grid[i][j].midPointY-87)
                    txt.rotate(270)
                    
                if self.grid[i][j].node ==True:
                    c = "node"
                    txt = self.scene.addText(("%s" %(c)),QtGui.QFont("Arial",6))
                    txt.setPos(self.grid[i][j].midPointX+47,self.grid[i][j].midPointY-67)
                    txt.setDefaultTextColor (QtGui.QColor("darkred"))
                    txt.rotate(270)
    
    def reportCellStartsEnds(self):
        height = len(self.grid)
        width = len(self.grid[0]) #just check the legnth of first row
        for i in range(height):
            for j in range(width):
                
                if self.grid[i][j].brchST ==True:
                    c = "B st " +str(i)+str(j)
                    txt = self.scene.addText(("%s" %(c)),QtGui.QFont("Arial",7))
                    txt.setPos(self.grid[i][j].midPointX-5,self.grid[i][j].midPointY-67)
                    txt.setDefaultTextColor (QtGui.QColor("darkred"))
        
                    txt.rotate(-85)

                    
                if self.grid[i][j].nodeST ==True:
                    c = "N st "+str(i)+str(j) 
                    txt = self.scene.addText(("%s" %(c)),QtGui.QFont("Arial",7))
                    txt.setPos(self.grid[i][j].midPointX+55,self.grid[i][j].midPointY-67)
                    txt.setDefaultTextColor (QtGui.QColor("darkgreen"))
                    txt.rotate(-35)
                   
                if self.grid[i][j].nodeE ==True:
                    c = "N E "+str(i)+str(j)
                    txt = self.scene.addText(("%s" %(c)),QtGui.QFont("Arial",7))
                    txt.setPos(self.grid[i][j].midPointX+55,self.grid[i][j].midPointY-67)
                    txt.setDefaultTextColor (QtGui.QColor("darkblue"))
                    txt.rotate(-65)

                
    def findBranchesAndNodes(self): ###NOTE: there are two of these: one here and one in LadderToC               
        height = len(self.grid)
        width = len(self.grid[0])
        for i in range(height): #clear all the node and branch tags
            for j in range(width):
                self.grid[i][j].branch = False
                self.grid[i][j].node = False
       #BRANCHES
        for i in range(height):
            ###print 'grid[{0}][{1}].rungOrOR = {2}'.format(i, j, self.grid[i][j].rungOrOR)
            #check of it is an OR:
            if self.grid[i][j].rungOrOR == "OR":
                for j in range(width):
                    ###print ' '
                    for k in range(i,height):#looks down for rung or
                        ###print 'k=', k
                        if self.grid[k][j].rungOrOR != "OR":
                            ###print '-grid[{0}][{1}].rungOrOR != OR'.format(k,j)
                            break #hit rung w/o findng
                        """ THINGS CAN BE A BRANCH AND A NODE
                        #check if node
                        if j!=0\
                                and self.grid[k][j-1].MTorElement != "MT" \
                                and self.grid[k][j].MTorElement == "MT":
                            break#is a node (same as below)
                        """
                        if self.grid[k][j].MTorElement != "MT" and (j == 0 or self.grid[k][j-1].MTorElement == "MT"):
                            self.grid[i][j].branch = True
                            ###print '++[k][j-1] self.grid[{0}][{1}].MTorElement={2}'.format(k, j-1, self.grid[k][j-1].MTorElement)
                            ###print '++self.grid[{0}][{1}].MTorElement={2}'.format(k, j, self.grid[k][j].MTorElement)
                            ###print '--grid[{0}][{1}].branch = True '.format(i, j)
                            break
                    #another situation:
                    if j != 0 and self.grid[i][j].MTorElement != "MT" and self.grid[i][j-1].MTorElement != "MT":
                        self.grid[i][j].branch = False
                        ###print '---grid[{0}][{1}].branch = False'.format(i, j)
 
        #NODES:
        for i in range(height):
            #check of it is an OR:
            if self.grid[i][j].rungOrOR == "OR": 
                for j in range(width):
                    for k in range(i,height):
                        if self.grid[k][j].rungOrOR != "OR":
                            ###print '----grid[{0}][{1}] hit RUNG w/o find'.format(k, j)
                            break #hit rung w/o findng 
                        if self.grid[k][j].MTorElement != "MT" \
                                and j!= width-1\
                                and self.grid[k][j+1].MTorElement != "MT":
                            ###print '-----grid[{0}][{1}] Found Blank OR'.format(k, j+1)
                            break# found blankOR s
                        
                        if self.grid[k][j].MTorElement != "MT" \
                                and j!= width-1\
                                and self.grid[k][j+1].MTorElement == "MT":
                            ###print '------grid[{0}][{1}].node = True'.format(i, j)
                            self.grid[i][j].node = True
                            break
                    if j < width-1\
                            and self.grid[i][j].MTorElement != "MT"\
                            and  self.grid[i][j+1].MTorElement != "MT":
                        ####print '--------grid[{0}][{1}].node = False'.format(i, j)
                        self.grid[i][j].node = False
                        
                        
    def markStartsAndEnds(self):
        self.findBranchesAndNodes()
                        
    def findStartsAndEnds(self):
        
        self.findBranchesAndNodes()
        height = len(self.grid)
        width = len(self.grid[0])
        for i in range(height): #clear all the node and branch tags
            for j in range(width):
                self.grid[i][j].brchST = False
                self.grid[i][j].brchE = False
                self.grid[i][j].nodeST = False
                self.grid[i][j].nodeE = False
                
        #BRANCH Starts :                
        for i in range(height-1):
            for j in range(width):
                #print "branch ",i,j,self.grid[i][j].branch," branch i+1 ", self.grid[i+1][j].branch
                #check if branchstart at rung:
                if self.grid[i][j].branch == False and self.grid[i+1][j].branch == True:
                   self.grid[i][j].brchST = True
                
                #check if branchstart at branch w/outpt
                if self.grid[i][j].branch == True and self.grid[i+1][j].branch == True \
                        and self.grid[i][width-1].MTorElement != "blankOR"\
                        and self.grid[i][width-1].MTorElement != "MT":
                   self.grid[i][j].brchST = True
                #check for situation where branch is shifted down:
                #fix this up? not needed?
                """
                if self.grid[i][j].branch == False and self.grid[i+1][j].MTorElement == "blankOR"\
                        and self.grid[i][width-1].MTorElement != "blankOR"\
                        and self.grid[i][width-1].MTorElement != "MT":
                   self.grid[i][j].brchST = True
                """
        #NODE Starts:
        for i in range(height-1):
            for j in range(width-1):
                if self.grid[i+1][j].node == True:
                    self.grid[i][j].nodeST = True
                if  self.grid[i][j].MTorElement =="MT" and self.grid[i][j].rungOrOR =="OR":
                    self.grid[i][j].nodeST = False  
        #NODE Ends:
        for i in range(height-1):
            for j in range(width-1):
                if self.grid[i][j].node == True and self.grid[i+1][j].node == False:    
                    self.grid[i][j].nodeE = True
        

    def reAssignBlockIndex(self, cellNum):
        blockIndex = -1
        width = len(self.grid[0]) #cell count in each row
        if self.grid[cellNum[0]][0].rungOrOR == "OR":

            for i in range(width):
                if i==0 and self.grid[cellNum[0]][i].MTorElement != "MT":
                    blockIndex = blockIndex+1
                    self.grid[cellNum[0]][i].blockIndex = blockIndex
                elif self.grid[cellNum[0]][i].MTorElement != "MT"\
                        and self.grid[cellNum[0]][i-1].MTorElement == "MT":
                    blockIndex = blockIndex + 1
                    self.grid[cellNum[0]][i].blockIndex = blockIndex
                elif self.grid[cellNum[0]][i].MTorElement != "MT"\
                        and self.grid[cellNum[0]][i-1].MTorElement != "MT":
                    self.grid[cellNum[0]][i].blockIndex = self.grid[cellNum[0]][i-1].blockIndex
                elif self.grid[cellNum[0]][i].MTorElement == "MT":
                    self.grid[cellNum[0]][i].blockIndex = -1





    def addWire(self, cellNum):
        #if cellNum[1] != 0: #don't place to the far left 
        width = len(self.grid[0]) #just check the legnth of first row

        #Avoid "OR" branch under "MT" cell
        if self.grid[cellNum[0]-1][0].rungOrOR == "Rung" or self.grid[cellNum[0]-1][cellNum[1]].MTorElement != "MT":
            #make row below from a rung to an OR if not already
            if self.grid[cellNum[0]][0].rungOrOR != "OR":#make rung below into OR if not already
                for i in range(width):#fill with OR cells : for in range 0 to width
                    self.grid[cellNum[0]][i].rungOrOR = "OR"
                print "converted to OR row"

            if self.grid[cellNum[0]][cellNum[1]].MTorElement == "MT":
                self.grid[cellNum[0]][cellNum[1]].MTorElement = "blankOR"
                print "MT --> blankOR"

            elif self.grid[cellNum[0]][cellNum[1]].MTorElement == "blankOR":
                self.grid[cellNum[0]][cellNum[1]].MTorElement = "MT"
                print "blankOR --> MT AT ",cellNum[0], ", ", cellNum[1]

        self.reAssignBlockIndex(cellNum)
             
        #self.removeBlankOR()#if deleted all items in OR row, delete it
        self.resetBlankOR()
                
    def placeElememt(self, cellNum, tempCellData,toolToPlace):#put tempCellData into cellNum
    
        if toolToPlace !=None:
            self.placeIcon(cellNum, toolToPlace[1]) 
        ##012##       
        self.grid[cellNum[0]][cellNum[1]].MTorElement = tempCellData.MTorElement
        self.grid[cellNum[0]][cellNum[1]].variableName = tempCellData.variableName
        self.grid[cellNum[0]][cellNum[1]].ioAssign = tempCellData.ioAssign
        self.grid[cellNum[0]][cellNum[1]].comment = tempCellData.comment
        self.grid[cellNum[0]][cellNum[1]].setPoint = tempCellData.setPoint
        self.grid[cellNum[0]][cellNum[1]].setPoint = tempCellData.setPoint
        self.grid[cellNum[0]][cellNum[1]].source_A = tempCellData.source_A
        self.grid[cellNum[0]][cellNum[1]].const_A = tempCellData.const_A
        self.grid[cellNum[0]][cellNum[1]].source_B = tempCellData.source_B
        self.grid[cellNum[0]][cellNum[1]].const_B = tempCellData.const_B
        self.grid[cellNum[0]][cellNum[1]].functType = tempCellData.functType # not used
        #try:
         #   tempCellData.setPoint += 1
        #except TypeError:
        #    
        #else:
        #    self.grid[cellNum[0]][cellNum[1]].setPoint = tempCellData.setPoint
        
    def placeIcon(self, cellNum, toolNum):
        pixmap = self.Tools.toolList[toolNum].pixmap
        item = QtGui.QGraphicsPixmapItem(pixmap)
        item.setPos(self.grid[cellNum[0]][cellNum[1]].midPointX+9,self.grid[cellNum[0]][cellNum[1]].midPointY-73)
        self.scene.addItem(item)

    def placeTextExtra(self, cellNum):
        tcolor = QtGui.QColor(128,128,128,189)
        i = cellNum[0]
        j = cellNum[1]
        if self.grid[cellNum[0]][cellNum[1]].branch:
            self.brnch_node_item_text = QtGui.QGraphicsTextItem("branch")
        elif self.grid[cellNum[0]][cellNum[1]].node:
            self.brnch_node_item_text = QtGui.QGraphicsTextItem("node")
        else:
            self.brnch_node_item_text = QtGui.QGraphicsTextItem(" ")
        self.brnch_node_item_text.setPos(self.grid[i][j].midPointX, self.grid[i][j].midPointY-65)
        self.brnch_node_item_text.setDefaultTextColor(tcolor)
        if self.debugShowBranchNode:
            self.scene.addItem(self.brnch_node_item_text)
        if self.grid[cellNum[0]][cellNum[1]].MTorElement == "blankOR":
            self.cell_mtorele_text = QtGui.QGraphicsTextItem("blankOR")
        else:
            self.cell_mtorele_text = QtGui.QGraphicsTextItem(" ")
        self.cell_mtorele_text.setDefaultTextColor(tcolor)
        self.cell_mtorele_text.setPos(self.grid[i][j].midPointX, self.grid[i][j].midPointY-75)
        if self.debugShowMTorEle:
            self.scene.addItem(self.cell_mtorele_text)

        txt = 'B:{0}'.format(self.grid[cellNum[0]][cellNum[1]].blockIndex)
        self.blockindex_text = QtGui.QGraphicsTextItem(txt)
        self.blockindex_text.setDefaultTextColor(tcolor)
        self.blockindex_text.setPos(self.grid[i][j].midPointX, self.grid[i][j].midPointY-85)
        if self.debugShowBlockIndex:
            self.scene.addItem(self.blockindex_text)

        txt2 = ''
        if self.grid[cellNum[0]][cellNum[1]].brchST:
            txt2 = 'B:ST'
        self.branchST_text = QtGui.QGraphicsTextItem(txt2)
        self.branchST_text.setDefaultTextColor(tcolor)
        self.branchST_text.setPos(self.grid[i][j].midPointX, self.grid[i][j].midPointY-85)
        if self.debugShowBranchST:
            self.scene.addItem(self.branchST_text)

        txt3 = ''
        if self.grid[cellNum[0]][cellNum[1]].brchE:
            txt3 = 'B:E'
        self.branchE_text = QtGui.QGraphicsTextItem(txt3)
        self.branchE_text.setDefaultTextColor(tcolor)
        self.branchE_text.setPos(self.grid[i][j].midPointX, self.grid[i][j].midPointY-85)
        if self.debugShowBranchE:
            self.scene.addItem(self.branchE_text)

        txt4 = ''
        if self.grid[cellNum[0]][cellNum[1]].nodeE:
            txt4 = 'N:E'
        self.nodeE_text = QtGui.QGraphicsTextItem(txt4)
        self.nodeE_text.setDefaultTextColor(tcolor)
        self.nodeE_text.setPos(self.grid[i][j].midPointX, self.grid[i][j].midPointY-85)
        if self.debugShowNodeE:
            self.scene.addItem(self.nodeE_text)

        txt5 = ''
        if self.grid[cellNum[0]][cellNum[1]].nodeST:
            txt5 = 'N:ST'
        self.nodeST_text = QtGui.QGraphicsTextItem(txt5)
        self.nodeST_text.setDefaultTextColor(tcolor)
        self.nodeST_text.setPos(self.grid[i][j].midPointX+32, self.grid[i][j].midPointY-85)
        if self.debugShowNodeST:
            self.scene.addItem(self.nodeST_text)



    def placeText(self, cellNum):#put in name and comment, and setpoint and IO
        i = cellNum[0]
        j = cellNum[1]
        if self.grid[i][j].variableName != None:
            elmtTxt = self.grid[i][j].variableName
            item = QtGui.QGraphicsTextItem(elmtTxt)
            item.setFont( QtGui.QFont("Arial",8))               
            item.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-50)
            self.scene.addItem(item)
        if self.grid[i][j].comment != None:
            elmtTxt = self.grid[i][j].comment
            item = QtGui.QGraphicsTextItem(elmtTxt)
            item.setFont( QtGui.QFont("Arial",8))
            item.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-88)
            self.scene.addItem(item)
        if self.grid[i][j].setPoint != None:
            elmtTxt = str(self.grid[i][j].setPoint)
            item = QtGui.QGraphicsTextItem(elmtTxt)
            item.setFont( QtGui.QFont("Arial",8))
            item.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-40)
            self.scene.addItem(item)
        if self.grid[i][j].ioAssign != None and self.grid[i][j].ioAssign != "Internal":
            elmtTxt = self.grid[i][j].ioAssign
            item = QtGui.QGraphicsTextItem(elmtTxt)
            item.setFont( QtGui.QFont("Arial",6))
            item.setPos(self.grid[i][j].midPointX-5,self.grid[i][j].midPointY-78)
            self.scene.addItem(item)
        #print "source_A:", self.grid[i][j].source_A
        #print "const_A:", self.grid[i][j].const_A
        #print "source_B:", self.grid[i][j].source_B
        #print "const_B:", self.grid[i][j].const_B
        ##013##   larger number = lower position
        if self.grid[i][j].source_A != None:    #math funct is there
            if self.grid[i][j].source_A == "Constant":
                elmtTxt = str(self.grid[i][j].const_A)
                item = QtGui.QGraphicsTextItem(elmtTxt)
                item.setFont( QtGui.QFont("Arial",8))
                item.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-85)
                self.scene.addItem(item)
            else:
                elmtTxt = self.grid[i][j].source_A
                item = QtGui.QGraphicsTextItem(elmtTxt)
                item.setFont( QtGui.QFont("Arial",8))
                item.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-85)
                self.scene.addItem(item)
            if self.grid[i][j].source_B == "Constant":
                elmtTxt = str(self.grid[i][j].const_B)
                item = QtGui.QGraphicsTextItem(elmtTxt)
                item.setFont( QtGui.QFont("Arial",8))
                item.setPos(self.grid[i][j].midPointX,self.grid[i][j].midPointY-59)
                self.scene.addItem(item)
            else:
                elmtTxt = self.grid[i][j].source_B
                item = QtGui.QGraphicsTextItem(elmtTxt)
                item.setFont( QtGui.QFont("Arial",8))
                item.setPos(self.grid[i][j].midPointX-5,self.grid[i][j].midPointY-59)
                self.scene.addItem(item)


            
            
            
    def changeRectangle(self):
        height = len(self.grid)
        width = len(self.grid[0]) 
        #print "height before ", self.scene.sceneRect().height()
        #print "x and y", self.scene.sceneRect().x(),self.scene.sceneRect().y()
        self.rectangle = self.scene.sceneRect()
        self.rectangle.setHeight((height*60)+20)
        self.rectangle.setWidth((width*60)+20)
        self.rectangle.setX(-12)
        self.rectangle.setY(-40)
        self.scene.setSceneRect(self.rectangle)
        #print "new height ", self.scene.sceneRect().height()
        
    def checkOrphanName(self,cellNum):#checks if an element will be connected to a non-existent register
        orphan = False
        if self.grid[cellNum[0]][cellNum[1]].MTorElement == "ADC"or\
                self.grid[cellNum[0]][cellNum[1]].MTorElement == "Timer"or\
                self.grid[cellNum[0]][cellNum[1]].MTorElement == "Counter":
  
            thisVarName = self.grid[cellNum[0]][cellNum[1]].variableName
            height= len(self.grid)
            width = len(self.grid[0]) #just check the legnth of first row
            for i in range(height):
                for j in range(width):
                    #if cellNum[0] != i and cellNum[1] != j:
                    if self.grid[i][j].source_A == thisVarName or self.grid[i][j].source_A == thisVarName:
                        orphan = True
                        messageBox = QtGui.QMessageBox()
                        messageBox.information(None,"Error"," Elements share this name")
                        #messageBox.exec_()
                        
        return orphan
