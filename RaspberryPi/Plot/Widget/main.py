from throttle_controller import ThrottleController
from widget_settings import ICON_PATH

def run_widget():

    app = ThrottleController()
    app.mainloop()

if __name__ == '__main__':

    run_widget()