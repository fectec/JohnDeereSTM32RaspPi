# Library imports

from libraries import serial, time, tk, ttk
import widget_settings as set, plot_serial_settings as serial_set

# Definition of the ThrottleController class

class ThrottleController(tk.Tk):

    def __init__(self):

        super().__init__()

        # Mode variable

        self.mode = 0

        # Throttle value variable

        self.throttle_value = ""

        # Init serial communication and GUI

        self.init_serial()
        self.init_ui()

        # Bind keyboard events

        self.bind("<Left>", self.move_slider_left)
        self.bind("<Right>", self.move_slider_right)

    def init_serial(self):

        try:

            # Open the serial port

            self.ser = serial.Serial(serial_set.SERIAL_PORT, serial_set.BAUDRATE)
            print("Serial port opened successfully.")

        except:

            print("Error opening the serial port.")
        
    def init_ui(self):

        self.title(set.WINDOW_TITLE)
        self.geometry(f"{set.WINDOW_GEOMETRY[2]}x{set.WINDOW_GEOMETRY[3]}")
        self.configure(bg=set.BACKGROUND_STYLE)

        window_icon = tk.PhotoImage(file=set.ICON_PATH)
        self.iconphoto(True, window_icon)

        # Create a vertical layout

        layout = ttk.Frame(self)

        # Create a custom style for the slider
        
        style = ttk.Style()
        style.configure("Custom.Horizontal.TScale", background=set.SLIDER_BACKGROUND_COLOR)

        # Create a slider

        self.slider = ttk.Scale(layout, from_=set.SLIDER_BOUNDS[0], to=set.SLIDER_BOUNDS[1], orient="horizontal", style="Custom.Horizontal.TScale")
        self.slider.set(set.SLIDER_BOUNDS[0])
        self.slider.bind("<ButtonRelease>", self.update_throttle)
        self.slider.pack()

        # Create a label for the slider

        self.slider_label = ttk.Label(layout, text=set.SLIDER_LABEL_TEXT + str(self.slider.get()), style="Slider.TLabel")
        self.slider_label.pack()

        # Create a button

        self.mode_button = ttk.Checkbutton(layout, text=set.BUTTON_TEXT_MODE, command=self.button_clicked, style="Custom.TButton")
        self.mode_button.pack()

        layout.pack()

    def button_clicked(self):

        # STM32 gets input values from the Throttle Controller or 
        # from the physical dispositive

        self.mode = 1 if self.mode_button.instate(['selected']) else 0 
    
    def move_slider_left(self, event):

        value = max(self.slider.get() - 1, 0)
        self.slider.set(value)
        self.update_throttle()

    def move_slider_right(self, event):
        
        value = min(self.slider.get() + 1, 100)
        self.slider.set(value)
        self.update_throttle()

    def update_throttle(self):
        
        self.throttle_value = int(self.slider.get())

        self.slider_label.config(text=set.SLIDER_LABEL_TEXT + str(self.throttle_value))

        if self.mode == 1:
            
            self.serial_transmit()

    def serial_transmit(self):

        try: 

            # Transmit data (throttle value) over the serial port

            self.ser.write(self.throttle_value.to_bytes())

            time.sleep(0.1)
            
            print("Transmitted data:", str(self.throttle_value))

        except:
            
            print("Error writing data to the serial port.")