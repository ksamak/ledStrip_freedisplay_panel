#!/usr/bin/env python

import serial
import time
import argparse
import sys

port = "/dev/ttyACM0"
ser = serial.Serial(port, 9600)

time.sleep(3)

value = " " + sys.argv[1] + " "
if len(value) > 126: # microcontroller limit
	print "length of string too long"
	sys.exit(1)
#value = " abcdefghijklmnopqrstuvwxyz-abcdefghijklmnopqrstuvwxyz "
typee = 1
length = len(value)
print "len ",length

ser.write(chr(typee))
ser.write(chr(length))

ser.write(value)

#for i in range(len(value)/20):
#	ser.write(value[20*i:20*i+20])
#	print value[20*i:20*i+20]
#	time.sleep(0.002)

while 1:
	print ser.read(),
