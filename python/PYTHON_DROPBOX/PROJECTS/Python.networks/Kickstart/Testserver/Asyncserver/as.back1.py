__author__ = 'aronno'
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
        else:
            if(len(strcommands)==2):
                if(strcommands[0] == 'reg'):
                    self.parent.reg_basic(self, strcommands[1])
                    #print '\nReg:' strcommands[1] '\n'

    def query_device_id(self):
        self.out_buffer = '[1021]' #get id

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
#GET THE LOCATION OF THIS APPLICATION.
local_path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
print local_path + "\\data_log.db"

data_log = shelve.open(filename=local_path+"\\data_log.db", writeback=True)
#data_log['1'] = {'temp':'33', 'volt':'215', 'current':'12'}
#print data_log['1']['volt']
data_log.close()

try:

    raw_input('pree enter to start..')
    print 'starting ...'
    local_process.start()

    raw_input('press enter to stop...')
    asyncore.close_all()


finally:
    print 'done ...'

