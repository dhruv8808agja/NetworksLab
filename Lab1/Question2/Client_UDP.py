import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

addr = ('127.0.0.1', 8080)

s.sendto('Request for date', addr)

print(s.recvfrom(100))

s.close()
