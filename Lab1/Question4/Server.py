import socket 
import select 
import sys 
from thread import *

def clientthread(conn, addr): 
    conn.send("Welcome to this chatroom!")
    while True:
        message = conn.recv(2048)
        if message:
            print "<" + addr[0] + ":" + str(addr[1]) + "> " + message
            message_to_send = "<" + addr[0] + ":" + str(addr[1]) + "> " + message
            broadcast(message_to_send, conn)
        else:
            remove(conn)

def broadcast(message, connection):
    for client in list_of_clients:
        if client != connection:
            try:
                client.send(message)
            except:
                client.close()
                remove(client)

def remove(connection):
    if connection in list_of_clients:
        list_of_clients.remove(connection)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(('127.0.0.1', 8090))

server.listen(100)
list_of_clients = []
  
while True: 
    conn, addr = server.accept()
    list_of_clients.append(conn)
    print addr[0] + ":" + str(addr[1]) + " connected"

    start_new_thread(clientthread,(conn,addr))
conn.close() 
server.close()