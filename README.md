# John Deere STM32 & Raspberry Pi

Main project in collaboration with *John Deere* for the undergrad course “**System Design on Chip**”, which delves mainly into *SoCs*, *Computer Architecture and Organization*, *Bare Metal Programming*, *Real-Time Operating Systems* and *Embedded Linux*.

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a2e3f5e0-a5d1-4a21-a7a1-1e9dee4edf54" alt = "NUCLEO-F103RB & Raspberry Pi 3 Model B"/>
</p>

It consists of a **John Deere tractor driving simulator**. The project uses SoCs to prototype the technologies integrated into a John Deere agricultural tractor. A *matrix keypad* represents the Steering and Braking of the vehicle, and a *potentiometer* represents the Throttle. The *NUCLEO-F103RB* development board with *STM32F103RB MCU* displays these values on an *LCD*. Also, through the *UART* protocol, they are sent to a *Raspberry Pi 3 Model B* (with *Raspberry Pi OS 64-bit*, *based on Debian*), which carries out its processing and graphing on a screen.

## Schematic Diagram

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/2c093969-b633-49ea-a714-b15d97b25be8" alt = "Boards"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/24e47b09-ac57-4903-a343-ffd03eb09838" alt = "Inputs" width="500" height="450"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/91148303-7e2e-4740-a791-cfd799e3a00f" alt = "Outputs" width="600" height="300"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/c7cc9924-c6d5-40a0-8bd2-2a930c9e2250" alt = "LEDs Output" width="200" height="250"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a3f06499-64ff-4d7e-99d5-d39f5a66b107" alt = "FTDI Output" width="500" height="200"/>
</p>

## NUCLEO-F103RB Model Integration

John Deere provided the files for a model of a **tractor engine automatic transmission controller**. This receives two input values, vehicle Throttle and Brake, and returns three output values, *Engine speed*, *Vehicle Speed* and *Gear*. Since a potentiometer represents the Throttle, the *ADC* on the NUCLEO-F103RB board is used to sense a variable voltage value which is then normalized to a range of 0 to 100 and fed to the model. 

On the other hand, the *matrix keypad* is read by declaring the *rows* pins as *outputs* and the *columns* pins as *pull-up inputs*. Then, the row to be read is selected by setting the corresponding pin to ground and turning on the remaining pins. Thus, if a button in this row is pressed, an input will detect a logic 0 while the others remain at logic 1, so it is necessary to detect which of these has such a value to determine the column, and thus, the pressed button. If the pressed button is not found in such a row, then the procedure is repeated with the next row. In other words, it is a constant process of sweeping through rows and columns.

Then, the button pressed is decoded into an action. The 5 sets the Brake value to 100. Meanwhile, 4 and 6 are treated as left and right, their effect being to decrease by one the value of the voltage read (before normalization, i.e., in the range of 0 to 3.3V), in order to simulate a slowdown during a turn in a curve. Again, the Brake value is fed to the model. 

Once the model has processed this information, the output data is sent via the *USART internal peripheral* to the *UART TX pin* of the NUCLEO-F103RB board, which, like it will be reviewed later, is connected to the *UART RX* pin of the Raspberry Pi. It is also string formatted and written to the LCD. It is important to note that the *TIM internal peripheral* is programmed to provide the required delays to both the model and the LCD.

## Raspberry Pi 3 Model B Plotting

The Raspberry Pi receives the output data from the model (engine speed, vehicle speed and gear) through the UART RX pin. Thus, using the *serial* library, the serial port containing the real-time values is read. These are written to a CSV file with the *csv* library and plotted with the *Matplotlib* library. A graphical interface was also realized via the *Pygame* library, which receives the graphs from *Matplotlib* in raw data format, converts them to surfaces, and can then draw them within the same game window. At an earlier stage of the development, a plotting script using *randomly generated data* was created. This file is also provided. 

To use the graphical interface, run **game.py**. It is possible to select between randomly generated or serially read data by uncommenting the desired functionality line and commenting the remaining one at the top of the file in the code imports section. To plot without a Pygame graphical interface, run **plot_RPi.py**, which uses serially read data. 

In both serial interaction cases, modify **plot_serial_settings.py** to specify the serial port depending on your test environment, i.e, *COMX* for Windows or */dev/ttySX* for Linux. The CSV files with the data (random or serial) will be stored in the *Data* folder. A script for testing a serial connection is uploaded. Once more, the serial port is modifiable within the plot_serial_settings.py, alongside the baud rate, which is by default 115200 to ensure compatibility with the NUCLEO-F103RB intern USART peripheral which operates at the same rate. 

Finally, a **bash script** was written to simplify the process of running the plotting file. It ensures the current user has *access* to the *serial interface and port*, creates and activates a *Python virtual environment*, installs (if necessary) the required *packages* (Pygame, Matplotlib, Numpy, Pyserial), *changes the directory* to the location of the plotting file, *executes* it and *deactivates* the virtual environment. Don't forget to run **sudo raspi-config** to enable the serial port. 

## Bonus - OLED Screen

The *I2C internal peripheral* was configured to communicate with a *128x64 OLED screen* (although it is possible to use a 128x32 screen). Then, functions were developed so it would be possible to display images sending *commands* and *data* in the format of a *buffer*.

## Demos

### Graphical Interface with Serial Data

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/c96a14ab-8e65-4f09-b992-fef5bcf41a36" alt = "Graphical Interface Serial Data Demo" width="600" height="350"/>
</p>

### Graphical Interface with Random Data

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/9bc90f82-4e30-47a8-b825-0492acb042d1" alt = "Graphical Interface Random Data Demo" width="600" height="350"/>
</p>

### First Physical Test

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/53f0341c-1f7c-4d7f-8cf4-8736078b7f43" alt = "Physical Demo" width="600" height="350"/>
</p>

### OLED Screen
