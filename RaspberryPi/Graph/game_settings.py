# Library imports

import pygame as pg
import os
import types

# Code imports

import background
import menu
import button
import player
from plot_settings import PLOT_SIZE

# Start pygame module

pg.init()

# Definitions of global constants

# Screen

FPS = 60

SCREEN_WIDTH = 1280
SCREEN_HEIGHT = 720
CAPTION = 'John Deere Tractor Driving Simulator'

SCREEN = pg.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))

# Assets

BASE_PATH = os.path.dirname(os.path.realpath( __file__ ))

# Game

GAME_SPEED = 10

GAME_ICON = pg.image.load(os.path.join(BASE_PATH, "assets/Icons", "game_icon.png"))
GAME_MUSIC = os.path.join(BASE_PATH, "assets/Music", "game_music.wav")

# Menu

MENU_TITLE_SIZE = 30
MENU_TITLE_COLOR = "#367c2b"
MENU_TITLE = "JOHN DEERE TRACTOR DRIVING SIMULATOR"

MENU_TITLE_FONT = pg.font.Font(os.path.join(BASE_PATH, "assets/Menu", "arcade_font.TTF"), MENU_TITLE_SIZE)
MENU_TITLE_TEXT = MENU_TITLE_FONT.render(MENU_TITLE, True, MENU_TITLE_COLOR)
MENU_TITLE_TEXT_RECT = MENU_TITLE_TEXT.get_rect()
MENU_TITLE_TEXT_RECT.center = (SCREEN_WIDTH // 2, SCREEN_WIDTH // 12)

MENU_CHARACTER_SPRITE = pg.image.load(os.path.join(BASE_PATH, "assets/Menu", "menu_character.png"))
MENU_CHARACTER_POS = (SCREEN_WIDTH // 2 - MENU_CHARACTER_SPRITE.get_width() // 2, SCREEN_HEIGHT // 2 - MENU_CHARACTER_SPRITE.get_height() // 8)

MENU_START_BUTTON_SPRITE = pg.image.load(os.path.join(BASE_PATH, "assets/Menu", "start_button.png"))
MENU_START_BUTTON = button.Button(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 3, MENU_START_BUTTON_SPRITE)

MENU_MUSIC = os.path.join(BASE_PATH, "assets/Music", "menu_music.wav")

# Background 

BACKGROUND_SPRITES = [pg.image.load(os.path.join(BASE_PATH, "assets/Game", "game_background.jpg")),
                      pg.image.load(os.path.join(BASE_PATH, "assets/Menu", "menu_background.jpg"))]

# Player

PLAYER_MOVING_SPRITES = [pg.image.load(os.path.join(BASE_PATH, "assets/Player", "player_moving_1.png")), 
                        pg.image.load(os.path.join(BASE_PATH, "assets/Player", "player_moving_2.png"))]

PLAYER_INITIAL_POS = (SCREEN_WIDTH // 4 - PLAYER_MOVING_SPRITES[0].get_width() // 2, SCREEN_HEIGHT // 2 - PLAYER_MOVING_SPRITES[0].get_height() // 2)

PLAYER_SOUND_EFFECT = os.path.join(BASE_PATH, "assets/SoundEffects", "tractor_engine.wav")

# Plot

GAME_PLOT_SIZE = tuple(element * 100 for element in PLOT_SIZE)
PLOT_POS = (SCREEN_WIDTH // 2 , SCREEN_HEIGHT // 2 - GAME_PLOT_SIZE[1] // 2)

# Game instances

TRACTOR = player.Player(PLAYER_INITIAL_POS[0], PLAYER_INITIAL_POS[1], 0, PLAYER_MOVING_SPRITES[0])
GAME_BG = background.Background(0, 0, BACKGROUND_SPRITES[0])

MENU_BG = background.Background(0, 0, BACKGROUND_SPRITES[1])
MENU_BG.draw = types.MethodType(menu.menu_draw, MENU_BG)