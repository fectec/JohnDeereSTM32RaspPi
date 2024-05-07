# Game imports

import game_settings

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

        pos = game_settings.pg.mouse.get_pos()

        if self.rect.collidepoint(pos):
            if game_settings.pg.mouse.get_pressed()[0] == 1 and self.clicked == False:

                self.clicked = True

        if game_settings.pg.mouse.get_pressed()[0] == 0:
                self.clicked = False

        game_settings.SCREEN.blit(self.image, (self.rect.x, self.rect.y))