# Library imports

import sys
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg

# Code imports

import game_settings
from plot_random import run_plot

# Menu

def menu() :

    run = True
    clock = game_settings.pg.time.Clock()

    game_settings.pg.mixer.Channel(1).play(game_settings.pg.mixer.Sound(game_settings.MENU_MUSIC))

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
    
    # Frame variable for plotting

    frame = 0

    # Fetch fig from the plot module

    fig = run_plot(frame)

    # Transform fig into canvas and get its raw data

    canvas = FigureCanvasAgg(fig)
    size = game_settings.GAME_PLOT_SIZE
    renderer = canvas.get_renderer()
    raw_data = renderer.buffer_rgba()

    game_settings.pg.mixer.Channel(1).play(game_settings.pg.mixer.Sound(game_settings.GAME_MUSIC))

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

        fig = run_plot(frame)

        # Redraw canvas

        canvas.draw()

        # Transform canvas' raw data into surface

        surf = game_settings.pg.image.frombuffer(raw_data.tobytes(), size, "RGBA")

        # Draw plot
        
        game_settings.SCREEN.blit(surf, game_settings.PLOT_POS)
    
        # Update display

        game_settings.pg.display.update()

        # Increment frame counter by one

        frame += 1

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