#!/bin/bash

# Script to run widget (Tested on: Raspberry Pi 3 Model B - Raspberry Pi OS 64-bit, based on Debian)

set -e                                                                          # Exit immediately if any command fails

#sudo raspi-config nonint do_serial 2                                           # Enable the serial port if needed
cd "$HOME"                                                                      # Change directory to the user's home directory
sudo adduser "$USER" dialout                                                    # Add the current user to the 'dialout' group
sudo chmod 666 /dev/ttyS0                                                       # Set r/w permissions for all users on the device /dev/ttyS0
python3 -m venv "$HOME/.venv"                                                   # Create a Python virtual environment named '.venv'
source "$HOME/.venv/bin/activate"                                               # Activate the virtual environment

cd ~/Downloads/Projects/JohnDeereSTM32RaspPi/RaspberryPi/Plot/Widget            # Change directory to the location of the 'widget.py' Python script (modify if needed)
python3 widget.py                                                               # Run the Python script named 'widget.py'

deactivate                                                                      # Deactivate the virtual environment