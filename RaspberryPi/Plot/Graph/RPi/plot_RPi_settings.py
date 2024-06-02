# Library imports

import os
import sys

# Code imports

BASE_PATH = os.path.dirname(os.path.realpath(__file__))
SERIAL_PLOT_PATH = os.path.realpath(os.path.join(BASE_PATH, '..', "Serial"))

sys.path.append(SERIAL_PLOT_PATH)