# Script for testing serial connection

# Library imports

import serial

# Code imports

from Graph.Serial.plot_serial_settings import SERIAL_PORT, BAUDRATE

try:
    
    try:

        # Open the serial port
        
        ser = serial.Serial(SERIAL_PORT, BAUDRATE)
        print("Serial port opened successfully.")

    except:

        print("Error opening the serial port.")

    # Read data from the serial port and print it to the console
    
    while True:

        if ser.in_waiting > 0:

            try:
                
                # Read a line of data from the serial port

                data = ser.readline().decode().strip()
                print("Received data:", data)

            except UnicodeDecodeError as e:

                print("Error decoding data:", e)

except:

    print("Error reading data from the serial port.")

finally:
    
    # Close the serial port

    try:

        if ser.is_open:

            ser.close()
            print("Serial port closed.")

    except:

        print("Error closing the serial port.")