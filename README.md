# John Deere STM32 & Raspberry Pi

Main project in collaboration with *John Deere* for the undergrad course “**System Design on Chip**”, which delves mainly into *SoCs*, *Computer Architecture and Organization*, *Bare Metal* Programming and *Embedded Linux*.

<p align="center">
  <img src="https://github.com/fectec/JohnDeereSTM32RaspPi/assets/127822858/a2e3f5e0-a5d1-4a21-a7a1-1e9dee4edf54" alt = "NUCLEO-F103RB & Raspberry Pi 3 Model B"/>
</p>

It consists of a **John Deere tractor driving simulator**. The project uses SoCs to prototype the technologies integrated into a John Deere agricultural tractor. *Buttons* represents the Steering and Braking of the vehicle, *switches* the Gear Selection and a *potentiometer* the Throttle. The *NUCLEO-F103RB* development board with *STM32F103RB MCU* displays these values on an *LCD*. Also, through the *UART* protocol, they are sent to a *Raspberry Pi 3 Model B*, which carries out its processing and graphing on a screen. 
