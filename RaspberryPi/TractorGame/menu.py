# Library imports

import pygame as pg

# Game imports

import settings as settings

# Overriding draw method

def menu_draw(self) :

    settings.SCREEN.blit(self.sprite, (self.x_pos, self.y_pos))
    settings.SCREEN.blit(settings.MENU_CHARACTER_SPRITE, settings.MENU_CHARACTER_POS)
    settings.SCREEN.blit(settings.MENU_TITLE_TEXT, settings.MENU_TITLE_TEXT_RECT)





