# Author: System Design On Chip Team 4
# Description: This code generates random values for a tractor's parameters,
# calculates its RPM and saves this data into a CSV file.

import random
import math
import csv
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Tractor's parameters variables

angular_velocity = 0 # rad/s
wheel_radius = 0.5 # m
transmission_ratio = 4 # no unit
RPM = 0 # revolutions per minute

# Simulation constants

ANGULAR_VELOCITY_BOUNDS = [10, 100]
WHEEL_RADIUS_BOUNDS = [0.48, 0.5]
TRANSMISSION_RATIO_BOUNDS = [4, 10]
RPM_BOUNDS = [(ANGULAR_VELOCITY_BOUNDS[0] * 60) / (2 * math.pi * WHEEL_RADIUS_BOUNDS[1] * TRANSMISSION_RATIO_BOUNDS[1]), (ANGULAR_VELOCITY_BOUNDS[1] * 60) / (2 * math.pi * WHEEL_RADIUS_BOUNDS[0] * TRANSMISSION_RATIO_BOUNDS[0])]

X_RANGE = 20

# List and matrix for live plotting

x_values = list(range(0, X_RANGE))
parameters_values = np.zeros((X_RANGE, 4))

# Function for generating random values

def generate_random_value(lower_bound, upper_bound, decimal=True):
  if(decimal == True):
    return random.uniform(lower_bound, upper_bound)
  else:
    return random.randint(lower_bound, upper_bound)

# Figure and axes declaration

fig, axes = plt.subplots(4, 1, figsize=(8, 10))
fig.subplots_adjust(hspace=0.5)
scatter_plots = [ax.plot(x_values, parameters_values[:, i], 'b-')[0] for i, ax in enumerate(axes)]

for i in range(4):
  axes[i].set_xlabel('Samples')

for i in range(4):
  axes[i].set_xlim(0, X_RANGE)

axes[0].set_ylabel('Angular Velocity (rad/s)')
axes[0].set_ylim(ANGULAR_VELOCITY_BOUNDS[0] - ANGULAR_VELOCITY_BOUNDS[0], ANGULAR_VELOCITY_BOUNDS[1] + ANGULAR_VELOCITY_BOUNDS[0])

axes[1].set_ylabel('Wheel Radius (m)')
axes[1].set_ylim(WHEEL_RADIUS_BOUNDS[0] - WHEEL_RADIUS_BOUNDS[0], WHEEL_RADIUS_BOUNDS[1] + WHEEL_RADIUS_BOUNDS[0])

axes[2].set_ylabel('Transmission Ratio (No Unit)')
axes[2].set_ylim(TRANSMISSION_RATIO_BOUNDS[0] - TRANSMISSION_RATIO_BOUNDS[0], TRANSMISSION_RATIO_BOUNDS[1] + TRANSMISSION_RATIO_BOUNDS[0])

axes[3].set_ylabel('RPM (rpm)')
axes[3].set_ylim(RPM_BOUNDS[0] - RPM_BOUNDS[0], RPM_BOUNDS[1] + RPM_BOUNDS[0])

# Create CSV file

FILE_NAME = "tractor_data.csv"

with open(FILE_NAME, mode = 'w', newline = '') as file:
    writer = csv.writer(file)
    writer.writerow(['Angular Velocity (rad/s)', 'Wheel Radius (m)', 'Transmission Ratio (No Unit)', 'RPM (rpm)'])

# Generate random values

def animate(frame):

    global parameters_values, transmission_ratio

    # Assign random value to angular velocity and wheel radius variables

    angular_velocity = generate_random_value(ANGULAR_VELOCITY_BOUNDS[0], ANGULAR_VELOCITY_BOUNDS[1])
    wheel_radius = generate_random_value(WHEEL_RADIUS_BOUNDS[0], WHEEL_RADIUS_BOUNDS[1])

    # Transmission ratio variable is changed as well, not as usual as the other two

    if(frame % 10 == 0):
      transmission_ratio = generate_random_value(TRANSMISSION_RATIO_BOUNDS[0], TRANSMISSION_RATIO_BOUNDS[1], False)

    # Calculate RPM

    RPM = (angular_velocity * 60) / (2 * math.pi * wheel_radius * transmission_ratio)

    # Write values to CSV

    with open(FILE_NAME, mode = 'a', newline = '') as file:
      writer = csv.writer(file)
      writer.writerow([angular_velocity, wheel_radius, transmission_ratio, RPM])

    # Add new values to parameters values matrix

    new_row = np.array([angular_velocity, wheel_radius, transmission_ratio, RPM])
    parameters_values = np.vstack([parameters_values, new_row])

    # Limit parameters values matrix to set number of items

    parameters_values = parameters_values[-X_RANGE : , :]

    # Update lines with new values

    for j, scatter_plot in enumerate(scatter_plots):
      scatter_plot.set_ydata(parameters_values[:, j])

    return scatter_plots

# Create animation

ani = FuncAnimation(fig, animate, frames=range(X_RANGE), blit=True)

# Keep plot window open

plt.show()
