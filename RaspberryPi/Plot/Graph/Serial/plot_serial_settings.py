# Library imports

import os
import sys

# Constants

NUMBER_OF_VARIABLES = 5

THROTTLE_BOUNDS = [0, 100]
BRAKE_BOUNDS = [0, 100]
VEHICLE_SPEED_BOUNDS = [0, 200]
ENGINE_SPEED_BOUNDS = [0, 6000]
GEAR_BOUNDS = [1, 4]

# Plot

PLOT_SIZE = (6, 7)
X_RANGE = 20

# CSV

BASE_PATH = os.path.dirname(os.path.realpath(__file__))
ROOT_PATH = os.path.realpath(os.path.join(BASE_PATH, '../..'))
sys.path.append(ROOT_PATH)

CSV_FILE_PATH = os.path.join(ROOT_PATH, "Data", "tractor_data.csv")

# Serial

SERIAL_PORT = "COM6"            # Windows
#SERIAL_PORT = "/dev/ttyS0"     # Raspberry Pi OS (Based on Debian)
BAUDRATE = 115200