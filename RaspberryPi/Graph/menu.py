# Game imports

import game_settings

# Overriding draw method

def menu_draw(self) :

    game_settings.SCREEN.blit(self.sprite, (self.x_pos, self.y_pos))
    game_settings.SCREEN.blit(game_settings.MENU_CHARACTER_SPRITE, game_settings.MENU_CHARACTER_POS)
    game_settings.SCREEN.blit(game_settings.MENU_TITLE_TEXT, game_settings.MENU_TITLE_TEXT_RECT)





