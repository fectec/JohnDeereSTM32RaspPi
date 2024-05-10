# Library imports

import serial

# Code imports

from plot_settings import SERIAL_PORT
from plot_settings import BAUDRATE

try:
    # Open the serial port
    
    ser = serial.Serial(SERIAL_PORT, BAUDRATE)
    print("Serial port opened successfully.")

    # Read data from the serial port and print it to the console
    
    while True:
        if ser.in_waiting > 0:

            # Read a line of data from the serial port

            data = ser.readline().decode().strip()
            print("Received data:", data)

except serial.SerialException as e:
    print("Error:", e)

finally:
    
    # Close the serial port
    
    ser.close()
    print("Serial port closed.")