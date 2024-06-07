from libraries import QApplication, sys
from throttle_controller import ThrottleController

if __name__ == '__main__':

    app = QApplication(sys.argv)
    throttle_controller = ThrottleController()
    throttle_controller.show()
    sys.exit(app.exec_())