import socket

s = socket.socket()

s.connect(('127.0.0.1', 8080))

s.send("Please send date")

print("Date is", s.recv(100))

s.close()
