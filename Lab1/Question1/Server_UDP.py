import socket

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	print("Socket created!!")
except socket.error as e:
	print(e)
port = 1024
s.bind(('', port))
print("Socket binded to port", port)

while True:
	message, addr = s.recvfrom(100)
	print addr, message
	s.sendto('Greetings from test server!!', addr)
	#s.close()


#print(socket.gethostbyname('www.nitk.ac.in'))
