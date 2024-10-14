import select
import socket
import sys
import queue

#Create receiving socket
receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
receiver_socket.setblocking(0)

#Bind receiver_socket socket to the port.
receiver_address = ('10.222.188.27', 80) #localhost address is 127.0.0.1 by default
print('starting on',receiver_address[0], ' port ', receiver_address[1])
receiver_socket.bind(receiver_address)
receiver_socket.listen(2)
inputs = [ receiver_socket ]
outputs = []
#msgs = {}
txtdata = ''

target_address = ('10.222.188.28', 80)
target_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

target_sent = False

msgs = {}

while True:
    point_break = False
    while inputs:
        #print('\nwaiting for next event')
        readable, writable, exceptional = select.select(inputs, outputs, inputs)

        for s in readable:
            if s is receiver_socket:
                connection, client_address = s.accept()
                connection.setblocking(0)
                inputs.append(connection)
                print('Connected From:%s' % (client_address[0]))
                #Give the connection a queue for data we want to send
                msgs[connection] = queue.Queue()
                try:
                    target_socket.connect(target_address)
                except:
                    print('Cannot connect to target')
                finally:
                    outputs.append(target_socket)
                    outputs.append(connection)
                    inputs.append(target_socket)
                    msgs[target_socket] = queue.Queue()
            else:
                data = s.recv(1024)
                if data:
                    
                    #print("\nFrom:%s:%s" % (s.getpeername()[0], data.decode('utf-8')))
                    print("\nFrom:%s:%s" % (s.getpeername()[0], data.decode('utf-8')))
                    if s is not target_socket:
                        if b'27' in data:
                            txtdata = data.decode('utf-8')
                            idx = txtdata.index('27')
                            txtdata = txtdata[:idx] + '28' + txtdata[idx+2:]
                            msgs[target_socket].put(bytes(txtdata, 'utf-8'))
                    else:
                        if b'28' in data:
                            txtdata = data.decode('utf-8')
                            idx = txtdata.index('28')
                            txtdata = txtdata[:idx] + '27' + txtdata[idx+2:]
                            msgs[inputs[1]].put(bytes(txtdata, 'utf-8'))
                            target_sent = True
                    #if s is inputs[0]:
                        #outputs.append(s)
                else:
                    print('Closing:', client_address, '\n')
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    #inputs.remove(target_socket)
                    #outputs.remove(target_socket)
                    inputs.clear()
                    outputs.clear()
                    s.close()
                    target_socket.close()
                    del msgs
                    point_break = True
        if point_break:
            point_break = False
            
            #receiver_socket.bind(receiver_address)
            receiver_socket.listen(2)
            inputs = [ receiver_socket ]
            outputs = []

            #target_address = ('127.0.0.1', 8080)
            target_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            msgs = {}
            break
        for s in writable:
            try:
                #if s is inputs[0]:
                #    print('Receiver\n')
                #elif s is inputs[1]:
                #    print('conn\n')
                #else:
                #    print('target')
                next_msg = msgs[s].get_nowait()
            except queue.Empty:
                pass
            else:
                s.send(next_msg)
                txtdata = next_msg
                print('------>')
                print(txtdata)
                print('<------\r\n')
                if target_sent:
                    point_break = True
        if point_break:
                point_break = False
                target_sent = False
                
                target_socket.close()
                inputs[1].close()
                
                inputs.clear()
                outputs.clear()
                
                del msgs
                #receiver_socket.bind(receiver_address)
                receiver_socket.listen(2)
                inputs = [ receiver_socket ]
                outputs = []

                #target_address = ('127.0.0.1', 8080)
                target_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                msgs = {}
                break
        for s in exceptional:
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()
            del msgs[s]
