# John Deere STM32 & Raspberry Pi

Main project in collaboration with *John Deere* for the undergrad course “**System Design on Chip**”, which delves mainly into *SoCs*, *Computer Architecture and Organization*, *Bare Metal Programming* and *Embedded Linux*.

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a2e3f5e0-a5d1-4a21-a7a1-1e9dee4edf54" alt = "NUCLEO-F103RB & Raspberry Pi 3 Model B"/>
</p>

It consists of a **John Deere tractor driving simulator**. The project uses SoCs to prototype the technologies integrated into a John Deere agricultural tractor. A *matrix keypad* represents the Steering and Braking of the vehicle, and a *potentiometer* represents the Throttle. The *NUCLEO-F103RB* development board with *STM32F103RB MCU* displays these values on an *LCD*. Also, through the *UART* protocol, they are sent to a *Raspberry Pi 3 Model B*, which carries out its processing and graphing on a screen. 

## NUCLEO-F103RB model integration

John Deere provided the files for a model of a **tractor engine automatic transmission controller**. This receives two input values, vehicle Throttle and Brake, and returns three output values, **Engine speed**, **Vehicle Speed** and **Gear**. Since a potentiometer represents the *Throttle*, the *ADC* on the NUCLEO-F103RB board is used to sense a variable voltage value which is then normalized to a range of 0 to 100 and fed to the model. 

On the other hand, the *matrix keypad* is read by declaring the *rows* pins as *outputs* and the *columns* pins as *pull-up inputs*. Then, the row to be read is selected by setting the corresponding pin to ground and turning on the remaining pins. Thus, if a button in this row is pressed, an input will detect a logic 0 while the others remain at logic 1, so it is necessary to detect which of these has such a value to determine the column, and thus, the pressed button. If the pressed button is not found in such a row, then the procedure is repeated with the next row. In other words, it is a constant process of sweeping through rows and columns.

Then, the button pressed is decoded into an action. The 5 sets the *Brake* value to 100. Meanwhile, 4 and 6 are treated as left and right, their effect being to decrease by one the value of the voltage read (before normalization, i.e., in the range of 0 to 3.3V), in order to simulate a slowdown during a turn in a curve. Again, the Brake value is fed to the model. 

Once the model has processed this information, the output data is sent via the *USART internal peripheral* to the *UART TX pin* of the NUCLEO-F103RB board, which, like it will be reviewed later, is connected to the *UART RX* pin of the Raspberry Pi. It is also string formatted and written to the LCD. It is important to note that the *TIM internal peripheral* is programmed to provide the required delays to both the model and the LCD.

## Raspberry Pi 3 Model B Plotting

The Raspberry Pi receives the output data from the model (engine speed, vehicle speed and gear) through the UART RX pin. Thus, using the *serial* library, the serial port containing the real-time values is read. These are written to a CSV file with the *csv* library and plotted with the *matplotlib* library. 

A graphical interface was also realized via the *pygame* library, which receives the graphs from *matplotlib* in raw data format, converts them to surfaces, and can then draw them within the same game window. 


