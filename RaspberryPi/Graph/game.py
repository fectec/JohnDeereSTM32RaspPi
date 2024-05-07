# Library imports

import pygame as pg
import sys

# Game imports

import game_settings

# Menu

def menu() :

    run = True
    clock = pg.time.Clock()

    pg.mixer.Channel(1).play(pg.mixer.Sound(game_settings.MENU_MUSIC))

    while run :
        
        # Limit game FPS

        clock.tick(game_settings.FPS)

        # If close window button is pressed, execution stops

        for event in pg.event.get() :
            if event.type == pg.QUIT :
                sys.exit()
        
        if game_settings.MENU_START_BUTTON.clicked == True :
            game_settings.SCREEN.fill("black")
            game()
        
        game_settings.MENU_BG.draw()
        game_settings.MENU_START_BUTTON.draw()

        pg.display.update()

# Game loop

def game() :

    run = True
    clock = pg.time.Clock()

    pg.mixer.Channel(1).play(pg.mixer.Sound(game_settings.GAME_MUSIC))

    while run :
        
        # Limit game FPS

        clock.tick(game_settings.FPS)

        # If close window button is pressed, execution stops

        for event in pg.event.get() :
            if event.type == pg.QUIT :
                sys.exit()
        
        game_settings.GAME_BG.draw()
        game_settings.TRACTOR.draw()

        pg.display.update()

def run_game() :

    # Start pygame module

    pg.init()

    # Set game window

    pg.display.set_caption(game_settings.CAPTION)
    pg.display.set_icon(game_settings.GAME_ICON)

    # Call menu method

    menu()

    # Quit game

    pg.quit()

if __name__ == "__main__":
    run_game()