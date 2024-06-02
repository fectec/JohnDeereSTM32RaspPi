# Library imports

import matplotlib.pyplot as plt

import csv
import serial
import numpy as np

# Code imports

import plot_serial_settings as set

# List and matrix for live plotting

x_values = list(range(0, set.X_RANGE))
parameters_values = np.zeros((set.X_RANGE, set.NUMBER_OF_VARIABLES))

# Figure and axes declaration

fig, axes = plt.subplots(set.NUMBER_OF_VARIABLES, 1, figsize=set.PLOT_SIZE)
fig.subplots_adjust(hspace=0.5)
scatter_plots = [ax.plot(x_values, parameters_values[:, i], 'g-')[0] for i, ax in enumerate(axes)]

for i in range(set.NUMBER_OF_VARIABLES):
  axes[i].set_xlabel('Samples')

for i in range(set.NUMBER_OF_VARIABLES):
  axes[i].set_xlim(0, set.X_RANGE)

axes[0].set_ylabel('Throttle')
axes[0].set_ylim(set.THROTTLE_BOUNDS[0] - set.THROTTLE_BOUNDS[0], set.THROTTLE_BOUNDS[1] + set.THROTTLE_BOUNDS[0])

axes[1].set_ylabel('Engine Speed')
axes[1].set_ylim(set.ENGINE_SPEED_BOUNDS[0] - set.ENGINE_SPEED_BOUNDS[0], set.ENGINE_SPEED_BOUNDS[1] + set.ENGINE_SPEED_BOUNDS[0])

axes[2].set_ylabel('Vehicle Speed')
axes[2].set_ylim(set.VEHICLE_SPEED_BOUNDS[0] - set.VEHICLE_SPEED_BOUNDS[0], set.VEHICLE_SPEED_BOUNDS[1] + set.VEHICLE_SPEED_BOUNDS[0])

axes[3].set_ylabel('Gear')
axes[3].set_ylim(set.GEAR_BOUNDS[0] - set.GEAR_BOUNDS[0], set.GEAR_BOUNDS[1] + set.GEAR_BOUNDS[0])

# Create CSV file

with open(set.CSV_FILE_PATH, mode = 'w', newline = '') as file:
    writer = csv.writer(file)
    writer.writerow(['Throttle', 'Engine Speed', 'Vehicle Speed', 'Gear'])

# Instantiate Serial object

ser = serial.Serial(set.SERIAL_PORT, set.BAUDRATE)

def run_plot():

  global parameters_values, ser

  # Read values, decode bytes to string and remove leading/trailing whitespaces

  rx_data = ser.readline().decode('utf_8').strip()
  
  # Split the received string by commas

  values = rx_data.split(',')

  # Check if all values are received

  if len(values) == 4:

    print("Data received: ", rx_data)

    # Write values to CSV

    with open(set.CSV_FILE_PATH, mode = 'a', newline = '') as file:
      writer = csv.writer(file)
      writer.writerow([float(value) for value in values])

    # Add new values to parameters values matrix

    new_row = np.array([float(value) for value in values])
    parameters_values = np.vstack([parameters_values, new_row])

    # Limit parameters values matrix to set number of items

    parameters_values = parameters_values[-set.X_RANGE : , :]

    # Update lines with new values

    for j, scatter_plot in enumerate(scatter_plots):
      scatter_plot.set_ydata(parameters_values[:, j])

  else:
      
    # Handle the case when all values are not received properly

    print("Incomplete data received: ", rx_data)

  return fig

if __name__ == "__main__":
  run_plot()