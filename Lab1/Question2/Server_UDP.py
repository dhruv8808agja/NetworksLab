import socket
import datetime

s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)

s.bind(('', 8080))

#s.listen(5)

i = 0
while i < 4:
	message, addr = s.recvfrom(100)
	print addr, message
	s.sendto(str(datetime.datetime.now()), addr)
	i += 1
