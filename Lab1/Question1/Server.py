import socket

try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	print("Socket created!!")
except socket.error as e:
	print(e)
port = 1024
s.bind(('', port))
print("Socket binded to port", port)

s.listen(2)
st = "Greetings from test server!!"
while True:
	c, addr = s.accept()
	print(addr, c)
	c.send(st)
	c.close()

#print(socket.gethostbyname('www.nitk.ac.in'))
