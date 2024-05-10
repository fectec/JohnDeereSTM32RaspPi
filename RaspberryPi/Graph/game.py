# Library imports

import sys
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg

# Code imports

import game_settings
from plot import run_plot

#from plot_random import run_plot # Uncomment this and comment on the up line if you want to run with random data

# Menu

def menu() :

    run = True
    clock = game_settings.pg.time.Clock()

    game_settings.pg.mixer.Channel(1).play(game_settings.pg.mixer.Sound(game_settings.MENU_MUSIC), loops=-1)

    while run :
        
        # Limit game FPS

        clock.tick(game_settings.FPS)

        # If close window button is pressed, execution stops

        for event in game_settings.pg.event.get() :
            if event.type == game_settings.pg.QUIT :
                sys.exit()
        
        if game_settings.MENU_START_BUTTON.clicked == True :
            game_settings.SCREEN.fill("black")
            game()
        
        game_settings.MENU_BG.draw()
        game_settings.MENU_START_BUTTON.draw()

        game_settings.pg.display.update()

# Game loop

def game() :

    run = True
    clock = game_settings.pg.time.Clock()

    # Fetch fig from the plot module

    fig = run_plot()

    # Transform fig into canvas and get its raw data

    canvas = FigureCanvasAgg(fig)
    size = game_settings.GAME_PLOT_SIZE
    renderer = canvas.get_renderer()
    raw_data = renderer.buffer_rgba()

    game_settings.pg.mixer.Channel(0).play(game_settings.pg.mixer.Sound(game_settings.PLAYER_SOUND_EFFECT), loops=-1, fade_ms=0)
    game_settings.pg.mixer.Channel(0).set_volume(0.5)

    game_settings.pg.mixer.Channel(1).play(game_settings.pg.mixer.Sound(game_settings.GAME_MUSIC), loops=-1)
    game_settings.pg.mixer.Channel(1).set_volume(1.0)

    while run :
        
        # Limit game FPS

        clock.tick(game_settings.FPS)

        # If close window button is pressed, execution stops

        for event in game_settings.pg.event.get() :
            if event.type == game_settings.pg.QUIT :
                sys.exit()

        # Draw background and tractor

        game_settings.GAME_BG.draw()
        game_settings.TRACTOR.draw()

        # Fetch a new fig from the plot module

        fig = run_plot()

        # Redraw canvas

        canvas.draw()

        # Transform canvas' raw data into surface

        surf = game_settings.pg.image.frombuffer(raw_data.tobytes(), size, "RGBA")

        # Draw plot
        
        game_settings.SCREEN.blit(surf, game_settings.PLOT_POS)
    
        # Update display

        game_settings.pg.display.update()

def run_game() :

    # Set game window

    game_settings.pg.display.set_caption(game_settings.CAPTION)
    game_settings.pg.display.set_icon(game_settings.GAME_ICON)

    # Call menu method

    menu()

    # Quit game

    game_settings.pg.quit()

if __name__ == "__main__":
    run_game()
