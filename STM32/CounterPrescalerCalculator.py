# Script for calculating CNT and PSC values for the desired time delay

# Library imports

import math

FOSC = 64e6     # 64 MHz board frequency
TOSC = 1 / FOSC
ARR = 65535

TIME = float(input())

PSC = math.ceil((TIME / (TOSC * (ARR + 1)))) - 1
CNT = round((ARR + 1) - (TIME / (TOSC * (PSC + 1))))

print("PSC: " + hex(PSC).upper() + "\nCNT: " + hex(CNT).upper())