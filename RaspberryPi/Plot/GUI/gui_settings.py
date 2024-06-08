# Library imports

from libraries import os, sys

# Base path

BASE_PATH = os.path.dirname(os.path.realpath(__file__))

# Window

WINDOW_TITLE = 'Throttle Controller'
WINDOW_GEOMETRY = [300, 100, 500, 100]

# Background

BACKGROUND_STYLE = "background-color: lightgreen;"

# Icon

ICON_PATH = os.path.realpath(os.path.join(BASE_PATH, "Assets", "icon.png"))

# Slider

SLIDER_LABEL_TEXT = "Throttle: "
SLIDER_LABEL_STYLE = "color: green; font-size: 15px; font-weight: bold;"

SLIDER_HANDLE_STYLE = "QSlider::handle:horizontal { background-color: green; }"

SLIDER_BOUNDS = [0, 100]

# Button

BUTTON_TEXT_MODE = "Press for SIMULATION"

BUTTON_STYLE = "background-color: green; font-weight: bold;"

# Serial communication

PLOT_SERIAL_PATH = os.path.realpath(os.path.join(BASE_PATH, '..', "Graph", "Serial"))
sys.path.append(PLOT_SERIAL_PATH)