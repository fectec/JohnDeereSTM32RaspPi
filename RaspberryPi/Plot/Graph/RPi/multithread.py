# Library imports

import multiprocessing

# Code imports

import multithreading_settings
from multithreading_settings import RUN_PLOT_PATH, RUN_WIDGET_PATH

def run_serial():
    exec(open(RUN_PLOT_PATH).read())

def run_widget():
    exec(open(RUN_WIDGET_PATH).read())

if __name__ == '__main__':
    
    serial_process = multiprocessing.Process(target=run_serial)
    widget_process = multiprocessing.Process(target=run_widget)

    serial_process.start()
    widget_process.start()

    serial_process.join()
    widget_process.join()