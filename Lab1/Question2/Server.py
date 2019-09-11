import socket
import datetime

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('', 8080))

s.listen(5)

i = 0
while i < 4:
	c, addr = s.accept()
	print addr
	print c.recv(100)
	c.send(str(datetime.datetime.now()))
	c.close()
	i += 1
s.close()
