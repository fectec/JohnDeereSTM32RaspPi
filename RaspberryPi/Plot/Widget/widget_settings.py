# Library imports

from libraries import os, sys

# Base path

BASE_PATH = os.path.dirname(os.path.realpath(__file__))

# Window settings

WINDOW_TITLE = 'Throttle Controller'
WINDOW_GEOMETRY = [300, 100, 500, 100]

# Background style

BACKGROUND_STYLE = "#4BB213"

# Icon path

ICON_PATH = os.path.realpath(os.path.join(BASE_PATH, "Assets", "icon.png"))

# Slider settings

SLIDER_LABEL_TEXT = "Throttle: "
SLIDER_BOUNDS = [0, 100]
SLIDER_BACKGROUND_COLOR = "#B5E549"

# Button settings

BUTTON_TEXT_MODE = "Press for SIMULATION"
BUTTON_STYLE = "background-color: green; font-weight: bold;"

# Serial communication

PLOT_SERIAL_PATH = os.path.realpath(os.path.join(BASE_PATH, '..', "Graph", "Serial"))
sys.path.append(PLOT_SERIAL_PATH)