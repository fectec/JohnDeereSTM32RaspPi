# Code imports

from game_settings import SCREEN, MENU_CHARACTER_SPRITE, MENU_CHARACTER_POS, MENU_TITLE_TEXT, MENU_TITLE_TEXT_RECT

# Overriding draw method

def menu_draw(self) :

    SCREEN.blit(self.sprite, (self.x_pos, self.y_pos))
    SCREEN.blit(MENU_CHARACTER_SPRITE, MENU_CHARACTER_POS)
    SCREEN.blit(MENU_TITLE_TEXT, MENU_TITLE_TEXT_RECT)