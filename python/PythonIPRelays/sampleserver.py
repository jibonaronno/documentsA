import select, socket, sys, queue


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.setblocking(0)
server.bind(('10.222.188.27', 80))
server.listen(1)
inputs = [server]
outputs = []
message_queues = {}

point_break = False

txtdata = ''

txt1 = ''
txt2 = '0'

bit0 = 0
bit1 = 0
bit2 = 0
bit3 = 0
bit4 = 0
bit5 = 0

def commandProcess(txtcommand):
    idx01 = -1
    txtcmd = ''
    addv = 0

    global bit0
    global bit1
    global bit2
    global bit3
    global bit4
    global bit5
    global txt2

    if 'command' in txtcommand:
        if 'godin' in txtcommand:
            txt2 = '55'
        else:
            idx01 = txtcommand.index('command')
            txtcmd = txtcommand[idx01+10:idx01+12]
            txt2 = '0'
            print(txtcmd+'\r\n')
            if 'a1' in txtcmd:
                bit0 = 1
            elif 'a0' in txtcmd:
                bit0 = 0
            if 'b1' in txtcmd:
                bit1 = 1
            elif 'b0' in txtcmd:
                bit1 = 0
            if 'c1' in txtcmd:
                bit2 = 1
            elif 'c0' in txtcmd:
                bit2 = 0
            if 'd1' in txtcmd:
                bit3 = 1
            elif 'd0' in txtcmd:
                bit3 = 0
            if 'e1' in txtcmd:
                bit4 = 1
            elif 'e0' in txtcmd:
                bit4 = 0
            if 'f1' in txtcmd:
                bit5 = 1
            elif 'f0' in txtcmd:
                bit5 = 0
    else:
        txt2 = '0'    
    addv = ((bit0 * 1) + (bit1 * 2) + (bit2 * 4) + (bit3 * 8) + (bit4 * 16) + (bit5 * 32))
    return addv

btnval = 0

while True:
    while inputs:
        readable, writable, exceptional = select.select(
            inputs, outputs, inputs)
        for s in readable:
            if s is server:
                connection, client_address = s.accept()
                connection.setblocking(0)
                inputs.append(connection)
                message_queues[connection] = queue.Queue()
            else:
                data = s.recv(1024)
                if data:
                    print(data)
                    print('\r\n')
                    btnval = commandProcess(data.decode('utf-8'))
                    txtdata = 'HTTP/1.0 200 OK\r\nContent-Type:text/html\r\nMassiveLicense:1648\r\nConnection:close\r\n\r\n10,222,188,27:'+txt2+',11,'+str(btnval)+',33,488'
                    message_queues[s].put(bytes(txtdata, 'utf-8'))
                    if s not in outputs:
                        outputs.append(s)
                else:
                    print('Closing\r\n')
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    s.close()
                    del message_queues[s]

        for s in writable:
            try:
                next_msg = message_queues[s].get_nowait()
            except queue.Empty:
                outputs.remove(s)
            else:
                s.send(next_msg)
                print('------>')
                print(next_msg)
                print('<------\r\n')
                s.close()
                inputs.clear()
                outputs.clear()
                del message_queues
                #receiver_socket.bind(receiver_address)
                server.listen(1)
                inputs = [ server ]
                outputs = []
                message_queues = {}
                point_break = True
        if point_break:
            point_break = False
            break

        for s in exceptional:
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()
            del message_queues[s]
