# Code imports

from game_settings import SCREEN

# Definition of the Player class

class Player :

    def __init__(self, x_pos, y_pos, speed, sprite) :

        self.speed = speed
        self.sprite = sprite

        self.rect = self.sprite.get_rect()
        self.rect.x = x_pos
        self.rect.y = y_pos

    def draw(self) :
         
        SCREEN.blit(self.sprite, (self.rect.x, self.rect.y))