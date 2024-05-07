import multiprocessing

from app import run_app
from game import run_game

def main():

    # Create separate processes for the Tkinter app and the Pygame game

    app_process = multiprocessing.Process(target=run_app)
    game_process = multiprocessing.Process(target=run_game)
    
    # Start the Tkinter app process

    app_process.start()
    game_process.start()

if __name__ == "__main__":
    main()