import socket 
import select 
import sys 
from thread import *

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server.bind(('127.0.0.1', 8090))

def clientthread(addr, z): 
    server.sendto("Welcome to this chatroom!", addr)
    while True:
        message, add = server.recvfrom(2048)
        if message:
            print "<" + add[0] + ":" + str(add[1]) + "> " + message
            message_to_send = "<" + add[0] + ":" + str(add[1]) + "> " + message
            broadcast(message_to_send, add)
        else:
            remove(addr)

def broadcast(message, addr):
    for add in addresses:
        if add != addr:
            try:
                server.sendto(message, add)
            except:
                remove(add)

def remove(add):
    if add in addresses:
        addresses.remove(add)


addresses = []
  
while True:
    message, addr = server.recvfrom(1024)
    if addr not in addresses:
        addresses.append(addr)
        print addr[0] + ":" + str(addr[1]) + " connected"
        start_new_thread(clientthread,(addr, 1))
server.close()
