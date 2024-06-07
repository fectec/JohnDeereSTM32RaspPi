# Library imports

import os, sys

# Code imports

BASE_PATH = os.path.dirname(os.path.realpath(__file__))
PLOT_SERIAL_PATH = os.path.realpath(os.path.join(BASE_PATH, '..', "Serial"))

sys.path.append(PLOT_SERIAL_PATH)