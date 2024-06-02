# Library imports

from libraries import pg

# Code imports

from game_settings import SCREEN

# Definition of the Button class

class Button:
    
    """ Constructor for the Button class. It sets its image and rect attributes and
    stablishes that the button is not clicked at first."""

    def __init__(self, x, y, image):

        self.image = image
        self.rect = self.image.get_rect()
        self.rect.center = (x, y)
        self.clicked = False

    # Method that checks if the button is pressed and draws it on screen.

    def draw(self):

        pos = pg.mouse.get_pos()

        if self.rect.collidepoint(pos):
            if pg.mouse.get_pressed()[0] == 1 and self.clicked == False:

                self.clicked = True

        if pg.mouse.get_pressed()[0] == 0:
                self.clicked = False

        SCREEN.blit(self.image, (self.rect.x, self.rect.y))