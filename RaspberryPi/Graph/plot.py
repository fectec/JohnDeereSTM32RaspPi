# Library imports

import csv
import numpy as np

import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Code imports

import plot_settings

# List and matrix for live plotting

x_values = list(range(0, plot_settings.X_RANGE))
parameters_values = np.zeros((plot_settings.X_RANGE, plot_settings.NUMBER_OF_VARIABLES))

# Figure and axes declaration

fig, axes = plt.subplots(plot_settings.NUMBER_OF_VARIABLES, 1, figsize=plot_settings.PLOT_SIZE)
fig.subplots_adjust(hspace=0.5)
scatter_plots = [ax.plot(x_values, parameters_values[:, i], 'g-')[0] for i, ax in enumerate(axes)]

for i in range(plot_settings.NUMBER_OF_VARIABLES):
  axes[i].set_xlabel('Samples')

for i in range(plot_settings.NUMBER_OF_VARIABLES):
  axes[i].set_xlim(0, plot_settings.X_RANGE)

axes[0].set_ylabel('Engine Speed')
axes[0].set_ylim(plot_settings.ENGINE_SPEED_BOUNDS[0] - plot_settings.ENGINE_SPEED_BOUNDS[0], plot_settings.ENGINE_SPEED_BOUNDS[1] + plot_settings.ENGINE_SPEED_BOUNDS[0])

axes[1].set_ylabel('Vehicle Speed')
axes[1].set_ylim(plot_settings.VEHICLE_SPEED_BOUNDS[0] - plot_settings.VEHICLE_SPEED_BOUNDS[0], plot_settings.VEHICLE_SPEED_BOUNDS[1] + plot_settings.VEHICLE_SPEED_BOUNDS[0])

axes[2].set_ylabel('Gear')
axes[2].set_ylim(plot_settings.GEAR_BOUNDS[0] - plot_settings.GEAR_BOUNDS[0], plot_settings.GEAR_BOUNDS[1] + plot_settings.GEAR_BOUNDS[0])

# Create CSV file

FILE_NAME = "tractor_data.csv"

with open(FILE_NAME, mode = 'w', newline = '') as file:
    writer = csv.writer(file)
    writer.writerow(['Engine Speed', 'Vehicle Speed', 'Gear'])

# Read values

def run_plot(frame):

    global parameters_values, transmission_ratio

    # Assign random value to angular velocity and wheel radius variables

    engine_speed = 0.5
    vehicle_speed = 1
    gear = 2

    # Write values to CSV

    with open(FILE_NAME, mode = 'a', newline = '') as file:
      writer = csv.writer(file)
      writer.writerow([engine_speed, vehicle_speed, gear])

    # Add new values to parameters values matrix

    new_row = np.array([engine_speed, vehicle_speed, gear])
    parameters_values = np.vstack([parameters_values, new_row])

    # Limit parameters values matrix to set number of items

    parameters_values = parameters_values[-plot_settings.X_RANGE : , :]

    # Update lines with new values

    for j, scatter_plot in enumerate(scatter_plots):
      scatter_plot.set_ydata(parameters_values[:, j])

    return fig