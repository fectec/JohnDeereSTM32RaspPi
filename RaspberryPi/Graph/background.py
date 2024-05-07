# Game imports

import game_settings

# Definition of the Background class

class Background :

    def __init__(self, x_pos, y_pos, sprite) :

        self.x_pos = x_pos
        self.y_pos = y_pos
        
        self.sprite = sprite
        self.sprite_height = self.sprite.get_height()

    def draw(self) :
         
        game_settings.SCREEN.blit(self.sprite, (self.x_pos, self.y_pos))
        game_settings.SCREEN.blit(self.sprite, (self.x_pos, self.y_pos - self.sprite_height))

        if self.y_pos >= self.sprite_height :
            
            game_settings.SCREEN.blit(self.sprite, (self.x_pos, self.y_pos - self.sprite_height))
            self.y_pos = 0

        self.y_pos += game_settings.GAME_SPEED
