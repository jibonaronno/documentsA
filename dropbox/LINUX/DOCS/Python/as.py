__author__ = 'aronno'

#BASIC DESCRIPTION: There are 2 basic class for network message transactions. The master class is asyncore.dispatcher.
#I inheritance it and name it Server class. The server class has a dictionary member named echos. My plan is to save
#each connected socket in this dictionary with names as keys.
#       I declared a class named EchoHandler inherited from asyncore.dispatcher_with_send . This class represents each
# Socket connection. Whenever my Server class accepts a request, It creates a EchoHandler class instance with socket
# and itself too. So that each EchoHandler can call Server functions. Initially when Server creates an EchoHandler,
# it does not store it into the dictionary. When a specific format of message came from a connected client that contains
# a register request, then that Socket will be added to Server.echos[] dictionary with the requested name from client
# as a key.

import asyncore, socket
import threading
import inspect
import os
import shelve

class Server(asyncore.dispatcher):
    def __init__(self, host, port):
        asyncore.dispatcher.__init__(self)
        self.create_socket(socket.AF_INET, socket.SOCK_STREAM)
        self.bind(('', port))
        self.listen(1)

        self.echos = dict()

    def handle_accept(self):
        # when we get a client connection start a dispatcher for that
        # client
        sock, address = self.accept()
        print 'Connection by', address
        #self.echos[address] = EchoHandler(sock, self)
        EchoHandler(sock, self)

    def reg_basic(self, echo, name):
        self.echos[name] = echo
        print '\nReg:'+ name+ '\n'

    def handle_close(self):
        print  'closing...'
        self.close()

    def handle_error(self):
        pass

    def send_msg_basic(self, name, msg):
        print '\n NAME:' + name + '\n'
        print self.echos.keys()
        for key in self.echos.keys():
            if(key == name):
                self.echos[key].out_buffer = '\n'+ msg+'\n'
               # self.echos[key].out_buffer = 'your message'
                print 'KEY:'+ key + '\n'

class EchoHandler(asyncore.dispatcher_with_send):

    def __init__(self, sock, parent):
        asyncore.dispatcher_with_send.__init__(self, sock)
        self.parent = parent
        self.strdata = ""

#filter text coming from CLIENTS by removing '\n' and '\r'.
    def filter_text(self, txt):
        if(len(txt)>0):
            tt = [char for char in txt[::1] if char != '\n' and char != '\r']
            return ''.join(tt)
        else:
            return ''

    # dispatcher_with_send extends the basic dispatcher to have an output
    # buffer that it writes whenever there's content
    def handle_read(self):
        data = self.recv(1024)
        print str(data)
        self.strdata = self.filter_text(str(data))
        #print self.filter_text(self.strdata)
        #self.out_buffer = data
        #if not self.out_buffer:
            #self.close()
        strcommands = self.strdata.split(',')
        if(len(strcommands) == 3):
            if(strcommands[0] == 'sendmsg'):
                self.parent.send_msg_basic(strcommands[1], strcommands[2])
        elif(len(strcommands)==2):
                if(strcommands[0] == 'reg'):
                    self.parent.reg_basic(self, strcommands[1])
                    #print '\nReg:' strcommands[1] '\n'

    def varify_and_depart_commands(self, str_commands):
        if(str_commands != None):
            if(str_commands[0] == 'reg'):
                if(len(str_commands) == 2):
                    self.parent.reg_basic(self, str_commands[1])
                else: print 'Parameter Count Mismatch.\n'
            elif(str_commands[0] == 'sendmsg'):
                if(len(str_commands)==3):
                    self.parent.send_msg_basic(str_commands[1], str_commands[2])
                else: print 'Parameter Count Mismatch.\n'
            else:
                print 'Command Mismatch.\n'


    def query_device_id(self):
        self.out_buffer = '[1021]' #get id

#user will want to send a command to a device client. first of all store the user command to a table including the device id.
#if the device recieved the command and executes the device will feed back with success/error message. then this program will
#store the success/error message on the same record. getting complex... need to do some homework.
class LocalStorage(object):
    def __init__(self, filename):
        self.filename = filename

    def store_incoming_data_by_cid(self, cid, data):
        pass

    def store_site_states(self, region, zone, area, rbs):
        pass


def asyncore_loop():
    try:
        asyncore.loop()

    except asyncore.errorcode, msg:
        print msg[0]

s = Server('', 8888)

local_process = threading.Thread(target=asyncore_loop)

#print 'Location : ' + inspect.stack()[0][1]

local_path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
print local_path + "\\data_log.db"

data_log = shelve.open(filename=local_path+"\\data_log.db", writeback=True)
#data_log['1'] = {'temp':'33', 'volt':'215', 'current':'12'}
#print data_log['1']['volt']
data_log.close()

try:

    raw_input('press enter to start..')
    print 'starting ...'
    local_process.start()

    raw_input('press enter to stop...')
    asyncore.close_all()


finally:
    print 'done ...'

