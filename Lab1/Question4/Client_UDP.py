import socket
import sys
import select

c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s_addr = ('127.0.0.1', 8090)
c.sendto("Hell0", s_addr)
while True:
    sockets_list, a, b = select.select([sys.stdin, c], [], [])
    for s in sockets_list:
    	if s == c:
            message, addr = c.recvfrom(2048)
            print message
        else:
            message = raw_input()
            print "<You>" , message
            c.sendto(message, s_addr)
server.close()