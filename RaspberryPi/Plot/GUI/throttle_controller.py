# Library imports

from libraries import QWidget, QVBoxLayout, QLabel, QSlider, Qt, QPushButton, QIcon, serial
import gui_settings as set, plot_serial_settings as serial_set

# Definition of the ThrottleController class

class ThrottleController(QWidget):

    def __init__(self):

        super().__init__()

        # Mode variable

        self.mode = 0

        # Throttle value variable

        self.throttle_value = ""

        # Init serial communication and GUI

        self.initSerial()
        self.initUI()

    def initSerial(self):

        try:

            # Open the serial port

            self.ser = serial.Serial(serial_set.SERIAL_PORT, serial_set.BAUDRATE)
            print("Serial port opened successfully.")

        except:

            print("Error opening the serial port.")
        
    def initUI(self):

        # Create a vertical layout

        layout = QVBoxLayout()

        # Create a slider

        self.slider = QSlider(Qt.Horizontal, self)

        self.slider.setMinimum(set.SLIDER_BOUNDS[0])
        self.slider.setMaximum(set.SLIDER_BOUNDS[1])
        self.slider.valueChanged.connect(self.updateThrottle)

        self.slider.setStyleSheet(set.SLIDER_HANDLE_STYLE) 

        # Create a label for the slider

        self.slider_label = QLabel(set.SLIDER_LABEL_TEXT + str(self.slider.value()), self)

        self.slider_label.setStyleSheet(set.SLIDER_LABEL_STYLE)

        # Create a button

        self.mode_button = QPushButton(set.BUTTON_TEXT_MODE, self)

        self.mode_button.setCheckable(True)
        self.mode_button.clicked.connect(self.buttonClicked) 
  
        self.mode_button.setStyleSheet(set.BUTTON_STYLE)    

        # Add widgets to layout

        layout.addWidget(self.slider_label)
        layout.addWidget(self.slider)
        layout.addWidget(self.mode_button)

        # Set the layout for the widget

        self.setLayout(layout)

        # Set the window

        self.setWindowTitle(set.WINDOW_TITLE)
        self.setGeometry(set.WINDOW_GEOMETRY[0], set.WINDOW_GEOMETRY[1], set.WINDOW_GEOMETRY[2], set.WINDOW_GEOMETRY[3])  # set window geometry
        self.setWindowIcon(QIcon(set.ICON_PATH))

        # Set the background color

        self.setStyleSheet(set.BACKGROUND_STYLE)

    def buttonClicked(self):

        if self.mode_button.isChecked():

            self.mode = 1                   # STM32 gets input values from the Throttle Controller
            
        else:       

            self.mode = 0                   # STM32 gets input values from the physical dispositive

    def updateThrottle(self):

        self.throttle_value = str(self.slider.value())

        self.slider_label.setText(set.SLIDER_LABEL_TEXT + self.throttle_value)

        if self.mode == 1:

            self.serialTransmit()

    def serialTransmit(self):

        try: 

            # Transmit data (throttle value) over the serial port

            self.ser.write(self.throttle_value.encode())
            print("Transmitted data:", self.throttle_value)

        except:
            
            print("Error writing data to the serial port.")