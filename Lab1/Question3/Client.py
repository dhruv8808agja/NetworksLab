import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(('127.0.0.1', 8080))

t = 0
while t < 5:
	t = t + 1
	inp = raw_input("Enter your message: ")
	s.send(str(inp))
	print s.recv(100)
