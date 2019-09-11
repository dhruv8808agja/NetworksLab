import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s.bind(('', 8080))

while(True):
	message, addr = s.recvfrom(100)
	#print "Connected to ", addr
	print "Recieved message from ", addr, ": ", message
	inp = raw_input("Enter your message to be sent: ")
	#print inp
	s.sendto(str(inp), addr)
