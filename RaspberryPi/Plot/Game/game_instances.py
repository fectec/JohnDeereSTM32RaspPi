# Library imports

from libraries import types

# Code imports

from game_settings import SCREEN_WIDTH, SCREEN_HEIGHT, MENU_START_BUTTON_SPRITE, PLAYER_INITIAL_POS, PLAYER_MOVING_SPRITES, BACKGROUND_SPRITES

from button import Button
from player import Player
from background import Background
from menu import menu_draw

# Game instances

MENU_BG = Background(0, 0, BACKGROUND_SPRITES[1])
MENU_BG.draw = types.MethodType(menu_draw, MENU_BG)

MENU_START_BUTTON = Button(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 3, MENU_START_BUTTON_SPRITE)

GAME_BG = Background(0, 0, BACKGROUND_SPRITES[0])
TRACTOR = Player(PLAYER_INITIAL_POS[0], PLAYER_INITIAL_POS[1], 0, PLAYER_MOVING_SPRITES[0])