#!/usr/bin/env python
# -*- coding: utf-8 -*- 


"""
Waltech Ladder Maker is distributed under the MIT License. 

Copyright (c) 2014 Karl Walter.  karl (at) waltech.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

#this wil be the ladder grid to C functions
# cell structure:
#(self, midPointX, midPointY, MTorElement, rungOrOR, variableName, ioAssign, comment, setPoint):
import popupDialogs
from managegrid import ManageGrid       

class ladderToOutLine():
    
    def __init__(self,grid):#bring in all the things being sent down here
        self.grid = grid



    def markStartsAndEnds(self):
        outLine = ["//Start of Ladder:"]
        height = len(self.grid)
        width = len(self.grid[0])
        ManageGrid(self.grid, None, None,None).markStartsAndEnds()

    def makeOutLine(self):
        #go through the grid and create a text file with if-then and or statements
        outLine = ["//Start of Ladder:"]
        height = len(self.grid)
        width = len(self.grid[0])
        ManageGrid(self.grid, None, None,None).findStartsAndEnds()

        branchList= [[None,None]] # i branch number, j location on branch
        nodeList = [[None]] # list of branches for this node
        nodesUsed = 0 #keeps track of nodes already put into outLine
        
        for i in range(height):
        
            #>>>>PROCESS RUNG
            #>>>> Not an OR branch, not blank row.  Not an OR branch and is a blank row, but has an OR below
            #>>>>
            RungToDo = False# see if is a rung with something on it
            if self.ORhere(i,0) == False and self.blankRow(i) == False: RungToDo = True
            if self.ORhere(i,0) == False and self.blankRow(i) == True and\
                    i!=height-1 and self.ORhere(i+1,0) == True: RungToDo = True 
                       
            if RungToDo == True: 
                #>>>determine number of branches under this rung:
                hitRung = False
                numBranches = 0
                if i != height-1:
                    d = i+1
                    while hitRung == False:
                        if d == height: hitRung = True
                        elif self.ORhere(d,0) == False: hitRung = True
                        else: 
                            numBranches = numBranches +1
                            d = d+1          
                for z in range(i,i+numBranches+1):
                    #>>>> CHECK FOR Stateusers: Timers, counters, edge etc
                    #>>>> Anyting that uses the rung state as an input to itself
                    #>>>>   similar to branch w/outputs below.  Makes a new invisible rung that is processed first.
                    #check through this rung and associated branchs for timer or counter
                    #record position
                    #make a rightturnlist
                    stateUsers = self.rungStateUser(z)# a stateUser is a counter or timer falling edge or the like
                    if stateUsers != [None]:
                        for x in range(1,len(stateUsers)): #run this for each of the stateUsers found
                            p=z
                            print "$$$$$ making fake rung for State User", x
                            #work from stateUser left and up:     
                            hitRung = False
                            if self.ORhere(p,0) == False: 
                                hitRung = True #stateUser is on rung, not branch
                                print "yes stateUser is on main rung"
                            
                            j = stateUsers[x][2] #start at StateUser and work left
                            print "$$$$ pos of stateuser:",p,j
                            p,rightTurnList = self.loadRightTurns(p,j,hitRung)
                            #process as a Rung:
                            position = stateUsers[x][2] +1
                            tempOutLine = ["//StateUser"]
                            self.processRung(p,branchList,tempOutLine,nodeList,rightTurnList,position)
                            #remove any branchST not included in node
                            self.straybranchSTcheck(branchList,tempOutLine,nodeList)
                            outLine = outLine+tempOutLine
                #>>> now process rung normally:     
                self.processRung(i,branchList,outLine,nodeList,None,width)
            #end if rungToDo     
            #>>>>process branches with outputs:
            #>>>> 
            if self.ORhere(i,0) == True and self.blankRow(i) == False:#
                if self.isOutOnOR(i,width-1) == True:
                    print "BRANCH W/OUTPUT: on branch at row", i 
                    hitRung = False
                    j = width-1# start at right
                    i,rightTurnList = self.loadRightTurns(i,j,hitRung)
                    #process as a Rung:
                    #print"rightturnlist", rightTurnList
                    self.processRung(i,branchList,outLine,nodeList,rightTurnList,width) 

                
        #outline done, output.
        print "Outline:\n"
        for i in range(len(outLine)):
            print outLine[i]
        
        return outLine


#>>>>>>>>>>>>>>>>>>functions below<<<<<<<<<<<<<<<<<<<<<<<

    def processRung(self,i,branchList,outLine,nodeList,rightTurnList,position):
        
        #This funtion does one of three things: 
        #Process stateUsers, Process brances with outputs, and Process Nomal rows
        #looks at position and rightTurnLis to determine type of processing to do 
        print "processing rung"
        height = len(self.grid)
        width = len(self.grid[0])
        p = i # save rung, i will change if righturnlist is used
        if rightTurnList != None and width == position:
            outLine.append("//output brnch connected to rung at " +str(i))
        elif rightTurnList != None and width > position:
            outLine.append("//connected to rung at " +str(i))
        else:
            outLine.append("//rung at " +str(i))
        
        #>>>normal process row:
        for j in range(position): #go through cells on this row if it is a rung
                    
            #>>>Check for branch:
            #print "$$$ p",p,"i",i,"righturnlist",rightTurnList
            i = self.rightTurnListCheck(i,j, rightTurnList)
            self.branchStart(i,j,branchList,outLine,rightTurnList)# check for branch and add to branchList
            
            #>>>put in element if there is one:
            if j <position-1:
                #print"adding element"
                self.addElementToOutline(i,j,outLine)
            #>>>check for node Start:
            self.nodeStart(i,j,nodeList,outLine,branchList,rightTurnList)
            
        #>>>Add stateusers here:
        if position < width : # position< width means a timer, edg, etc
            print "adding stateuser"
            p = self.rightTurnListCheck(i,j, rightTurnList)
            self.branchStart(i,position-1,branchList,outLine,rightTurnList)# check for branch and add to branchList
            if self.grid[p][position-1].variableName !=None :
                outLine.append([ "rungstate_"+str(self.grid[p][position-1].MTorElement) +"_"+ str(self.grid[p][position-1].variableName)])
            else:
                outLine.append(["rungstate_"+str(self.grid[p][position-1].MTorElement) +"_"+ str(p) +"_"+ str(position-1)])
            print "added", outLine[-1][0]

        
        
        #>>>add output
        
        if self.grid[i][len(self.grid[i])-1].variableName !=None and \
                    self.grid[i][len(self.grid[i])-1].source_A == None and \
                    self.grid[i][len(self.grid[i])-1].const_A == None and \
                    self.grid[i][len(self.grid[i])-1].MTorElement != "ADC" and \
                    width == position  : 
                    #has a name exists 
                    #is not math
                    #is not math or pwm
                    #is not adc
                    #width == position means an output
            print "adding output"
            outLine.append(["output_" + str(self.grid[i][-1].variableName),\
                        str(self.grid[i][-1].ioAssign)])
            print "added", outLine[-1][0]
            
        ##021##
        #>>>add result (math, move, ADC)
        if self.grid[i][len(self.grid[i])-1].variableName !=None and \
                    self.grid[i][len(self.grid[i])-1].source_A != None and \
                    self.grid[i][len(self.grid[i])-1].const_A != None and \
                    width == position  : 
                    #has a name exists 
                    #is has a source
                    #is has a source
                    #width == position means an output
            print "adding result"
            outLine.append(["Result_"+ str(self.grid[i][-1].variableName),\
                        str(self.grid[i][j].MTorElement), \
                        str(self.grid[i][j].source_A), \
                        str(self.grid[i][j].source_B), \
                        str(self.grid[i][j].const_A), \
                        str(self.grid[i][j].const_B)])
            print "added", outLine[-1][0]
        
        #if self.grid[i][len(self.grid[i])-1].MTorElement != None: 
        #    print "MEORELEMENT: ",self.grid[i][len(self.grid[i])-1].MTorElement  
           
        if self.grid[i][len(self.grid[i])-1].MTorElement == "ADC" and\
                    width == position  : 
                    #width == position means an output
            print "adding ADC"
            outLine.append(["ADC_" + str(self.grid[i][-1].variableName),\
                        str(self.grid[i][-1].ioAssign)])
            print "added", outLine[-1][0]
            
        if self.grid[i][len(self.grid[i])-1].MTorElement == "PWM" and\
                    width == position  : 
                    #width == position means an output
            print "adding PWM"
            outLine.append(["PWM_" + str(i)+"_"+str(j),\
                        str(self.grid[i][-1].ioAssign),\
                        str(self.grid[i][j].setPoint)])              
            print "added", outLine[-1][0]
            
        outLine.append("//end rung \n")
        print "\n"
    
    def loadRightTurns(self,i,j,hitRung):
        rightTurnList = [None] #will contain any right turn branches
        while hitRung == False:
            # go left to branch
            print "i,j",i,j
            print "self.grid[i][j].branch:", self.grid[i][j].branch
            while self.grid[i][j].branch == False:
                j = j-1
            print"going up from i,j at branch" ,i,j
            #go up to branch that goes left.  adding righturns as found
            i = i-1
            for g in range(1024): #max righturns 
                #situation: directly above in parallel:
                if self.grid[i][j].brchST == True and self.MTorLeft(i,j) == True:
                    rightTurnList.append([i,j])
                #situation: hit a row with something to left:
                if self.grid[i][j].brchST == True and self.MTorLeft(i,j) == False:
                    rightTurnList.append([i,j])
                    break
                #may not need the next: (safetys)
                #situation: hit rung   
                if self.ORhere(i,0) == False:
                    hitRung = True
                    break
                #situation: hit top rung
                if i == 0: 
                    hitRung = True
                    break
                #move up one
                i = i-1
            if self.ORhere(i,0) == False: hitRung = True
        return i,rightTurnList
                                    
    
    """    
    def straybranchSTcheck(self,ranchList,tempOutLine,nodeList):
		#look through tempOutline, find branchST ex: ['startBR', [0, 1]]
		#record i,j of this
		# then look for ['node_', [0, 2], [1, 1], [0, 1]]
		#see if i,j is in this node position 2 or more
		#if not, pop that startBR
        print "stray branch check"
        unusedbrSTlist = [None,None]
        loc = [None,None]
        for x in range(len(tempOutLine)):
            for y in range(len(tempOutLine[x])):
                if tempOutLine[x][y][:7] == 'startBR':
                    loc= tempOutLine[x][1]
                    print "branchst found" ,loc
                    foundInNode = False
                    for z in range(len(tempOutLine)):
                        for a in range(len(tempOutLine[z])):
                            if tempOutLine[z][a][:5] == 'node_':
                                for g in range(2,len(tempOutLine[x])):
                                    if loc == tempOutLine[x][g]:foundInNode = True
                    if foundInNode==False:
                        print "brachST not in a node"
                        unusedbrSTlist.append(loc)
        for x in range(1,len(unusedbrSTlist)):
            loc = unusedbrSTlist[x]
            for z in range(len(tempOutLine)):
                for a in range(len(tempOutLine[z])):
                    if tempOutLine[z][a][:7]=='startBR' and loc== tempOutLine[z][1]:
                        tempOutLine.pop(z)
                        break
                    else: print "nope ", (tempOutLine[z][a])[:7]
	"""		 
    def straybranchSTcheck(self,ranchList,tempOutLine,nodeList):
		#look through tempOutline, find branchST ex: ['startBR', [0, 1]]
		#record i,j of this
		# then look for ['node_', [0, 2], [1, 1], [0, 1]]
		#see if i,j is in this node position 2 or more
		#if not, pop that startBR
        print "straybranchcheck"
        unusedbrSTlist = [None,None]
        loc = [None,None]
        for x in range(len(tempOutLine)):
            print "tempoutline x", tempOutLine[x]
            if 'startBR' in tempOutLine[x]:
				loc= tempOutLine[x][1]
				print "startBR found" ,loc,tempOutLine[x]
				foundInNode = False
				for z in range(len(tempOutLine)):
					if 'node_' in tempOutLine[x]:
						for g in range(2,len(tempOutLine[x])):
							if loc == tempOutLine[x][g]:foundInNode = True
				if foundInNode==False:
					print "brachST not in a node"
					unusedbrSTlist.append(loc)
        for x in range(1,len(unusedbrSTlist)):
			loc = unusedbrSTlist[x]
			for z in range(len(tempOutLine)):
				if 'startBR' in tempOutLine[z] and loc== tempOutLine[z][1]:
					tempOutLine.pop(z)
					break			
		
    
        
    def rungStateUser(self,i): #returns list of names of ststeUsers, and their position
        #Note: determines type by comparing to a list here.  Timer, Counter, Falling...
        stateUser = [None]
        width = len(self.grid[1])
        for q in range (width-1):
            if self.grid[i][q].MTorElement == "Timer" or\
                   self.grid[i][q].MTorElement == "Counter" or\
                   self.grid[i][q].MTorElement == "Fall" :
                stateUser.append([self.grid[i][q].MTorElement,i,q])
        return stateUser    
        
    #
    ### small helper, grid check functions: 
    #
    
    def isOutOnOR(self,i,j):
        outonOR = False
        width = len(self.grid[1])
        #if j == width-1:print "checking if output on OR",i,j
        if j == width-1 and self.ORhere(i,j) == True\
            and self.grid[i][j].MTorElement != "MT"\
            and self.grid[i][j].MTorElement !="blankOR" :
            outonOR = True
        return outonOR
        
    def MTorLeft(self,i,j):
        leftMTOR = False
        if j>=1:
            if(self.grid[i][j-1].MTorElement == "MT" and self.grid[i][j-1].rungOrOR =="OR"): 
                leftMTOR = True
        if j == 0: leftMTOR = True
        return leftMTOR
              
    def ORhere(self,i,j):
        if  self.grid[i][j].rungOrOR == "OR":
            return True
        else: return False 
    
    def blankRow(self,i):
        allMT = True
        for k in range (len(self.grid[i])):   
            if self.grid[i][k].MTorElement != "MT":
                allMT = False
        return allMT
    
    #
    ###  
    # 
    
    def rightTurnListCheck(self, i,j, rightTurnList):
        #check in rightTurnList for this branch start:
        doneGoingRight = False
        c = 0
        z = 0
        while doneGoingRight == False:
            z = i
            if self.grid[i][j].brchST == True:
                if rightTurnList != None and len(rightTurnList)>1:
                    print ">righturnlist being used<", rightTurnList 
                    for x in range(1,len(rightTurnList)):
                        if rightTurnList[x] == [i,j]:
                            i = i+1
                            while self.grid[i][j].MTorElement == "MT":#need to check for MT
                                i = i+1 
            c=c+1
            if c>1024: break
            if z == i: doneGoingRight = True
        return i
      
    def branchStart(self,i,j,branchList,outLine,rightTurnList):
        if self.grid[i][j].brchST == True:
            #check down for branches with output:
			#if it is false, it adds the branch.  keeps branches 
			#w/o corresponding ndes from being added
            toOutput = False
            height = len(self.grid)
            width = len(self.grid[i])
            p=i+1
            while self.grid[p][j].branch == True :
                #if self.isOutOnOR(p,width-1) == True and self.grid[p][j].MTorElement != "blankOR":
                if self.isOutOnOR(p,width-1) == True:
                    #outLine.append("right turn")
                    toOutput = True
                    break
                p=p+1
                if p == height: break
            #    
            if toOutput == False:
                self.branchAdd(i,j,branchList,outLine,True)
        return i
            
     
                    
    def branchAdd(self,i,j,branchList,outLine,start):
        if branchList[0] == [None,None] : #for the very first one, don't append 
            branchList[0]=[i,j]
        else:
            branchList.append([i,j]) #add the new branch location
        lastBranch  = len(branchList)-1
        print "_____adding br_",str(branchList[lastBranch][0]),str(branchList[lastBranch][1])
        if start == True:
            outLine.append(["startBR",branchList[lastBranch]])
        else:
            outLine.append(["branch",branchList[lastBranch]])
            
            #outLine.append("br_" +str(branchList[lastBranch][0])\
             #       +"_"+str(branchList[lastBranch][1]))
                
                
    def nodeStart(self,i,j,nodeList,outLine,branchList,rightTurnList):
        if self.grid[i][j].nodeST == True:
            self.processNode(i,j,outLine,branchList,nodeList,rightTurnList)
            
    
    #put in element if there is one: 
    ##020##       
    def addElementToOutline(self,i,j,outLine):
        """
        "Fall"
        "Timer"
        "Counter"
        "contNO"
        "contNC"
        "Equals"
        .
        .
        .
        """
        
        width = len(self.grid[i])
        ##"cont_" 
        if self.grid[i][j].MTorElement == "contNO" \
                or self.grid[i][j].MTorElement =="contNC"\
                and j<width-1:
            outLine.append(["cont_" + str(self.grid[i][j].variableName),\
                        str(self.grid[i][j].MTorElement), \
                        str(self.grid[i][j].ioAssign)])
                        
        if self.grid[i][j].MTorElement == "Fall" \
                and j<width-1:
            outLine.append(["Fall_"+ str(i)+"_"+str(j),\
                        str(self.grid[i][j].MTorElement), \
                        str(self.grid[i][j].setPoint),\
                        "latching"])
                        
        if self.grid[i][j].MTorElement == "Timer" \
                and j<width-1:
            outLine.append(["Timer_" + str(self.grid[i][j].variableName),\
                        str(self.grid[i][j].MTorElement), \
                        str(int(self.grid[i][j].setPoint*100))])
                        
        if self.grid[i][j].MTorElement == "Counter" \
                and j<width-1:
            outLine.append(["Counter_" + str(self.grid[i][j].variableName),\
                        str(self.grid[i][j].MTorElement), \
                        str(self.grid[i][j].setPoint),\
                        "latching"])
        #"Equals" "Greater""Lessthan""GreaterOrEq""LessOrEq"
        if self.grid[i][j].MTorElement == "Equals" \
                and j<width-1:
            outLine.append(["Equals_"+ str(i)+"_"+str(j),\
                        str(self.grid[i][j].source_A), \
                        str(self.grid[i][j].source_B), \
                        str(self.grid[i][j].const_A), \
                        str(self.grid[i][j].const_B)])
        if self.grid[i][j].MTorElement == "Greater" \
                and j<width-1:
            outLine.append(["Greater_"+ str(i)+"_"+str(j),\
                        str(self.grid[i][j].source_A), \
                        str(self.grid[i][j].source_B), \
                        str(self.grid[i][j].const_A), \
                        str(self.grid[i][j].const_B)])
        if self.grid[i][j].MTorElement == "Lessthan" \
                and j<width-1:
            outLine.append(["Lessthan_"+ str(i)+"_"+str(j),\
                        str(self.grid[i][j].source_A), \
                        str(self.grid[i][j].source_B), \
                        str(self.grid[i][j].const_A), \
                        str(self.grid[i][j].const_B)])
        if self.grid[i][j].MTorElement == "GreaterOrEq" \
                and j<width-1:
            outLine.append(["GreaterOrEq_"+ str(i)+"_"+str(j),\
                        str(self.grid[i][j].source_A), \
                        str(self.grid[i][j].source_B), \
                        str(self.grid[i][j].const_A), \
                        str(self.grid[i][j].const_B)])
        if self.grid[i][j].MTorElement == "LessOrEq" \
                and j<width-1:
            outLine.append(["LessOrEq_"+ str(i)+"_"+str(j),\
                        str(self.grid[i][j].source_A), \
                        str(self.grid[i][j].source_B), \
                        str(self.grid[i][j].const_A), \
                        str(self.grid[i][j].const_B)])
        
    def addNodeToOutline(self,nodeList,outLine,i,j): 
        nodeString = ""
        #look through nodelist and find i,j:
        for x in range(len(nodeList)):
            if nodeList[x][0] == [i,j]:
                nodeList[x].insert(0,"node_")
                outLine.append(nodeList[x])

   #puts a branch into a node
    def addToNode(self,node,i,j,nodeList):
        alreadyHere = False
        for x in range(1,len(nodeList[node])):
            if nodeList[node][x] == [i,j]:
                alreadyHere = True
        if alreadyHere == False:
            nodeList[node].append([i,j])
            self.outputnodelist(nodeList)
       
    def outputnodelist(self, nodeList):
        for w in range(len(nodeList)):
            print "      ",nodeList[w]
        #print"\n"
    
    def countParallels(self,i,j):#Check how many parallel rows there are for this node:
        p=i #save i
        q=j #save j
        startBrJ = None
        blanks = 0
        parallels = 0
        for z in range(len(self.grid)-i-1): # look down to end of grid, max
            q=j #reset q
            if self.grid[p][q].nodeE ==True:
                break 
            p = p+1#go down to next node
            if self.grid[p][q].MTorElement == "MT":#if MT, keep going down
                blanks=blanks+1
                continue
            while self.grid[p][q].branch == False: #go left to branch, 
                q = q-1
                if q<0:
                    break 
            if parallels == 0:#first time to left, record start branch j
                startBrJ = q 
                parallels = parallels +1
                continue
            if parallels >0 and q == startBrJ:#this branch is parallel
                parallels = parallels +1
            if parallels >0 and q != startBrJ:# not a parallel branch
                break
            #if self.grid[p][q].brchE = True:
            #    break
        if parallels>1:
            print"MORE THAN TWO PARALLELS"
            self.dialog = popupDialogs.ThreeParallelsDialog()
            self.dialog.setWindowTitle('parallelOR')
            self.dialog.setGeometry(100, 100, 290, 120)
            self.dialog.exec_()# For Modal dialogs
        return parallels+blanks
    
    #>>>PROCESS NODE:
    #>>>
    def processNode(self,i,j,outLine,branchList,nodeList,rightTurnList):
        height = len(self.grid)
        
        #>>>make node, set to current
        print ">>>making new node ", i,j
        if nodeList[0] == [None]:
            nodeList[0] = [[i,j]]
            activeNode = 0    
        else:
            nodeList.append([[i,j]])
            activeNode = len(nodeList)-1
        self.outputnodelist(nodeList) 
           
        #see how many parallels go in this node:
        parallels = self.countParallels(i,j)
        
        #Now process these parallels
        for z in range(parallels):    
            #>>>go down to next node
            print ">>>going down to next node"
            i=i+1

            if self.grid[i][j].MTorElement == "MT":  #it's a blank, go on
                continue
                
            #>>>go left to BRANCH    
            print ">>> going left to branch"    
            while self.grid[i][j].branch == False: 
                j = j-1
            
            #>>> add branch to branchlist
            print ">>> adding this branch: ", i ,j
            self.branchAdd(i,j,branchList,outLine,False)  
            
            #>>>add branch to node at current node's i:
            self.addToNode(activeNode,i,j,nodeList) 
        
            #>>>go up and add start branch to node at this j:
            p = nodeList[activeNode][-1][0]
            print "p (=nodeList[activeNode][-1][0]) is ",p
            while self.grid[p][j].brchST == False:# go up to brchST
                p = p-1
            print ">>> and adding start branch: ",  p,j
            self.addToNode(activeNode,p,j,nodeList)#add branch from node's i and this j  

            #>>>head right
            print ">>>heading right"
            q=nodeList[activeNode][0][1]# j of active node
            while j!=q:
                #>>>put in element if there is one:
                print "chk for elmt"
                self.addElementToOutline(i,j,outLine)
                #>>>check for node Start:
                #>>>NOTE: don't check for start-branch druring parallels, except last one<<<
                #if j!=q or z == parallels:
                print "chk for node st"
                self.nodeStart(i,j,nodeList,outLine,branchList,rightTurnList)
                j=j+1
                #>>>Check for branch:
                print "chk for br ST"
                i = self.rightTurnListCheck(i,j, rightTurnList)
                self.branchStart(i,j,branchList,outLine,rightTurnList)# check for branch and add to branchList
            
            #>>>put in element if there is one:
            print "chk for elmt"
            self.addElementToOutline(i,j,outLine)
        #done with this batch of parallels
        print "adding node to outline"
        p=nodeList[activeNode][0][0]
        q=nodeList[activeNode][0][1]
        self.addNodeToOutline(nodeList,outLine,p,q)
        #>>>check for node Start here at end of parallels at j of node:
        self.nodeStart(i,j,nodeList,outLine,branchList,rightTurnList)

        
   
   
   
   

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
