# John Deere STM32 & Raspberry Pi

<p align="justify">Main project in collaboration with <b>John Deere</b> for the undergrad course "<b>System Design on Chip</b>", which delves mainly into <i>SoCs</i>, <i>Computer Architecture and Organization</i>, <i>Bare Metal Programming</i>, <i>Real-Time Operating Systems</i>, and <i>Embedded Linux</i>.</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a2e3f5e0-a5d1-4a21-a7a1-1e9dee4edf54" alt = "NUCLEO-F103RB & Raspberry Pi 3 Model B width="200" height="150"/>
</p>

<p align="justify">It consists of a <b>John Deere tractor driving simulator</b>. The project uses SoCs to prototype the technologies integrated into a John Deere agricultural tractor. A <i>matrix keypad</i> represents the Steering and Braking of the vehicle, and a <i>potentiometer</i> represents the Throttle. The <b>NUCLEO-F103RB</b> development board with <b>STM32F103RB MCU</b> operates those values with a <i>tractor engine automatic transmission controller</i> model and displays the output on an <i>LCD</i>. Also, through the <i>UART</i> protocol, it is sent to a <b>Raspberry Pi 3 Model B</b> (with <i>Raspberry Pi OS 64-bit</i>, <i>based on Debian</i>), which carries out its graphing on a screen.</p>

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

<p align="justify">John Deere provided the files for a model of a <b>tractor engine automatic transmission controller</b>. This receives two input values, vehicle Throttle and Brake, and returns three output values, <i>Engine speed</i>, <i>Vehicle Speed</i> and <i>Gear</i>. Since a potentiometer represents the Throttle, the <i>ADC</i> on the NUCLEO-F103RB board is used to sense a variable voltage value which is then normalized to a range of 0 to 100 and fed to the model.</p>

<p align="justify">On the other hand, the <i>matrix keypad</i> is read by declaring the <i>rows</i> pins as <i>outputs</i> and the <i>columns</i> pins as <i>pull-up inputs</i>. Then, the row to be read is selected by setting the corresponding pin to ground and turning on the remaining pins. Thus, if a button in this row is pressed, an input will detect a logic 0 while the others remain at logic 1, so it is necessary to detect which of these has such a value to determine the column, and thus, the pressed button. If the pressed button is not found in such a row, then the procedure is repeated with the next row. In other words, it is a constant process of sweeping through rows and columns.</p>

<p align="justify">Once the model has processed this information, the output data is sent via the <i>USART internal peripheral</i> to the <i>UART TX pin</i> of the NUCLEO-F103RB board, which, like it will be reviewed later, is connected to the <i>UART RX</i> pin of the Raspberry Pi. It is also string formatted and written to the LCD. It is important to note that the <i>TIM internal peripheral</i> is programmed to provide the required delays to both the model and the LCD.</p>

<p align="justify">It should be noted that there are two modes of operation: <i>manual</i> and <i>simulation</i>. In the first one, the Throttle is determined by the potentiometer, and in the second one, with a value sent through the serial port by the Raspberry Pi. Button A on the matrix keyboard chooses the manual mode, while button B selects the simulation mode. In the latter, the input data is read via the <i>UART RX pin</i> of the NUCLEO-F103RB board which is connected to the <i>UART TX</i> pin of the Raspberry Pi.</p>

## Raspberry Pi 3 Model B Plotting

<p align="justify">The Raspberry Pi receives the output data from the model (engine speed, vehicle speed and gear) through the <i>UART RX pin</i>. Thus, using the <i>serial</i> library, the serial port containing the real-time values is read. These are written to a CSV file with the <i>csv</i> library and plotted with the <i>Matplotlib</i> library. A graphical interface was also realized via the <i>Pygame</i> library, which receives the graphs from <i>Matplotlib</i> in raw data format, converts them to surfaces, and can then draw them within the same game window.</p>

<p align="justify">To use the graphical interface, run <b>game.py</b>. It is possible to select between randomly generated or serially read data by uncommenting the desired functionality line and commenting the remaining one at the top of the file in the code imports section. To plot without a Pygame graphical interface, run <b>plot_RPi.py</b>, which uses serially read data.</p>

<p align="justify">In addition, a widget was created with the <i>Tkinter</i> library in which the user can stipulate a Throttle value by means of a slider. If the button corresponding to the simulation is pressed, the Throttle is transmitted over the <i>UART TX pin</i> with the help of the same library used to receive. To use it run <b>widget.py</b>.</p>

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

<p align="justify">In all serial interaction cases, modify <b>plot_serial_settings.py</b> to specify the serial port depending on your test environment, i.e, <i>COMX</i> for Windows or <i>/dev/ttySX</i> for Linux. The CSV files with the data (random or serial) will be stored in the <i>Data</i> folder. A script for testing a serial connection is uploaded. Once more, the serial port is modifiable within the plot_serial_settings.py, alongside the baud rate, which is by default 115200 to ensure compatibility with the NUCLEO-F103RB intern USART peripheral which operates at the same rate.</p>

<p align="justify">Finally, <b>bash scripts</b> were written to simplify the process of running the plotting and widget files. It ensures the current user has <i>access</i> to the <i>serial interface and port</i>, creates and activates a <i>Python virtual environment</i>, installs (if necessary) the required <i>packages</i> (Pygame, Matplotlib, Numpy, Pyserial), <i>changes the directory</i> to the location of the file, <i>executes</i> it and <i>deactivates</i> the virtual environment. Don't forget to run <i>sudo raspi-config</i> to enable the serial port.</p>

## Real-Time Operating System

<p align="justify">To conclude the project, the Bare Metal code was refactored to add a <b>Real-Time Operating System</b> (RTOS), in this case, using the <i>CMSIS_V1 API</i> for <i>FreeRTOS</i>. The program was divided into tasks, for which an approximate execution time was measured. Then, based on the <i>rate-monotonic scheduling</i> (RMS) priority assignment algorithm, the priority of each task was determined and a feasibility analysis for such selection was performed.</p>

## Bonus - OLED Screen

<p align="justify">The <i>I2C internal peripheral</i> was configured to communicate with a <i>128x64 OLED screen</i> (although it is possible to use a 128x32 screen). Then, functions were developed so it would be possible to display images sending <i>commands</i> and <i>data</i> in the format of a <i>buffer</i>.</p>

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/e12e0cb1-62c1-4d93-9d94-f2e031be2def" alt = "OLED Screen" width="210" height="120"/>
</p>

## Bonus - PWM for Micro Servo

<p align="justify">A <i>TIM internal peripheral</i> was used to generate a <i>PWM signal</i> and control a <i>Micro Servo</i>, simulating the movement of the tractor's steering wheel.</p>
