import socket
import sys
import select

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.connect(('127.0.0.1', 8090))

while True:
    sockets_list, a, b = select.select([sys.stdin, server], [], [])    
    for s in sockets_list:
    	if s == server:
            message = server.recv(2048)
            print message
        else:
            message = raw_input()
            print "<You>" , message
            server.send(message)
server.close()