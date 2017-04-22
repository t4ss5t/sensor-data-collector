#!/usr/bin/python
# whereIsArduino.py
# origin: http://www.raspberry-pi-geek.de/Magazin/2013/05/Raspberry-Pi-und-Arduino-Uno-verbinden/%28offset%29/2
import serial
for com in range(0,4):
  try:
    PORT = '/dev/ttyACM'+str(com)
    BAUD = 9600
    board = serial.Serial(PORT,BAUD)
    print 'Arduino erkannt an /dev/ttyACM'+str(com)
    print 'Hardware: %s' % board.__str__()
    board.close()
    break
  except:
    print 'Kein Arduino an /dev/ttyACM'+str(com)
