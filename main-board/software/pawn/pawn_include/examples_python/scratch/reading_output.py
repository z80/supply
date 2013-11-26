# -*- coding: utf-8 -*-
"""
Created on Tue Nov 26 15:12:04 2013

@author: z_80
"""

#Socket client example in python
 
import socket   #for sockets
import sys  #for exit
 
#create an INET, STREAMing socket
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error:
    print 'Failed to create socket'
    sys.exit()
     
print 'Socket Created'
 
host = 'localhost';
port = 42001;
 
try:
    remote_ip = socket.gethostbyname( host )
 
except socket.gaierror:
    #could not resolve
    print 'Hostname could not be resolved. Exiting'
    sys.exit()
 
print "ip: ", remote_ip
#Connect to remote server
s.connect( (remote_ip, port) )
 
print 'Socket Connected to ' + host + ' on ip ' + remote_ip
 
#Send some data to remote server
#message = "GET / HTTP/1.1\r\n\r\n"
 
#try :
    #Set the whole string
    #s.sendall(message)
#    pass
#except socket.error:
    #Send failed
#    print 'Send failed'
#    sys.exit()
 
#print 'Message send successfully'

print "Listening..."
i = 0
while True:
    #Now receive data
    reply = s.recv(4096)
    print reply
    
    #s.send( 'sensor-update "kkk" {0}\r\n'.format( i ) )
    i += 1
    
    print "####################################################################"
    print ""
    print ""
    print ""
    

