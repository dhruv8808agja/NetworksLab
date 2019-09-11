import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

addr = ('127.0.0.1', 8080)

t = 0
while t < 5:
	t = t + 1
	inp = raw_input("Enter your message: ")
	s.sendto(str(inp), addr)
	print s.recvfrom(100)
