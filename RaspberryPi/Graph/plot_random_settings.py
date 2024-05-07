# Library imports

import math

# Simulation constants

NUMBER_OF_VARIABLES = 4

ANGULAR_VELOCITY_BOUNDS = [10, 100]
WHEEL_RADIUS_BOUNDS = [0.48, 0.5]
TRANSMISSION_RATIO_BOUNDS = [4, 10]
RPM_BOUNDS = [(ANGULAR_VELOCITY_BOUNDS[0] * 60) / (2 * math.pi * WHEEL_RADIUS_BOUNDS[1] * TRANSMISSION_RATIO_BOUNDS[1]), (ANGULAR_VELOCITY_BOUNDS[1] * 60) / (2 * math.pi * WHEEL_RADIUS_BOUNDS[0] * TRANSMISSION_RATIO_BOUNDS[0])]

X_RANGE = 20

# Plot

PLOT_SIZE = (6, 7)