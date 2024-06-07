# Library imports

import matplotlib.pyplot as plt, csv, random, numpy as np

# Code imports

import plot_random_settings as set

# Tractor's parameters variables

angular_velocity = 0 # rad/s
wheel_radius = 0.5 # m
transmission_ratio = 4 # no unit
rpm = 0 # revolutions per minute

# List and matrix for live plotting

x_values = list(range(0, set.X_RANGE))
parameters_values = np.zeros((set.X_RANGE, set.NUMBER_OF_VARIABLES))

# Function for generating random values

def generate_random_value(lower_bound, upper_bound, decimal=True):
  if(decimal == True):
    return random.uniform(lower_bound, upper_bound)
  else:
    return random.randint(lower_bound, upper_bound)

# Figure and axes declaration

fig, axes = plt.subplots(set.NUMBER_OF_VARIABLES, 1, figsize=set.PLOT_SIZE)
fig.subplots_adjust(hspace=0.5)
scatter_plots = [ax.plot(x_values, parameters_values[:, i], 'g-')[0] for i, ax in enumerate(axes)]

for i in range(set.NUMBER_OF_VARIABLES):
  axes[i].set_xlabel('Samples')

for i in range(set.NUMBER_OF_VARIABLES):
  axes[i].set_xlim(0, set.X_RANGE)

axes[0].set_ylabel('Angular Velocity (rad/s)')
axes[0].set_ylim(set.ANGULAR_VELOCITY_BOUNDS[0] - set.ANGULAR_VELOCITY_BOUNDS[0], set.ANGULAR_VELOCITY_BOUNDS[1] + set.ANGULAR_VELOCITY_BOUNDS[0])

axes[1].set_ylabel('Wheel Radius (m)')
axes[1].set_ylim(set.WHEEL_RADIUS_BOUNDS[0] - set.WHEEL_RADIUS_BOUNDS[0], set.WHEEL_RADIUS_BOUNDS[1] + set.WHEEL_RADIUS_BOUNDS[0])

axes[2].set_ylabel('Transmission Ratio')
axes[2].set_ylim(set.TRANSMISSION_RATIO_BOUNDS[0] - set.TRANSMISSION_RATIO_BOUNDS[0], set.TRANSMISSION_RATIO_BOUNDS[1] + set.TRANSMISSION_RATIO_BOUNDS[0])

axes[3].set_ylabel('rpm (rpm)')
axes[3].set_ylim(set.RPM_BOUNDS[0] - set.RPM_BOUNDS[0], set.RPM_BOUNDS[1] + set.RPM_BOUNDS[0])

# Create CSV file

with open(set.CSV_FILE_PATH, mode = 'w', newline = '') as file:
    writer = csv.writer(file)
    writer.writerow(['Angular Velocity (rad/s)', 'Wheel Radius (m)', 'Transmission Ratio (No Unit)', 'rpm (rpm)'])

# Generate random values

frame = 0

def run_plot():

    global parameters_values, transmission_ratio, frame

    # Assign random value to angular velocity and wheel radius variables

    angular_velocity = generate_random_value(set.ANGULAR_VELOCITY_BOUNDS[0], set.ANGULAR_VELOCITY_BOUNDS[1])
    wheel_radius = generate_random_value(set.WHEEL_RADIUS_BOUNDS[0], set.WHEEL_RADIUS_BOUNDS[1])

    # Transmission ratio variable is changed as well, not as usual as the other two

    if(frame % 10 == 0):
      transmission_ratio = generate_random_value(set.TRANSMISSION_RATIO_BOUNDS[0], set.TRANSMISSION_RATIO_BOUNDS[1], False)

    # Calculate rpm

    rpm = (angular_velocity * 60) / (2 * set.math.pi * wheel_radius * transmission_ratio)

    # Write values to CSV

    with open(set.CSV_FILE_PATH, mode = 'a', newline = '') as file:
      writer = csv.writer(file)
      writer.writerow([angular_velocity, wheel_radius, transmission_ratio, rpm])

    # Add new values to parameters values matrix

    new_row = np.array([angular_velocity, wheel_radius, transmission_ratio, rpm])
    parameters_values = np.vstack([parameters_values, new_row])

    # Limit parameters values matrix to set number of items

    parameters_values = parameters_values[-set.X_RANGE : , :]

    # Update lines with new values

    for j, scatter_plot in enumerate(scatter_plots):
      scatter_plot.set_ydata(parameters_values[:, j])

    frame += 1

    return fig

if __name__ == "__main__":
  run_plot()