/*
 * matrixkeyboard.c
 */

#include "main.h"
#include "matrixkeyboard.h"

// PB10, PB4, PB5, PB3

unsigned short int R_POSITIONS[NUMBER_OF_ELEMENTS] = {10, 6, 5, 7};

// PB1, PB15, PB14, PB13

unsigned short int C_POSITIONS[NUMBER_OF_ELEMENTS] = {1, 15, 14, 13};

char keys[NUMBER_OF_ELEMENTS][NUMBER_OF_ELEMENTS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

char USER_MATRIX_KEYBOARD_Read( void ) {

  char selectedKey;

  for (unsigned short int i = 0; i < NUMBER_OF_ELEMENTS; i++) {

      GPIOB->BSRR = (1 << (R_POSITIONS[i] + 16));

      for (unsigned short int j = 0; j < NUMBER_OF_ELEMENTS; j++) {

	  if ((GPIOB->IDR & (1 << C_POSITIONS[j])) == 0) {
	      selectedKey = keys[i][j];
	  }
      }

      GPIOB->BSRR = (1 << R_POSITIONS[i]);
  }

  return selectedKey;
}
