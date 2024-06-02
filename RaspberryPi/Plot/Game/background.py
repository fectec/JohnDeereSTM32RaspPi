# Code imports

from game_settings import SCREEN, GAME_SPEED

# Definition of the Background class

class Background :

    def __init__(self, x_pos, y_pos, sprite) :

        self.x_pos = x_pos
        self.y_pos = y_pos
        
        self.sprite = sprite
        self.sprite_height = self.sprite.get_height()

    def draw(self) :
         
        SCREEN.blit(self.sprite, (self.x_pos, self.y_pos))
        SCREEN.blit(self.sprite, (self.x_pos, self.y_pos - self.sprite_height))

        if self.y_pos >= self.sprite_height :
            
            SCREEN.blit(self.sprite, (self.x_pos, self.y_pos - self.sprite_height))
            self.y_pos = 0

        self.y_pos += GAME_SPEED