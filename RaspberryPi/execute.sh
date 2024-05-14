#!/bin/bash

# Script to run game (Tested on: Raspberry Pi 3 Model B - Raspberry Pi OS 64-bit, based on Debian)

set -e                                                          # Exit immediately if any command fails

cd "$HOME"                                                      # Change directory to the user's home directory
sudo adduser "$USER" dialout                                    # Add the current user to the 'dialout' group
sudo chmod 666 /dev/ttyS0                                       # Set r/w permissions for all users on the device /dev/ttyS0
python3 -m venv "$HOME/.venv"                                   # Create a Python virtual environment named '.venv'
source "$HOME/.venv/bin/activate"                               # Activate the virtual environment

# Install required Python packages (uncomment and add packages if needed)

#pip install pygame -U
#pip install matplotlib -U
#pip install numpy -U
#pip install pyserial -U

cd ~/Downloads/Projects/JohnDeereSTM32RaspPi/RaspberryPi/Graph  # Change directory to the location of the 'game.py' / 'plot_linux.py' Python scripts (modify if needed)

#python3 game.py                                                # Run the Python script named 'game.py'
python3 plot_linux.py                                           # Run the Python script named 'plot_linux.py'

deactivate                                                      # Deactivate the virtual environment