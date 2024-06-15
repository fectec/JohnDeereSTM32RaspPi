# John Deere STM32 & Raspberry Pi

Main project in collaboration with *John Deere* for the undergrad course “**System Design on Chip**”, which delves mainly into *SoCs*, *Computer Architecture and Organization*, *Bare Metal Programming*, *Real-Time Operating Systems* and *Embedded Linux*.

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a2e3f5e0-a5d1-4a21-a7a1-1e9dee4edf54" alt = "NUCLEO-F103RB & Raspberry Pi 3 Model B"/>
</p>

It consists of a **John Deere tractor driving simulator**. The project uses SoCs to prototype the technologies integrated into a John Deere agricultural tractor. A *matrix keypad* represents the Steering and Braking of the vehicle, and a *potentiometer* represents the Throttle. The *NUCLEO-F103RB* development board with *STM32F103RB MCU* displays these values on an *LCD*. Also, through the *UART* protocol, they are sent to a *Raspberry Pi 3 Model B* (with *Raspberry Pi OS 64-bit*, *based on Debian*), which carries out its processing and graphing on a screen.

### First Physical Test

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/53f0341c-1f7c-4d7f-8cf4-8736078b7f43" alt = "First Physical Demo" width="600" height="350"/>
</p>

### Final Physical Test

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/8f712f2e-be62-41b0-96c5-b83a94b2bdbf" alt = "Final Physical Demo" width="400" height="300"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/0de1c4ec-86eb-4cae-99a6-1186f1f1a89f" alt = "Final Physical Demo" width="600" height="350"/>
</p>

## Schematic Diagram

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/32a6bc8c-37bf-4e23-9471-2c223f21b508" alt = "Boards"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a70a0e8e-5ac5-4a2c-acda-91c0dac7272c" alt = "Inputs" width="500" height="450"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/dc73c69d-eedd-4f88-a5e9-a8ea6115a675" alt = "Image outputs" width="600" height="300"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/1fc19804-64f4-4ad0-a7f6-30c772a6479e" alt = "LEDs Output" width="200" height="250"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/c33448a6-4618-4868-a795-044317b1b2fc" alt = "Micro Servo Output" width="200" height="180"/>
</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/59e5efac-e0c5-403f-a1a3-363c7e69a983" alt = "FTDI Output" width="500" height="200"/>
</p>

## NUCLEO-F103RB Model Integration

John Deere provided the files for a model of a **tractor engine automatic transmission controller**. This receives two input values, vehicle Throttle and Brake, and returns three output values, *Engine speed*, *Vehicle Speed* and *Gear*. Since a potentiometer represents the Throttle, the *ADC* on the NUCLEO-F103RB board is used to sense a variable voltage value which is then normalized to a range of 0 to 100 and fed to the model. 

On the other hand, the *matrix keypad* is read by declaring the *rows* pins as *outputs* and the *columns* pins as *pull-up inputs*. Then, the row to be read is selected by setting the corresponding pin to ground and turning on the remaining pins. Thus, if a button in this row is pressed, an input will detect a logic 0 while the others remain at logic 1, so it is necessary to detect which of these has such a value to determine the column, and thus, the pressed button. If the pressed button is not found in such a row, then the procedure is repeated with the next row. In other words, it is a constant process of sweeping through rows and columns.

Then, the button pressed is decoded into an action. The 5 sets the Brake value to 100. Meanwhile, 4 and 6 are treated as left and right, their effect being to decrease by one the value of the voltage read (before normalization, i.e., in the range of 0 to 3.3V), in order to simulate a slowdown during a turn in a curve. Again, the Brake value is fed to the model. 

Once the model has processed this information, the output data is sent via the *USART internal peripheral* to the *UART TX pin* of the NUCLEO-F103RB board, which, like it will be reviewed later, is connected to the *UART RX* pin of the Raspberry Pi. It is also string formatted and written to the LCD. It is important to note that the *TIM internal peripheral* is programmed to provide the required delays to both the model and the LCD.

It should be noted that there are two modes of operation: *manual* and *simulation*. In the first one, the Throttle is determined by the potentiometer, and in the second one, with a value sent through the serial port by the Raspberry Pi. Button A on the matrix keyboard chooses the manual mode, while button B selects the simulation mode. In the latter, the input data is read via the *UART RX pin* of the NUCLEO-F103RB board which is connected to the *UART TX* pin of the Raspberry Pi. 

## Raspberry Pi 3 Model B Plotting

The Raspberry Pi receives the output data from the model (engine speed, vehicle speed and gear) through the *UART RX pin*. Thus, using the *serial* library, the serial port containing the real-time values is read. These are written to a CSV file with the *csv* library and plotted with the *Matplotlib* library. A graphical interface was also realized via the *Pygame* library, which receives the graphs from *Matplotlib* in raw data format, converts them to surfaces, and can then draw them within the same game window. At an earlier stage of the development, a plotting script using *randomly generated data* was created. This file is also provided. 

To use the graphical interface, run **game.py**. It is possible to select between randomly generated or serially read data by uncommenting the desired functionality line and commenting the remaining one at the top of the file in the code imports section. To plot without a Pygame graphical interface, run **plot_RPi.py**, which uses serially read data. 

In addition, a widget was created with the *Tkinter* library in which the user can stipulate a Throttle value by means of a slider. If the button corresponding to the simulation is pressed, the Throttle is transmitted over the *UART TX pin* with the help of the same library used to receive. To use it run **widget.py**.

### Graphical Interface with Random Data

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/9bc90f82-4e30-47a8-b825-0492acb042d1" alt = "Graphical Interface Random Data Demo" width="600" height="350"/>
</p>

### Graphical Interface with Serial Data

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/277b9cf4-1416-4760-bf3c-58a580699492" alt = "Graphical Interface Serial Data Demo" width="600" height="350"/>
</p>

### No Graphical Interface with Serial Data on Raspberry Pi

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/98e5ec46-dd77-45ab-bebe-3e1e409a786b" alt = "No Graphical Interface Serial Data Demo" width="600" height="350"/>
</p>

### Throttle Controller Widget

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/acb6facc-3afd-4e62-b664-717f83fbbfff" alt = "Throttle Controller Widget Demo" width="600" height="350"/>
</p>

In all serial interaction cases, modify **plot_serial_settings.py** to specify the serial port depending on your test environment, i.e, *COMX* for Windows or */dev/ttySX* for Linux. The CSV files with the data (random or serial) will be stored in the *Data* folder. A script for testing a serial connection is uploaded. Once more, the serial port is modifiable within the plot_serial_settings.py, alongside the baud rate, which is by default 115200 to ensure compatibility with the NUCLEO-F103RB intern USART peripheral which operates at the same rate. 

Finally, **bash scripts** were written to simplify the process of running the plotting and widget files. It ensures the current user has *access* to the *serial interface and port*, creates and activates a *Python virtual environment*, installs (if necessary) the required *packages* (Pygame, Matplotlib, Numpy, Pyserial), *changes the directory* to the location of the file, *executes* it and *deactivates* the virtual environment. Don't forget to run **sudo raspi-config** to enable the serial port. 

## RTOS

To conclude the project, the code was refactored to add a Real-Time Operating System, in this case, using the CMSIS_V1 API for FreeRTOS. The program was divided into tasks, to which an approximate execution time was measured. Then, based on the Rate-monotonic scheduling (RMS) priority assignment algorithm, the priority of each task was determined and a feasibility analysis for such selection was performed. 

## Bonus - OLED Screen

The *I2C internal peripheral* was configured to communicate with a *128x64 OLED screen* (although it is possible to use a 128x32 screen). Then, functions were developed so it would be possible to display images sending *commands* and *data* in the format of a *buffer*.

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/e12e0cb1-62c1-4d93-9d94-f2e031be2def" alt = "OLED Screen" width="210" height="120"/>
</p>

## Bonus - PWM for Micro Servo

A *TIM internal peripheral* was used to generate a *PWM signal* and control a *Micro Servo*, simulating the movement of the tractor's steering wheel.
