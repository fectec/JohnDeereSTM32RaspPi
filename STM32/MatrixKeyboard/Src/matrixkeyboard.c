/*
 * matrixkeyboard.c
 */

#include "main.h"
#include "matrixkeyboard.h"

// PB10, PB4, PB5, PB3

unsigned short int R_POSITIONS[NUMBER_OF_ELEMENTS] = {10, 4, 5, 3};

// PB1, PB15, PB14, PB13

unsigned short int C_POSITIONS[NUMBER_OF_ELEMENTS] = {1, 15, 14, 13};

unsigned short int USER_MATRIX_KEYBOARD_Read(void) {

  unsigned short int position = 0;

  for (unsigned short int i = 0; i < NUMBER_OF_ELEMENTS; i++) {

      GPIOB->BSRR = (1 << R_POSITIONS[i]);

      for (unsigned short int j = 0; j < NUMBER_OF_ELEMENTS; j++) {

	  if ((GPIOB->IDR & (1 << C_POSITIONS[j])) == 0) {
	      position = j;
	  }
      }

      GPIOB->BSRR = (1 << (R_POSITIONS[i] + 16));
  }

  return position;
}
