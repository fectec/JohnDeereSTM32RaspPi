# Library imports

import os, sys

# Code imports

BASE_PATH = os.path.dirname(os.path.realpath(__file__))
WIDGET_PATH = os.path.realpath(os.path.join(BASE_PATH, '..', '..', "Widget"))

RUN_PLOT_PATH = os.path.realpath(os.path.join(BASE_PATH, "plot_RPi.py"))
RUN_WIDGET_PATH = os.path.realpath(os.path.join(WIDGET_PATH, "main.py"))

sys.path.append(WIDGET_PATH)