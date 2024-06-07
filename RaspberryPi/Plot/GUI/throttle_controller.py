# Library imports

from libraries import QWidget, QVBoxLayout, QLabel, QSlider, Qt, QPushButton, QIcon
from gui_settings import SLIDER_LABEL_TEXT, SLIDER_LABEL_STYLE, SLIDER_BOUNDS, SLIDER_HANDLE_STYLE, WINDOW_TITLE, WINDOW_GEOMETRY, BUTTON_TEXT_MODE, BUTTON_STYLE, ICON_PATH, BACKGROUND_STYLE

# Definition of the ThrottleController class

class ThrottleController(QWidget):

    def __init__(self):

        super().__init__()
        self.initUI()

    def initUI(self):

        # Create a vertical layout

        layout = QVBoxLayout()

        # Create a slider

        self.slider = QSlider(Qt.Horizontal, self)

        self.slider.setMinimum(SLIDER_BOUNDS[0])
        self.slider.setMaximum(SLIDER_BOUNDS[1])
        self.slider.valueChanged.connect(self.updateThrottleText)

        self.slider.setStyleSheet(SLIDER_HANDLE_STYLE) 

        # Create a label for the slider

        self.slider_label = QLabel(SLIDER_LABEL_TEXT + str(self.slider.value()), self)

        self.slider_label.setStyleSheet(SLIDER_LABEL_STYLE)

        # Create a button

        self.mode_button = QPushButton(BUTTON_TEXT_MODE, self)

        self.mode_button.setCheckable(True)
        self.mode_button.clicked.connect(self.buttonClicked) 
  
        self.mode_button.setStyleSheet(BUTTON_STYLE)    

        # Add widgets to layout

        layout.addWidget(self.slider_label)
        layout.addWidget(self.slider)
        layout.addWidget(self.mode_button)

        # Set the layout for the widget

        self.setLayout(layout)

        # Set the window

        self.setWindowTitle(WINDOW_TITLE)
        self.setGeometry(WINDOW_GEOMETRY[0], WINDOW_GEOMETRY[1], WINDOW_GEOMETRY[2], WINDOW_GEOMETRY[3])  # set window geometry
        self.setWindowIcon(QIcon(ICON_PATH))

        # Set the background color

        self.setStyleSheet(BACKGROUND_STYLE)

        # Mode variable

        self.mode = 0

    def buttonClicked(self):

        if self.mode_button.isChecked():
            self.mode = 1                   # STM32 gets input values from the Throttle Controller
        else:       
            self.mode = 0                   # STM32 gets input values from the physical dispositive

    def updateThrottleText(self):

        throttle_value = self.slider.value()

        self.slider_label.setText(SLIDER_LABEL_TEXT + str(throttle_value))

        if self.mode == 1:
            print(throttle_value)