# Script for testing serial connection

# Library imports

import serial

# Code imports

from Graph.Serial.plot_serial_settings import SERIAL_PORT, BAUDRATE

try:
    
    # Open the serial port
    
    ser = serial.Serial(SERIAL_PORT, BAUDRATE)
    print("Serial port opened successfully.")

    # Read data from the serial port and print it to the console
    
    while True:

        if ser.in_waiting > 0:

            try:
                
                # Read a line of data from the serial port

                data = ser.readline().decode().strip()
                print("Received data:", data)

            except UnicodeDecodeError as e:

                print("Error decoding data:", e)

except serial.SerialException as e:

    print("Error:", e)

finally:
    
    # Close the serial port

    if ser.is_open:

        ser.close()
        print("Serial port closed.")