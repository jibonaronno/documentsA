import socket


s = socket.socket()
host = socket.gethostname()
port = 12345

s.connect((host, port))
s.send(b'Arigato godaimas')
data = s.recv(1024)
s.close()

print('Receved', repr(data))

