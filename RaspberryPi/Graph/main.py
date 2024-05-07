import threading

from app import run_app
from game import run_game

def main() :

    app_thread = threading.Thread(target=run_app)
    app_thread.start()
    
    run_game()

if __name__ == "__main__":
    main()