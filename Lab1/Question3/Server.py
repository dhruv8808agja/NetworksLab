import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('', 8080))

s.listen(5)

while(True):
	c, addr = s.accept()
	print "Connected to ", addr
	t = 5
	while(t > 0):
		t = t - 1
		print c.recv(100)
		inp = raw_input("Enter your message to be sent: ")
		# print inp
		c.send(str(inp))
	c.close()
