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

    def handle_accept(self):
        # when we get a client connection start a dispatcher for that
        # client
        sock, address = self.accept()
        print 'Connection by', address
        EchoHandler(sock)

    def handle_close(self):
        print  'closing...'
        self.close()

    def handle_error(self):
        pass

class EchoHandler(asyncore.dispatcher_with_send):
    # dispatcher_with_send extends the basic dispatcher to have an output
    # buffer that it writes whenever there's content
    def handle_read(self):
        data = self.recv(1024)
        print str(data)
        self.out_buffer = data
        if not self.out_buffer:
            self.close()

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

local_path = os.path.dirname(os.path.abspath(inspect.getfile(inspect.currentframe())))
print local_path + "\\data_log.db"

data_log = shelve.open(filename=local_path+"\\data_log.db", writeback=True)
#data_log['1'] = {'temp':'33', 'volt':'215', 'current':'12'} #Writing data to file.
print data_log['1']['volt']
data_log.close()

try:

    raw_input('pree enter to start..')
    print 'starting ...'
    local_process.start()

    raw_input('press enter to stop...')
    asyncore.close_all()


finally:
    print 'done ...'

