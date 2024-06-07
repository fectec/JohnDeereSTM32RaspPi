# Library imports

from libraries import QWidget, QVBoxLayout, QLabel, QSlider, Qt, QPushButton, QIcon, QFont, os
from gui_settings import FONT, FONT_SIZE, SLIDER_LABEL_TEXT, SLIDER_LABEL_STYLE, SLIDER_BOUNDS, SLIDER_HANDLE_STYLE, WINDOW_TITLE, WINDOW_GEOMETRY, BUTTON_TEXT_MODE_1, BUTTON_TEXT_MODE_2, BUTTON_STYLE

# Definition of the ThrottleController class

class ThrottleController(QWidget):

    def __init__(self):

        super().__init__()
        self.initUI()

    def initUI(self):

        # Create a vertical layout

        layout = QVBoxLayout()

        # Set the font

        font = QFont(FONT, FONT_SIZE)

        # Create a label for the slider

        self.slider_label = QLabel(SLIDER_LABEL_TEXT, self)

        self.slider_label.setFont(font) 
        self.slider_label.setStyleSheet(SLIDER_LABEL_STYLE)

        # Create a slider

        self.slider = QSlider(Qt.Horizontal, self)

        self.slider.setMinimum(SLIDER_BOUNDS[0])
        self.slider.setMaximum(SLIDER_BOUNDS[1])

        self.slider.setStyleSheet(SLIDER_HANDLE_STYLE) 

        # Create a button

        self.mode_button = QPushButton(BUTTON_TEXT_MODE_1, self)

        self.mode_button.setCheckable(True)
        self.mode_button.setChecked(True)
        self.mode_button.clicked.connect(self.buttonClicked) 

        self.mode_button.setFont(font)    
        self.mode_button.setStyleSheet(BUTTON_STYLE)              

        # Add widgets to layout

        layout.addWidget(self.slider_label)
        layout.addWidget(self.slider)
        layout.addWidget(self.mode_button)

        # Set the layout for the widget

        self.setLayout(layout)

        self.setWindowTitle(WINDOW_TITLE)
        self.setGeometry(WINDOW_GEOMETRY[0], WINDOW_GEOMETRY[1], WINDOW_GEOMETRY[2], WINDOW_GEOMETRY[3])  # set window geometry

        icon_path = os.path.join("Assets", "icon.png")
        self.setWindowIcon(QIcon(icon_path))

    def buttonClicked(self):

        if self.mode_button.isChecked():
            self.mode_button.setText(BUTTON_TEXT_MODE_2)
        else:
            self.mode_button.setText(BUTTON_TEXT_MODE_1)