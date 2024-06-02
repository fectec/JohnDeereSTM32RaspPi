# Library imports

from libraries import FigureCanvasAgg

# Code imports

import game_settings as set
import game_instances as ins

from plot_serial import run_plot
#from plot_random import run_plot    # Uncomment this and comment on the up line if you want to run with random data

# Menu

def menu() :

    run = True
    clock = set.pg.time.Clock()

    set.pg.mixer.Channel(1).play(set.pg.mixer.Sound(set.MENU_MUSIC), loops=-1)

    while run :
        
        # Limit game FPS

        clock.tick(set.FPS)

        # If close window button is pressed, execution stops

        for event in set.pg.event.get() :
            if event.type == set.pg.QUIT :
                set.sys.exit()
        
        if ins.MENU_START_BUTTON.clicked == True :
            set.SCREEN.fill("black")
            game()
        
        ins.MENU_BG.draw()
        ins.MENU_START_BUTTON.draw()

        set.pg.display.update()

# Game loop

def game() :

    run = True
    clock = set.pg.time.Clock()

    # Fetch fig from the plot module

    fig = run_plot()

    # Transform fig into canvas and get its raw data

    canvas = FigureCanvasAgg(fig)
    size = set.GAME_PLOT_SIZE
    renderer = canvas.get_renderer()
    raw_data = renderer.buffer_rgba()

    set.pg.mixer.Channel(0).play(set.pg.mixer.Sound(set.PLAYER_SOUND_EFFECT), loops=-1, fade_ms=0)
    set.pg.mixer.Channel(0).set_volume(0.5)

    set.pg.mixer.Channel(1).play(set.pg.mixer.Sound(set.GAME_MUSIC), loops=-1)
    set.pg.mixer.Channel(1).set_volume(1.0)

    while run :
        
        # Limit game FPS

        clock.tick(set.FPS)

        # If close window button is pressed, execution stops

        for event in set.pg.event.get() :
            if event.type == set.pg.QUIT :
                set.sys.exit()

        # Draw background and tractor

        ins.GAME_BG.draw()
        ins.TRACTOR.draw()

        # Fetch a new fig from the plot module

        fig = run_plot()

        # Redraw canvas

        canvas.draw()

        # Transform canvas' raw data into surface

        surf = set.pg.image.frombuffer(raw_data.tobytes(), size, "RGBA")

        # Draw plot
        
        set.SCREEN.blit(surf, set.PLOT_POS)
    
        # Update display

        set.pg.display.update()

def run_game() :

    # Set game window

    set.pg.display.set_caption(set.CAPTION)
    set.pg.display.set_icon(set.GAME_ICON)

    # Call menu method

    menu()

    # Quit game

    set.pg.quit()

if __name__ == "__main__":
    run_game()