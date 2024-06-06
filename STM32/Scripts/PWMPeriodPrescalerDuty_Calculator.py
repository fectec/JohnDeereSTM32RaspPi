# Script for calculating PSC, ARR and CCRX values for the desired PWM period and duty cycle

# Library imports

import math

FOSC = 64e6     # 64 MHz board frequency
TOSC = 1 / FOSC
ARR = 65535

TPWM = float(input())
DUTY_CYCLE_PERIOD = float(input())

DUTY_CYCLE_RATIO = DUTY_CYCLE_PERIOD / TPWM

PSC = math.ceil(TPWM / (TOSC * (ARR + 1))) - 1
ARR = round(TPWM / (TOSC * (PSC + 1)) - 1)
CCRX = round(DUTY_CYCLE_RATIO * ARR)

print("PSC: " + str(PSC) + "\nARR: " + str(ARR) + "\nCCRx: " + str(CCRX))