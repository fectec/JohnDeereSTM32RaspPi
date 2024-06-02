# Library imports

import numpy as np
import csv
import serial

import matplotlib.pyplot as plt

# Code imports

import plot_RPi_settings
import plot_serial_settings as set

# Added - New backend for plotting

from matplotlib.backends.backend_agg import FigureCanvasAgg
import pygame as pg
import sys

pg.init()

FPS = 60

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720

SCREEN = pg.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

GAME_PLOT_SIZE = tuple(element * 100 for element in set.PLOT_SIZE)
PLOT_POS = (SCREEN_WIDTH // 2 , SCREEN_HEIGHT // 2 - GAME_PLOT_SIZE[1] // 2)

# Added - Threading imports

import threading
import queue

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

# Added - Queue for communication between threads 

data_queue = queue.Queue()

# Added - Function for receiving data
  
def receive_data():

  try:

    # Open the serial port

    ser = serial.Serial(set.SERIAL_PORT, set.BAUDRATE)
    print("Serial port opened successfully.")

    while True:

      if ser.in_waiting > 0:

        try:

          # Read values, decode bytes to string and remove leading/trailing whitespaces

          rx_data = ser.readline().decode('utf_8').strip()
          
          # Split the received string by commas
        
          values = rx_data.split(',')

          # Check if all values are received

          if len(values) == 4:

            print("Data received: ", rx_data)
            data_queue.put(values)

          else:
            
            # Handle the case when all values are not received properly

            print("Incomplete data received: ", rx_data)

        except UnicodeDecodeError as e:

          print("Error decoding data:", e)

  except serial.SerialException as e:

    print("Error:", e)

  finally:
      
    # Close the serial port

    if ser.is_open:

        ser.close()
        print("Serial port closed.")

# Added - Function for storing in CSV

def store_csv():

  # Create CSV file

  with open(set.CSV_FILE_PATH, mode = 'a', newline = '') as file:
      
    writer = csv.writer(file)

    if file.tell() == 0:

      writer.writerow(['Throttle', 'Engine Speed', 'Vehicle Speed', 'Gear'])
  
    # Write values to CSV

    while True:
      
      values = data_queue.get()
      writer.writerow([float(value) for value in values])

# Added - Function for updating the plot

def update_plot():

  global parameters_values

  try:

    values = data_queue.get()

    # Add new values to parameters values matrix

    new_row = np.array([float(value) for value in values])
    parameters_values = np.vstack([parameters_values, new_row])

      # Limit parameters values matrix to set number of items

    parameters_values = parameters_values[-set.X_RANGE : , :]

    # Update lines with new values

    for j, scatter_plot in enumerate(scatter_plots):
      scatter_plot.set_ydata(parameters_values[:, j])

  except queue.Empty:

    pass

  return fig

# Added - Start threads

receive_thread = threading.Thread(target=receive_data)
store_csv_thread = threading.Thread(target=store_csv)

receive_thread.daemon = True
store_csv_thread.daemon = True

receive_thread.start()
store_csv_thread.start()

if __name__ == "__main__":

  clock = pg.time.Clock()

  # Fetch fig
  
  fig = update_plot()

  # Transform fig into canvas and get its raw data

  canvas = FigureCanvasAgg(fig)
  size = GAME_PLOT_SIZE
  renderer = canvas.get_renderer()
  raw_data = renderer.buffer_rgba()

  while True:

    # Limit game FPS

    clock.tick(FPS)

    # If close window button is pressed, execution stops

    for event in pg.event.get() :
      if event.type == pg.QUIT :
        sys.exit()

    # Fetch a new fig

    fig = update_plot()

    # Redraw canvas

    canvas.draw()

    # Transform canvas' raw data into surface

    surf = pg.image.frombuffer(raw_data.tobytes(), size, "RGBA")

    # Draw plot
        
    SCREEN.blit(surf, PLOT_POS)

    # Update display

    pg.display.update()















    

