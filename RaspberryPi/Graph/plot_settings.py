# Library imports

import os

# Constants

NUMBER_OF_VARIABLES = 4

THROTTLE_BOUNDS = [0, 100]
ENGINE_SPEED_BOUNDS = [0, 6000]
VEHICLE_SPEED_BOUNDS = [0, 200]
GEAR_BOUNDS = [1, 4]

# Plot

PLOT_SIZE = (6, 7)
X_RANGE = 20

# CSV

BASE_PATH = os.path.dirname(os.path.realpath( __file__ ))
CSV_FILE_PATH = os.path.join(BASE_PATH, "data", "tractor_data.csv")

# Serial

SERIAL_PORT = "COM6"            # Windows
#SERIAL_PORT = "/dev/ttyS0"     # Raspberry Pi OS (Based on Debian)
BAUDRATE = 115200