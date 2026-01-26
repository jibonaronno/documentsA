"""
Waltech Ladder Maker is distributed under the MIT License. 

Copyright (c) 2014 Karl Walter.  karl (at) waltech.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""
#!/usr/bin/env python
# -*- coding: utf-8 -*- 

#this wil be the outline to C functions
from PyQt4 import QtCore, QtGui
from PyQt4.Qt import QFont
from managegrid import ManageGrid  
import sys     

class OutLineToC():
    
    def __init__(self,grid,currentHW):#bring in all the things being sent down here
        self.grid = grid
        self.currentHW = currentHW
        
        if self.currentHW == "Waltech":
            #>>>inputs for Waltech IC
            self.inPutList = ["PINA",4],["PINA",3],["PINA",2],["PINA",1]\
                            ,["PINB",0],["PINB",1],["PINB",2],["PINB",3]\
                            ,["PINC",0],["PINC",1],["PINC",2],["PINC",3]
            #>>>outputs:                
            self.outPutList = ["PORTD",2],["PORTD",3],["PORTD",4],["PORTD",5]\
                            ,["PORTB",4],["PORTA",5],["PORTA",6],["PORTA",7]\
                            ,["PORTC",4],["PORTC",5],["PORTC",6],["PORTC",7]
            self.ADCList = []
            self.PWMList = []
                            
        if currentHW == "ArduinoUno":
            #>>>inputs 
            self.inPutList = ["PINC",4],["PINC",5],["PIND",2],["PIND",3]\
                            ,["PIND",4]
            #>>>outputs:                
            self.outPutList =["PORTD",5],["PORTD",6],["PORTD",7]\
                            ,["PORTB",0],["PORTB",3],["PORTB",4],["PORTB",5]
                            
            self.ADCList  = ["DDRC",0,0],["DDRC",1,1],["DDRC",2,2],["DDRC",3,3]
            #mode8 PWM on 16 bit timer
            self.PWMList  = ["DDRB","1","TCCR1A","----","COM1A1","TCCR1B","WGM13","CS10","OCR1A","ICR1"],\
                            ["DDRB","2","TCCR1A","----","COM1B1","TCCR1B","WGM13","CS10","OCR1B","ICR1"]
            
        if currentHW == "ArduinoNano": #same as Uno
            #>>>inputs 
            self.inPutList = ["PINC",4],["PINC",5],["PIND",2],["PIND",3]\
                            ,["PIND",4]
            #>>>outputs:                
            self.outPutList =["PORTD",5],["PORTD",6],["PORTD",7]\
                            ,["PORTB",0],["PORTB",3],["PORTB",4],["PORTB",5]
                            
            self.ADCList  = ["DDRC",0,0],["DDRC",1,1],["DDRC",2,2],["DDRC",3,3]
            #mode8 PWM on 16 bit timer
            self.PWMList  = ["DDRB","1","TCCR1A","----","COM1A1","TCCR1B","WGM13","CS10","OCR1A","ICR1"],\
                            ["DDRB","2","TCCR1A","----","COM1B1","TCCR1B","WGM13","CS10","OCR1B","ICR1"]
            
        if currentHW == "ArduinoMega":
            #>>>inputs 
            self.inPutList = ["PINK",0],["PINK",1],["PINK",2],["PINK",3],["PINK",4],["PINK",5],["PINK",6],["PINK",7]\
                            ,["PINB",0],["PINB",2]\
                            ,["PINL",0],["PINL",2],["PINL",4],["PINL",6]\
                            ,["PING",0],["PING",2]\
                            ,["PINC",0],["PINC",2],["PINC",4],["PINC",6]
            #>>>outputs:                
            self.outPutList= ["PORTB",1],["PORTB",3]\
                            ,["PORTL",1],["PORTL",3],["PORTL",5],["PORTL",7]\
                            ,["PORTG",1]\
                            ,["PORTD",7]\
                            ,["PORTC",1],["PORTC",3],["PORTC",5],["PORTC",7]\
                            ,["PORTA",6],["PORTA",4],["PORTA",2],["PORTA",0]\
                            ,["PORTD",0],["PORTB",1]

            #>>>PWM:     OK, checked mega2560  
            #Port, pin,(8 other register settings)  
            #in order of pwm_X choices in ladder       
            self.PWMList = ["DDRE","4","TCCR3A","----","COM3B1","TCCR3B","WGM33","CS30","OCR3B","ICR3"],\
                           ["DDRE","5","TCCR3A","----","COM3C1","TCCR3B","WGM33","CS30","OCR3C","ICR3"],\
                           ["DDRE","3","TCCR3A","----","COM3A1","TCCR3B","WGM33","CS30","OCR3A","ICR3"],\
                           \
                           ["DDRH","3","TCCR4A","----","COM4A1","TCCR4B","WGM43","CS40","OCR4A","ICR4"],\
                           ["DDRH","4","TCCR4A","----","COM4B1","TCCR4B","WGM43","CS40","OCR4B","ICR4"],\
                           \
                           ["DDRB","5","TCCR1A","----","COM1A1","TCCR1B","WGM13","CS10","OCR1A","ICR1"],\
                           ["DDRB","6","TCCR1A","----","COM1B1","TCCR1B","WGM13","CS10","OCR1B","ICR1"],\
                           ["DDRB","7","TCCR1A","----","COM1C1","TCCR1B","WGM13","CS10","OCR1C","ICR1"]

            #>>>ADC:  
            #Port DDR, pin, ADC channel #don't really need DDR             
            self.ADCList =  ["DDRF",0,0],\
                            ["DDRF",1,1],\
                            ["DDRF",2,2],\
                            ["DDRF",3,3],\
                            ["DDRF",4,4],\
                            ["DDRF",5,5],\
                            ["DDRF",6,6],\
                            ["DDRF",7,7]
                           

        
    def makeC(self,outLine,displayOutputPlace):
        print "making C\n"
        
        C_txt = "#include <stdint.h>\n#include <stdlib.h>\n#include <string.h>\n#include <avr/io.h>\n#include <avr/interrupt.h>\n\n"
        C_txt = C_txt +"volatile uint8_t timerOF=0;\n"
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"#define OVERSAMPLES 10\n"
            
            C_txt = C_txt +"static volatile uint16_t adcData;\n"
            C_txt = C_txt +"static volatile uint16_t ADCtotal;\n"
            C_txt = C_txt +"static volatile uint8_t adcDataL;\n"
            C_txt = C_txt +"static volatile uint8_t adcDataH;\n"
            C_txt = C_txt +"static volatile uint8_t sample_count;\n"
        
        if self.currentHW == "Waltech":
            C_txt = C_txt +"inline ISR(TIMER0_OVF_vect){timerOF=1;}\n"
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"inline ISR(TIMER0_OVF_vect){timerOF=1;}\n"
        
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"inline ISR(ADC_vect)\n{\n"
            C_txt = C_txt +"    adcDataL = ADCL;\n"
            C_txt = C_txt +"    adcDataH = ADCH;\n"
            C_txt = C_txt +"    adcData = 0;\n"
            C_txt = C_txt +"    adcData = adcData | adcDataH;\n"
            C_txt = C_txt +"    adcData = adcData << 8;\n"
            C_txt = C_txt +"    adcData = adcData | adcDataL;\n"
            C_txt = C_txt +"    ADCtotal = ADCtotal+adcData;\n"
            C_txt = C_txt +"    sample_count ++;\n}\n"

        #MATH:
        C_txt = C_txt +"int16_t do_math(int16_t A,int16_t B,char operator)\n{\n"
        C_txt = C_txt +"    int32_t result = 0;\n"
        C_txt = C_txt +"    if (operator == '+'){result = A+B;}\n"
        C_txt = C_txt +"    if (operator == '-'){result = A-B;}\n"
        C_txt = C_txt +"    if (operator == '*'){result = A*B;}\n"
        C_txt = C_txt +"    if (operator == '/'){result = A/B;}\n"
        C_txt = C_txt +"//    if (operator == '='){result = A = B;}\n"
        C_txt = C_txt +"    int16_t i =  ((result >> 0) & 0xffff);\n"
        C_txt = C_txt +"   return i;\n}\n"
        
        #ADC:
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"uint16_t read_adc(uint8_t channel)\n{\n"
            #C_txt = C_txt +"    sei();//set enable interrupts\n"    
            C_txt = C_txt +"    ADMUX = channel;// set channel\n"
            C_txt = C_txt +"    ADMUX |=  (1<<REFS0);// sets ref volts to Vcc\n"
            C_txt = C_txt +"    ADCSRA |= (1<<ADEN); // enable the ADC\n"
            C_txt = C_txt +"    sample_count = 0; ADCtotal = 0;//clear sample count\n"
            C_txt = C_txt +"    ADCSRA |= (1<<ADSC);//start conversion\n"     
            C_txt = C_txt +"    //read adcData done in interrupt\n"
            C_txt = C_txt +"    while (sample_count < OVERSAMPLES){asm volatile (\"nop\"::);}//wait for completion\n"
            C_txt = C_txt +"    ADCSRA &=~ (1<<ADEN); // stop the ADC\n"
            C_txt = C_txt +"    return (ADCtotal/OVERSAMPLES); //mx osamples = 63  othewise will overflow total register with 10 bit adc results\n}\n"

        C_txt = C_txt +"int main()\n"
        C_txt = C_txt +"{\n"
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"//set up ADC\n"    
            C_txt = C_txt +"    ADCSRA |= ( (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) );//  sets adc clock prescaler to 128 //checked\n"
            C_txt = C_txt +"    ADCSRA |= (1<<ADIE); // enable ADC conversion complete interrupt\n"
            C_txt = C_txt +"    ADCSRA |= (1<<ADATE);// set to auto trigger (free running by default)\n"	
        C_txt = self.DDROutPuts(C_txt)#//do DDR's#//use outputlist to generate
        #pullups on for Arduino:
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = self.pullupInPuts(C_txt)
        C_txt = C_txt +"    //set up loop timer:\n"
        if self.currentHW == "Waltech":
            C_txt = C_txt +"    TIMSK |= (1<<TOIE0);// overflow capture enable\n"
            C_txt = C_txt +"    TCNT0 = 101;// start at this\n"
            C_txt = C_txt +"    TCCR0 |= (1<<CS02);// timer started with /256 prescaler  fills up @61 hz\n"
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"    TIMSK0 |= (1<<TOIE0);// overflow capture enable\n"
            C_txt = C_txt +"    TCNT0 = 101;// start at this\n"
            C_txt = C_txt +"    TCCR0B |= ((1<<CS10)|(1<<CS12));// timer started with /1024 prescaler \n "
            C_txt = self.setUpPWMs(outLine,C_txt)
            
        C_txt = C_txt +"    sei();\n"
        C_txt = self.initVarsForMicro(outLine,C_txt)
        C_txt = C_txt +"    uint8_t W = 1;\n"
        C_txt = C_txt +"    while (1)\n"
        C_txt = C_txt +"    {\n"
        C_txt = C_txt +"        if (timerOF == 1)\n"
        C_txt = C_txt +"        {\n"
        
        if self.currentHW == "Waltech":
            C_txt = C_txt +"           timerOF=0;//reset timer flag\n"
            C_txt = C_txt +"           TCNT0 = 101;// start at this\n"
            C_txt = self.findInPuts(outLine,C_txt)
            
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            C_txt = C_txt +"           timerOF=0;//reset timer flag\n"
            C_txt = C_txt +"           TCNT0 = 101;// start at this\n"#ok
            C_txt = self.findInPutsArd(outLine,C_txt)
        
        if self.currentHW == "ArduinoMega"or self.currentHW == "ArduinoUno" or self.currentHW == "ArduinoNano":
            pwmList = []
            for i in range (len(outLine)):
                if "PWM_" == str(outLine[i][0])[:4] and outLine[i][1] not in pwmList:
                    C_txt = C_txt +"           "+str(outLine[i][1]) +" = 0;//set PWM flag to 0\n"
                    pwmList.append(outLine[i][1])

        #go through the outLine and create  if-then and or statements from elements

        currentBranchList=[None]
        for i in range (len(outLine)):
            if "//" in outLine[i]:
                C_txt = C_txt +"            "+str(outLine[i])+"\n" 
            if "rung at" in outLine[i]:
                C_txt = C_txt +"             W = 1;\n"    
            #BRANCHES:    
            if "branch" in outLine[i]: #normal branch, not a starter
                C_txt = C_txt + "             branch_"+\
                        str(outLine[i][1][0])+"_"+str(outLine[i][1][1])+ " = 1;\n" 
                currentBranchList.append(outLine[i][1])#this keeps track of the nested branches
            if "startBR" in outLine[i]:#starter branch.  add to branchlist 
                C_txt = C_txt + "             branch_"+\
                        str(outLine[i][1][0])+"_"+str(outLine[i][1][1])+ " = 1;\n"
                currentBranchList.append(outLine[i][1])#this keeps track of the nested branches
            #print "current branch", currentBranchList
            #COMPARISONS:
            ##027##
            #"Equals" "Greater""Lessthan""GreaterOrEq""LessOrEq"
            if "Equals_" in str(outLine[i][0]):
                C_txt = self.addEquals(outLine, C_txt, i)
            if "Greater_" in str(outLine[i][0]):
                C_txt = self.addGreater(outLine, C_txt, i)
            if "Lessthan_" in str(outLine[i][0]):
                C_txt = self.addLessthan(outLine, C_txt, i)
            if "GreaterOrEq_" in str(outLine[i][0]):
                C_txt = self.addGreaterOrEq(outLine, C_txt, i)
            if "LessOrEq_" in str(outLine[i][0]):
                C_txt = self.addLessOrEq(outLine, C_txt, i)
               
            #ELEMENTS:
            ##026##

            if "cont_" in str(outLine[i][0])\
                    or "Counter_" in str(outLine[i][0])\
                    or "Timer_" in str(outLine[i][0])\
                    or "Fall_" in str(outLine[i][0])\
                    or "Equals_" in str(outLine[i][0])\
                    or "Greater_" in str(outLine[i][0])\
                    or "Lessthan_" in str(outLine[i][0])\
                    or "GreaterOrEq_" in str(outLine[i][0])\
                    or "LessOrEq_" in str(outLine[i][0]):
                varNameStr = str(outLine[i][0])
                if len(outLine[i])>=2 and ("contNO" in outLine[i][1]):
                    varNameStr=varNameStr+"_NO"
                if len(outLine[i])>=2 and ("contNC" in outLine[i][1]):
                    varNameStr=varNameStr+"_NC"      
                if "rungstate" not in str(outLine[i][0]):
                    #element on rung, no parallel: (apply to W)
                    if currentBranchList[-1] == None:
                        if (len(outLine[i])>3) and  ("latching" in outLine[i][3]):
                            C_txt = C_txt + "             if("+varNameStr+ " == 0){W = 0;}\n"
                            C_txt = C_txt + "             else{W = 1;}\n"
                        else:
                            C_txt = C_txt + "             if("+varNameStr+ " == 0){W = 0;}\n"
                    #element with parallel (apply to last item in branchlist )
                    if  currentBranchList[-1] != None:
                        if (len(outLine[i])>3) and  ("latching" in outLine[i][3]):
                            C_txt = C_txt + "             if("+\
                            varNameStr+ " == 0){branch_"+str(currentBranchList[-1][0])+"_"+str(currentBranchList[-1][1])+" = 0;}\n"
                            C_txt = C_txt + "             else {branch_"+str(currentBranchList[-1][0])+"_"+str(currentBranchList[-1][1])+" = 2;}\n"
                        else:
                            C_txt = C_txt + "             if("+\
                                varNameStr+ " == 0){branch_"+str(currentBranchList[-1][0])+"_"+str(currentBranchList[-1][1])+" = 0;}\n"

            
            #NODE:
            #if "node_" in outLine[i][0]:
            if str(outLine[i][0])[:5] == "node_":    
                tempText1 = "             if( " #for node
                tempText2 = "             if( " # for node with latching on it
                for k in range(2,len(outLine[i])):
                    a = outLine[i][k][0]
                    b = outLine[i][k][1]
                    tempText1 = tempText1 + "(branch_"+str(a) + "_"+ str(b)+" == 0) && "
                    tempText2 = tempText2 + "(branch_"+str(a) + "_"+ str(b)+" == 2) || "
                    #Branch tracking:
                    #look through currentBranchList and remove (pop) any matching a,b
                    m = 0
                    while m < len(currentBranchList):
                        if currentBranchList[m] == [a,b]: 
                            #print "A,B here"
                            currentBranchList.pop(m)
                        else: m = m+1

                tempText1 = tempText1[:-5]#take away last " && " or " || "
                tempText2 = tempText2[:-5]#take away last " && " or " || "
                if currentBranchList[-1] != None:
                    tempText1 = tempText1 +" )) {branch_"+str(currentBranchList[-1][0])+"_"+str(currentBranchList[-1][1])+" = 0;} \n" 
                    tempText2 = tempText2 +" )) {branch_"+str(currentBranchList[-1][0])+"_"+str(currentBranchList[-1][1])+" = 1;} \n" 
                else:
                    tempText1 = tempText1 +" )) {W = 0;} //"+ str(outLine[i][0])+ str(outLine[i][1])+"\n"
                    tempText2 = tempText2 +" )) {W = 1;} //"+ str(outLine[i][0])+ str(outLine[i][1])+" if is latching element\n"
                C_txt = C_txt + tempText1+ tempText2
                    
            #State Users: (need to know the last state of the rung and the current state
            #WAS: if "rungstate_Counter" in str(outLine[i][0]):
            if str(outLine[i][0])[:17] ==  "rungstate_Counter":
                C_txt = self.addCounter(outLine, C_txt, str(outLine[i][0]),outLine)
                
            #WAS: if "rungstate_Timer" in str(outLine[i][0]):
            if str(outLine[i][0])[:15] ==  "rungstate_Timer":
                C_txt = self.addTimer(outLine, C_txt, str(outLine[i][0]))
            
            #WAS: if "rungstate_Fall" in str(outLine[i][0]):
            if str(outLine[i][0])[:14] ==  "rungstate_Fall":
                C_txt = self.addFall(outLine, C_txt, str(outLine[i][0]))
            ##028##
            #OUTPUT:
            #WAS: if "output_" in str(outLine[i][0]):
            if str(outLine[i][0])[:7] ==  "output_":
                C_txt = C_txt +"              "+  str(outLine[i][0]) +" = W;\n"
            
            #MATH:
            #WAS: if "Result_" in str(outLine[i][0]):
            if str(outLine[i][0])[:7] ==  "Result_":
                C_txt = self.addMath(outLine, C_txt, i)
            #PWM:
            #WAS: if "PWM_" == str(outLine[i][0])[:4]:
            if str(outLine[i][0])[:4] ==  "PWM_":
                C_txt = self.addPWM(outLine, C_txt, i) 
            #ADC:
            #WAS: if "ADC_" == str(outLine[i][0])[:4]:
            if str(outLine[i][0])[:4] ==  "ADC_" and str(outLine[i][1]) != "Internal":
                C_txt = self.addADC(outLine, C_txt, i)

        C_txt = self.findOutPuts(outLine,C_txt)
        #C_txt = self.linkNames(outLine, C_txt)
        C_txt = C_txt + "       }\n" #end of conditional
        C_txt = C_txt + "   }\n" #end of main loop
        C_txt = C_txt + "}\n" #end of main
        print C_txt
        
        print "saving C and Compiling"
        
        plat = sys.platform.lower()	# try to detect the OS so that a device can be selected...
        print "checked platform", plat
        opSys = "UNK" #default
        
        if   plat[:5] == 'linux': #linux
            opSys = "NIX"
        elif plat == 'win32':       #win32
            opSys = "WIN"
        elif plat == "darwin": #mac
            opSys = "MAC"
            print "found a MAC!"
        if opSys != "UNK":
            from hexmaker import hexMaker
            hexMaker(opSys).saveCfileAndCompile(C_txt,displayOutputPlace,self.currentHW)
        else: print "Op Sys not detected"
        
        
        
        
        
        
        
        
    #go through grid and assign inputs to variables    
    def findInPuts(self,outLine,C_txt):
        C_txt = C_txt +"           //inputs:\n"
        for i in range (len(outLine)):
            #WAS if len(outLine[i])>2 and "in_" in str(outLine[i][2]) :
            if len(outLine[i])>2 and str(outLine[i][2])[:3] == "in_" :
                inNum = (int(outLine[i][2].split("in_")[1])) -1
                microPinString = str(self.inPutList[inNum][0])+ " &(1<<"+str(self.inPutList[inNum][1])+");\n"
                #very unlikley that an element name has "&(1<<" in it  plus the rest of the micropinstring
                if outLine[i][1] == "contNO" and microPinString not in C_txt: 
                    C_txt = C_txt + "           "+str(outLine[i][0])+"_NO = "+microPinString
                if outLine[i][1] == "contNC" and microPinString not in C_txt:
                    C_txt = C_txt + "           "+str(outLine[i][0])+"_NC =~ "+microPinString
            #link inputs to outputs if names shared:
            #print "linking output names"
            if len(outLine[i])>1 and outLine[i][1] == "contNO":
                basename = (str(outLine[i][0])[5:])
                for x in range (len(outLine)):
                    if outLine[x][0][:7] == "output_" and outLine[x][0][7:] == basename:
                        #if "output_"+basename in C_txt: 
                        C_txt = C_txt +"             if(output_"+basename+" == 1){\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NO=1;}\n"
                        C_txt = C_txt +"             else {\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NO=0;} //link name\n"
            if len(outLine[i])>1 and outLine[i][1] == "contNC":
                basename = (str(outLine[i][0])[5:])
                for x in range (len(outLine)):
                    if outLine[x][0][:7] == "output_" and outLine[x][0][7:] == basename:
                        #if "output_"+basename in C_txt: 
                        C_txt = C_txt +"             if(output_"+basename+" == 0){\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NC=1;}\n"
                        C_txt = C_txt +"             else {\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NC=0;} //link name\n"
        C_txt = C_txt +"\n"
        
        return C_txt
    """don't need    
    def findFalling(self,outLine,C_txt):
        #need to write c code to set the falling variable based on the last one
        #will need to setup a falling variable ahead of time like initVarsForMicro
        return C_txt
    """

    #go through grid and assign inputs to variables for Arduino different only because hi is on  
    def findInPutsArd(self,outLine,C_txt):
        C_txt = C_txt +"           //inputs:\n"
        for i in range (len(outLine)):
            #WAS if len(outLine[i])>2 and "in_" in str(outLine[i][2]) :
            if len(outLine[i])>2 and str(outLine[i][2])[:3] == "in_" :
                inNum = (int(outLine[i][2].split("in_")[1])) -1
                microPinString = str(self.inPutList[inNum][0])+ " &(1<<"+str(self.inPutList[inNum][1])+");\n"
                if outLine[i][1] == "contNO" and microPinString not in C_txt:
                    C_txt = C_txt + "           "+str(outLine[i][0])+"_NO =~ "+microPinString
                if outLine[i][1] == "contNC" and microPinString not in C_txt:
                    C_txt = C_txt + "           "+str(outLine[i][0])+"_NC = "+microPinString
            #link inputs to outputs if names shared:
            #print "linking output names"
            if len(outLine[i])>1 and outLine[i][1] == "contNO":
                basename = (str(outLine[i][0])[5:])
                for x in range (len(outLine)):
                    if outLine[x][0][:7] == "output_" and outLine[x][0][7:] == basename:
                        #if "output_"+basename in C_txt: 
                        C_txt = C_txt +"             if(output_"+basename+" == 1){\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NO=1;}\n"
                        C_txt = C_txt +"             else {\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NO=0;} //link name\n"
            if len(outLine[i])>1 and outLine[i][1] == "contNC":
                basename = (str(outLine[i][0])[5:])
                for x in range (len(outLine)):
                    if outLine[x][0][:7] == "output_" and outLine[x][0][7:] == basename:
                        #if "output_"+basename in C_txt: 
                        C_txt = C_txt +"             if(output_"+basename+" == 0){\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NC=1;}\n"
                        C_txt = C_txt +"             else {\n"
                        C_txt = C_txt +"                "+str(outLine[i][0])+"_NC=0;} //link name\n"
        C_txt = C_txt +"\n"
        
        return C_txt



    def addCounter(self,outline, C_txt, outlineEntry, wholeOutline):
        C_txt = C_txt +"             "+  outlineEntry +" = W;\n"
        baseName = outlineEntry[10:]
        C_txt = C_txt +"             if((prev_rungstate_"+baseName+" == 0) && (rungstate_"+baseName+" == 1)){\n"
        C_txt = C_txt +"                 reg_"+baseName +"++;\n"
        C_txt = C_txt +"                 if (reg_"+baseName+" == 65535) {reg_"+baseName+"--;}//avoid overrun\n" 
        C_txt = C_txt +"                 if (setpoint_"+baseName+" <= reg_"+baseName+") {"+baseName+"=1;}\n"
        #C_txt = C_txt +"                 if (setpoint_"+baseName+" <= reg_"+baseName+") {W=1;}\n"
        C_txt = C_txt +"             }\n"
        C_txt = C_txt +"             prev_rungstate_"+baseName+" = rungstate_"+baseName+";\n"
        #check reset/ shared name with output:
        baseName = baseName[8:]
        #if "output_"+baseName in C_txt:
        for x in range (len(wholeOutline)):
            if wholeOutline[x][0][:7] == "output_" and wholeOutline[x][0][7:] == baseName:
                C_txt = C_txt +"             if(output_"+baseName+" == 1){reg_Counter_"+baseName+"=0; Counter_"+baseName+"=0;} //reset\n"
        return C_txt
        
    def addTimer(self,outline, C_txt, outlineEntry):
        C_txt = C_txt +"             "+  outlineEntry +" = W;\n"
        baseName = outlineEntry[10:]
        C_txt = C_txt +"             if((prev_rungstate_"+baseName+" == 0) && (rungstate_"+baseName+" == 1)){\n"
        C_txt = C_txt +"                run_"+baseName +"=1;}\n"
        C_txt = C_txt +"             if(run_"+baseName+" == 1){\n"
        C_txt = C_txt +"                reg_"+baseName +"++;\n"
        C_txt = C_txt +"                if (reg_"+baseName+" == 65535) {reg_"+baseName+"--;}//avoid overrun\n" 
        C_txt = C_txt +"                if (setpoint_"+baseName+" <= reg_"+baseName+") {"+baseName+"=1;}\n"
        C_txt = C_txt +"             }\n"
        
        #check reset/ shared name with output:
        #baseName = baseName[6:]
        C_txt = C_txt +"             if((prev_rungstate_"+baseName+" == 1) && (rungstate_"+baseName+" == 0)){\n" 
        C_txt = C_txt +"                reg_"+baseName+"=0; "+baseName+"=0; run_"+baseName+"=0;} //reset\n"
        C_txt = C_txt +"             prev_rungstate_"+baseName+" = rungstate_"+baseName+";\n"
        return C_txt
    
    def addFall(self,outline, C_txt, outlineEntry):
        baseName = outlineEntry[10:]
        C_txt = C_txt +"             if("+baseName+" == 1){"+baseName+" = 0;}\n"
        C_txt = C_txt +"             "+  outlineEntry +" = W;\n"
        
        C_txt = C_txt +"             if((prev_rungstate_"+baseName+" == 1) && (rungstate_"+baseName+" == 0)){\n"
        C_txt = C_txt +"             "+baseName+"=1;\n"
        C_txt = C_txt +"             }\n"
        C_txt = C_txt +"             prev_rungstate_"+baseName+" = rungstate_"+baseName+";\n"
        return C_txt
  
   
    #COMPARISONS:    
    def addEquals(self,outline, C_txt, line):
        if outline[line][1] == "Constant":
            C_txt = C_txt +"             if("+ str(outline[line][3]) +" == "
        else:
            C_txt = C_txt +"             if("+self.outputAndName(outline,outline[line],1)+" == "
        if outline[line][2] == "Constant":
            C_txt = C_txt + str(outline[line][4])+"){"
        else:
            C_txt = C_txt + self.outputAndName(outline,outline[line],2)+"){"
        
        C_txt = C_txt +str(outline[line][0])+"=1;}\n" 
        C_txt = C_txt +"             else {"
        C_txt = C_txt +str(outline[line][0])+"=0;} //comparison\n"
        return C_txt
    def addGreater(self,outline, C_txt, line):
        if outline[line][1] == "Constant":
            C_txt = C_txt +"             if("+ str(outline[line][3]) +" > "
        else:
            C_txt = C_txt +"             if("+self.outputAndName(outline,outline[line],1)+" > "
        if outline[line][2] == "Constant":
            C_txt = C_txt + str(outline[line][4])+"){"
        else:
            C_txt = C_txt + self.outputAndName(outline,outline[line],2)+"){"
        
        C_txt = C_txt +str(outline[line][0])+"=1;}\n" 
        C_txt = C_txt +"             else {"
        C_txt = C_txt +str(outline[line][0])+"=0;} //comparison\n"
        return C_txt
    def addLessthan(self,outline, C_txt, line):
        if outline[line][1] == "Constant":
            C_txt = C_txt +"             if("+ str(outline[line][3]) +" < "
        else:
            C_txt = C_txt +"             if("+self.outputAndName(outline,outline[line],1)+" < "
        if outline[line][2] == "Constant":
            C_txt = C_txt + str(outline[line][4])+"){"
        else:
            C_txt = C_txt + self.outputAndName(outline,outline[line],2)+"){"
        
        C_txt = C_txt +str(outline[line][0])+"=1;}\n" 
        C_txt = C_txt +"             else {"
        C_txt = C_txt +str(outline[line][0])+"=0;} //comparison\n"
        return C_txt
    def addGreaterOrEq(self,outline, C_txt, line):
        if outline[line][1] == "Constant":
            C_txt = C_txt +"             if("+ str(outline[line][3]) +" >= "
        else:
            C_txt = C_txt +"             if("+self.outputAndName(outline,outline[line],1)+" >= "
        if outline[line][2] == "Constant":
            C_txt = C_txt + str(outline[line][4])+"){"
        else:
            C_txt = C_txt + self.outputAndName(outline,outline[line],2)+"){"
        
        C_txt = C_txt +str(outline[line][0])+"=1;}\n" 
        C_txt = C_txt +"             else {"
        C_txt = C_txt +str(outline[line][0])+"=0;} //comparison\n"
        return C_txt
    def addLessOrEq(self,outline, C_txt, line):
        if outline[line][1] == "Constant":
            C_txt = C_txt +"             if("+ str(outline[line][3]) +" <= "
        else:
            C_txt = C_txt +"             if("+self.outputAndName(outline,outline[line],1)+" <= "
        if outline[line][2] == "Constant":
            C_txt = C_txt + str(outline[line][4])+"){"
        else:
            C_txt = C_txt + self.outputAndName(outline,outline[line],2)+"){"
        
        C_txt = C_txt +str(outline[line][0])+"=1;}\n" 
        C_txt = C_txt +"             else {"
        C_txt = C_txt +str(outline[line][0])+"=0;} //comparison\n"
        return C_txt
        
    def addMath(self,outline, C_txt, line):
        if outline[line][1] == "Plus": Operator = "\'+\'"
        if outline[line][1] == "Minus": Operator = "\'-\'"
        if outline[line][1] == "Mult": Operator = "\'*\'"
        if outline[line][1] == "Divide": Operator = "\'/'"
        #if outline[line][1] == "Move": Operator ="\'=\'"
        print "operator",Operator
        C_txt = C_txt +"            if (W == 1){\n                 "+str(outline[line][0])+" = "
        if outline[line][2] == "Constant":
            C_txt = C_txt +" do_math("+str(outline[line][4])+","
        else:
            C_txt = C_txt +" do_math("+self.outputAndName(outline,outline[line],2)+"," #2
        if outline[line][3] == "Constant":
            C_txt = C_txt +str(outline[line][5])+","
        else:
            C_txt = C_txt +self.outputAndName(outline,outline[line],3)+"," #3
        C_txt = C_txt + Operator +");}\n"
        return C_txt
            
    def addPWM(self,outline, C_txt, line):
        #WAS if "pwm_" in outline[line][1]: #if "internal" then PWM disabled
        if outline[line][1][:4] == "pwm_" :
            pwmNum = (int (outline[line][1].split("pwm_")[1])) -1# this is the pwm #
            pwmVal = str(int(round    (( float(outline[line][2]) )*5))) #percent times 500
            C_txt = C_txt +"            if ((W == 1 )&& ("+outline[line][1]+" == 0)){"+self.PWMList[pwmNum][8]+"="+pwmVal+";"+ outline[line][1]+" = 1; }\n"
            C_txt = C_txt +"            if ((W == 0 )&& ("+outline[line][1]+" == 0)){"+self.PWMList[pwmNum][8]+"= 0;}\n"
        return C_txt
        
    def addADC(self,outline, C_txt, line):
        channel = str((int (outline[line][1].split("adc_")[1])) -1)# this is the adc# 
        
        C_txt = C_txt +"            if (W == 1){"
        C_txt = C_txt +"reg_"+outline[line][0]+"=read_adc("+channel+");}\n"
        C_txt = C_txt +"            else{reg_"+outline[line][0]+"=0;}\n"
        return C_txt
    
    ##030##
    def outputAndName(self,outline,thisLine,pos):
        #scan outline for name
        #determine if output (8 bit unsigned) or result (16 bit signed)
        outputName = None
        for i in range (len(outline)):                  #check for Results first
            #print "compare to", str(outline[i][0])
            if len(outline[i])>1 and  str(outline[i][0]) == "Result_"+str(thisLine[pos]):
                outputName = "Result_"+ str(thisLine[pos])
                return outputName
        for i in range (len(outline)):                  
            #print "compare to", str(outline[i][0])
            if len(outline[i])>1 and  str(outline[i][0]) == "Counter_"+str(thisLine[pos]):
                outputName = "reg_Counter_"+ str(thisLine[pos])
                return outputName
        for i in range (len(outline)):                  
            #print "compare to", str(outline[i][0])
            if len(outline[i])>1 and  str(outline[i][0]) == "Timer_"+str(thisLine[pos]):
                outputName = "reg_Timer_"+ str(thisLine[pos])
                return outputName
        for i in range (len(outline)):                  
            #print "compare to", str(outline[i][0])
            if len(outline[i])>1 and  str(outline[i][0]) == "ADC_"+str(thisLine[pos]):
                outputName = "reg_ADC_"+ str(thisLine[pos])
                return outputName
        for i in range (len(outline)):
            if len(outline[i])>1 and  str(outline[i][0]) == "output_"+str(thisLine[pos]):
                outputName = "output_"+ str(thisLine[pos])
                print "comparing to a binary output" 
        return outputName
        
    #go through grid and assign outputs to variables 
    def findOutPuts(self,outLine,C_txt):
        C_txt = C_txt +"           //outputs:\n"
        for i in range (len(outLine)):
            #WAS if len(outLine[i])>1 and "out_" in str(outLine[i][1]) :
            if len(outLine[i])>1 and  str(outLine[i][1])[:4] == "out_":    
                outNum = (int(outLine[i][1].split("out_")[1])) -1
                microString =  "         if("+str(outLine[i][0])+" == 0){"\
                                +str(self.outPutList[outNum][0])+" &=~ (1<<"+str(self.outPutList[outNum][1])\
                                +");}\n"
                C_txt = C_txt + microString
                C_txt = C_txt + "         else {"+str(self.outPutList[outNum][0])\
                                +" |= (1<<"+str(self.outPutList[outNum][1])+");}\n"
        C_txt = C_txt +"\n"
        return C_txt
    
    #set outputs on micro    
    def DDROutPuts(self,C_txt):
        for x in range(len(self.outPutList)):
            dirport = self.outPutList[x][0].strip("PORT")
            C_txt = C_txt + "   DDR"+dirport+\
                    " |= (1<<"+str(self.outPutList[x][1])+");\n"
        C_txt = C_txt +"\n"
        return C_txt
        
    def pullupInPuts(self,C_txt):
        for x in range(len(self.inPutList)):
            dirport = self.inPutList[x][0].strip("PIN")
            C_txt = C_txt + "   PORT"+dirport+\
                    " |= (1<<"+str(self.inPutList[x][1])+");\n"
        C_txt = C_txt +"\n"
        return C_txt
        
    ##029##
    def initVarsForMicro(self, outLine, C_txt):
            # look for cont_ and output_  These whole strings will be var names I_J
            #look for startBR and  branch: #these become branch_I_Jfor i in range (len(outLine)):
        pwmList = []
        for i in range (len(outLine)): 
            #WAS if "cont_" in str(outLine[i][0]) and "contNO" in str(outLine[i][1]) :
            if  str(outLine[i][0])[:5] == "cont_" and  str(outLine[i][1])[:6] == "contNO" :
                if "    uint8_t "+ str(outLine[i][0]) +"_NO = 0;\n" not in C_txt:
                    C_txt = C_txt + "    uint8_t "+ str(outLine[i][0]) +"_NO = 0;\n"
                    
            #WAS if "cont_" in str(outLine[i][0]) and "contNC" in str(outLine[i][1]) :
            if  str(outLine[i][0])[:5] == "cont_" and  str(outLine[i][1])[:6] == "contNC" :
                if "    uint8_t "+ str(outLine[i][0]) +"_NC = 1;\n" not in C_txt:
                    C_txt = C_txt + "    uint8_t "+ str(outLine[i][0]) +"_NC = 1;\n"

            #WAS if "output_" in str(outLine[i][0]):
            if  str(outLine[i][0])[:7] == "output_" :
                if "    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "    uint8_t "+ str(outLine[i][0]) +" = 0;\n"
                    
            #WAS if "Result_" in str(outLine[i][0]):
            if  str(outLine[i][0])[:7] == "Result_" :
                if "    int16_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "    int16_t "+ str(outLine[i][0]) +" = 0;\n"
            
            #WAS if "branch" in outLine[i] or "startBR" in outLine[i] :
            if  str(outLine[i][0])[:6] == "branch" or  str(outLine[i][0])[:7] == "startBR" :
                if "    uint8_t branch_"+str(outLine[i][1][0])+"_"+str(outLine[i][1][1])+ " = 0;\n" not in C_txt:
                    C_txt = C_txt + "    uint8_t branch_"+str(outLine[i][1][0])+"_"+str(outLine[i][1][1])+ " = 0;\n"                       
            # probably redundant, but just in case startBR was not listed explicity in outline:
            if str(outLine[i][0])[:5] == "node_":
                if  "    uint8_t branch_"+str(outLine[i][-1][0])+"_"+str(outLine[i][-1][1])+ " = 0;\n" not in C_txt:
                    C_txt = C_txt + "    uint8_t branch_"+str(outLine[i][-1][0])+"_"+str(outLine[i][-1][1])+ " = 0;\n"
            
            
            #WAS if "Equals_" in outLine[i][0] :
            if  outLine[i][0][:7] == "Equals_"  : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" #inits the element name
            #WAS if "Greater_" in outLine[i][0] : 
            if  outLine[i][0][:8] == "Greater_"  :
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" #inits the element name
            #WAS if "Lessthan_" in outLine[i][0] :
            if  outLine[i][0][:9] ==  "Lessthan_" : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" #inits the element name
            #WAS if "GreaterOrEq_" in outLine[i][0] :
            if  outLine[i][0][:12] == "GreaterOrEq_"  : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" #inits the element name
            #WAS if "LessOrEq_" in outLine[i][0] :
            if  outLine[i][0][:9] == "LessOrEq_"  : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" #inits the element name
           
            #WAS if "Counter_" in outLine[i][0] ==  :
            if outLine[i][0][:8]== "Counter_"  : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt and "rungstate_" not in outLine[i][0]:
                    
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint16_t setpoint_"+ str(outLine[i][0]) +" = "+outLine[i][2]+";\n"
                    C_txt = C_txt + "    uint16_t reg_"+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint8_t prev_rungstate_"+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint8_t rungstate_"+ str(outLine[i][0]) +" = 0;\n\n"
            
            if "ADC_" ==  outLine[i][0][:4] : 
                if "    uint16_t reg_"+ str(outLine[i][0]) +" = 0;\n" not in C_txt :
                    C_txt = C_txt + "    uint16_t reg_"+ str(outLine[i][0]) +" = 0;\n"
            
            if "PWM_" == str(outLine[i][0])[:4] and outLine[i][1] not in pwmList:
                if "    uint8_t " + str(outLine[i][1]) +" = 0;\n" not in C_txt:
                    C_txt = C_txt + "    uint8_t " + str(outLine[i][1]) +" = 0;\n"
                    pwmList.append(outLine[i][1])

            #WAS if "Timer_" in outLine[i][0] :
            if  outLine[i][0][:6] == "Timer_" : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt and "rungstate_" not in outLine[i][0]:
                    
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint16_t setpoint_"+ str(outLine[i][0]) +" = "+outLine[i][2]+";\n"
                    C_txt = C_txt + "    uint16_t reg_"+ str(outLine[i][0]) +" = 0;\n\n"
                    C_txt = C_txt + "    uint8_t prev_rungstate_"+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint8_t rungstate_"+ str(outLine[i][0]) +" = 0;\n\n"
                    C_txt = C_txt + "    uint8_t run_"+ str(outLine[i][0]) +" = 0;\n\n"
            #WAS if "Fall_" in outLine[i][0] :
            if  outLine[i][0][:5] ==  "Fall_" : 
                if "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n" not in C_txt and "rungstate_" not in outLine[i][0]:
                    C_txt = C_txt + "\n    uint8_t "+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint8_t prev_rungstate_"+ str(outLine[i][0]) +" = 0;\n"
                    C_txt = C_txt + "    uint8_t rungstate_"+ str(outLine[i][0]) +" = 0;\n\n"
            
            
            #add timer, counter and falling vaiables needed here. 
       
        return C_txt
        
    def setUpPWMs(self, outLine, C_txt):
        pwmList = []
        for i in range (len(outLine)):
            if "PWM_" == str(outLine[i][0])[:4] and outLine[i][1] not in pwmList and outLine[i][1] != "Internal":
                pwmNum = (int(outLine[i][1].split("pwm_")[1])) -1# this is the pwm #
                C_txt = C_txt + "\n   //setup timer for PWM  "+ str(pwmNum+1)+"\n"
                C_txt = C_txt + "    "+self.PWMList[pwmNum][0]+ " |= (1<<"+self.PWMList[pwmNum][1]+");\n"
                C_txt = C_txt + "    "+self.PWMList[pwmNum][2]+ " |= (1<<"+self.PWMList[pwmNum][4]+");\n"
                C_txt = C_txt + "    "+self.PWMList[pwmNum][5]+ " |= ((1<<"+self.PWMList[pwmNum][6]+")|(1<<"+self.PWMList[pwmNum][7]+"));\n"
                C_txt = C_txt + "    "+self.PWMList[pwmNum][8]+ " = 0 ;\n" 
                C_txt = C_txt + "    "+self.PWMList[pwmNum][9]+ " = 500 ;\n\n"#top value for 16khz freq 
                pwmList.append(outLine[i][1])
        return C_txt

                    
         

 
