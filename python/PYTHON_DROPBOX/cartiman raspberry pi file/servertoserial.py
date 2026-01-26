import socket
import serial
import time
import sys


#TCP Setting      
TCP_IP = ''
TCP_PORT = 5000
BUFFER_SIZE = 1024
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
        s.bind((TCP_IP, TCP_PORT))
except socket.error , m:
        print 'ERROR! Bind : code ' + str(m[0]) + ' Message ' + m[1]
        sys.exit()        

#Serial Port 9600,8,E,1
try:
        ser = serial.Serial(
                port = '/dev/ttyAMA0',
                baudrate = 9600,
                bytesize = serial.EIGHTBITS,
                parity = serial.PARITY_EVEN,
                stopbits = serial.STOPBITS_ONE,
                timeout = 0
        )
except Exception, e:
        print "ERROR! Serial Port: " + str(e)
        sys.exit()
        
#PLC Command      
def commandonoff(Qx,Qy,Qv):
        str_write=[0 for i in range(38)]       
        str_write[0] = 0x68
        str_write[1] = 0x20
        str_write[2] = 0x20
        str_write[3] = 0x68
        str_write[4] = 0x02
        str_write[5] = 0x00
        str_write[6] = 0x7C
        str_write[7] = 0x32
        str_write[8] = 0x01
        str_write[9] = 0x00
        str_write[10] = 0x00
        str_write[11] = 0x43
        str_write[12] = 0x01
        str_write[13] = 0x00
        str_write[14] = 0x0E
        str_write[15] = 0x00
        str_write[16] = 0x05
        str_write[17] = 0x05
        str_write[18] = 0x01
        str_write[19] = 0x12
        str_write[20] = 0x0A
        str_write[21] = 0x10
        str_write[22] = 0x01 
        str_write[23] = 0x00
        str_write[24] = 0x01
        str_write[25] = 0x00
        str_write[26] = 0x00  
        str_write[27] = 0x82
        str_write[28] = 0x00
        str_write[29] = 0x00
        str_write[30] = Qx * 8 + Qy
        str_write[31] = 0x00
        str_write[32] = 0x03

        str_write[33] = 0x00
        str_write[34] = 0x01
        str_write[35] = Qv
        Temp_FCS = 0
        for i in range(4,36):
            Temp_FCS = Temp_FCS + str_write[i]
            
        str_write[36] = Temp_FCS % 256
        str_write[37] = 0x16
        if ser.isOpen:
                ser.write("".join(chr(h) for h in str_write))
                time.sleep(0.1)
                ser.write("\x10\x02\x00\x5C\x5E\x16")
                time.sleep(0.1)

while 1:
        s.listen(1)
        conn, addr = s.accept()
        print 'Client IP :', addr
        while 1:
                data = conn.recv(BUFFER_SIZE)
                if not data:
                        conn.close()
                        break

                if "ON" in data:
                        try:
                                numon=int(data[2:])
                                if numon >=0 and numon <=7:
                                        commandonoff(0,numon,1)
                                elif numon >=8 and numon <=15:
                                        y = numon % 8
                                        commandonoff(1,y,1)
                        except ValueError:
                                print 'ERROR! Lamp Number'

                elif "OFF" in data :
                        try:
                                numoff=int(data[3:])
                                if numoff >=0 and numoff <=7:
                                        commandonoff(0,numoff,0)
                                if numoff >=8 and numoff <=15:
                                        y = numoff % 8
                                        commandonoff(1,y,0)
                        except ValueError:
                                print 'ERROR! Lamp Number'
