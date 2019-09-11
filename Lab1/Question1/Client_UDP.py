import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

addr = ('127.0.0.1', 1024)

s.sendto('Trying to connect', addr)

print(s.recvfrom(100))

s.close()
