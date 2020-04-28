import sys, serial
import numpy as np
from time import sleep
from collections import deque
from matplotlib import pyplot as plt
import re

strPort = sys.argv[1];
#file=sys.argv[2];


ser = serial.Serial(strPort, 115200) # 
#f=open(file1,"w+")

j=0
  
dt=10
Troom_c=20
K1=1
K2=0.001
H=Heat_Capasity=420
Q=H*(Troom_c+273)
Tc=Troom_c

while True:
  line = ser.readline()
  Tc = [float(val) for val in line.split()]
  print(Tc)
#  j=j+1
#  t= j*dt
  
  Win=100 
#  Wout=K1*Stephan(Tc)+K2*(Tc-Troom_c)  
#  Q +=(Win - Wout)*dt
#  Tc=Q/H-273
  a = Win.to_bytes(1, byteorder="little")
  ser.write(a)
  sleep(1)

	
#  x_list.append(x)
#  t_list.append(t)
