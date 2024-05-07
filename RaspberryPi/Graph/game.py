# Library imports

import sys

# Game imports

import game_settings

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

    game_settings.pg.mixer.Channel(1).play(pg.mixer.Sound(game_settings.GAME_MUSIC))

    while run :
        
        # Limit game FPS

        clock.tick(game_settings.FPS)

        # If close window button is pressed, execution stops

        for event in game_settings.pg.event.get() :
            if event.type == game_settings.pg.QUIT :
                sys.exit()
        
        game_settings.GAME_BG.draw()
        game_settings.TRACTOR.draw()

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