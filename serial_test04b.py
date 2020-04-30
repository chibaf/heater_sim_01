import serial
import time
import sys

val = 0
strPort = sys.argv[1];
ser = serial.Serial(strPort, 115200)
time.sleep(2)
while 1:
  val = input()	
  if val=='a':
    break;
  a = int(val).to_bytes(1, byteorder="little")
  ser.write(a)
  print(a)
  line = ser.readline()
  Tc = [float(val) for val in line.split()]
  print(Tc[0])
#  line=ser.readline()
#  print(line)
ser.close()