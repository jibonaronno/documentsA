
import socket

s = socket.socket()

host = socket.gethostname()

port = 12345;

s.bind((host, port))

print("Listening for connection")

s.listen(5)

c, addr = s.accept()
print("got connection from %d", addr)

while True:
    data = c.recv(1024)
    if not data: break
    c.send(data)
c.close()
