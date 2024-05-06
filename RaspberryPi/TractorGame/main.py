# Library imports

import pygame as pg
import sys

# Game imports

import settings as settings

# Start pygame module

pg.init()

# Set game window

pg.display.set_caption(settings.CAPTION)
pg.display.set_icon(settings.GAME_ICON)

# Game loop 

def menu() :

    run = True
    clock = pg.time.Clock()

    pg.mixer.Channel(1).play(pg.mixer.Sound(settings.MENU_MUSIC))

    while run :
        
        # Limit game FPS

        clock.tick(settings.FPS)

        # If close window button is pressed, execution stops

        for event in pg.event.get() :
            if event.type == pg.QUIT :
                sys.exit()
        
        if settings.MENU_START_BUTTON.clicked == True :
            settings.SCREEN.fill("black")
            game()
        
        settings.MENU_BG.draw()
        settings.MENU_START_BUTTON.draw()

        pg.display.update()

def game() :

    run = True
    clock = pg.time.Clock()

    pg.mixer.Channel(1).play(pg.mixer.Sound(settings.GAME_MUSIC))

    while run :
        
        # Limit game FPS

        clock.tick(settings.FPS)

        # If close window button is pressed, execution stops

        for event in pg.event.get() :
            if event.type == pg.QUIT :
                sys.exit()
        
        settings.GAME_BG.draw()
        settings.TRACTOR.draw()

        pg.display.update()

menu()
pg.quit()