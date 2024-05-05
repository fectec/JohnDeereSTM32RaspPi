/*
 * matrixkeyboard.h
 */

#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H_

#define NUMBER_OF_ELEMENTS 4

extern unsigned short int R_POSITIONS[NUMBER_OF_ELEMENTS];
extern unsigned short int C_POSITIONS[NUMBER_OF_ELEMENTS];

unsigned short int USER_MATRIX_KEYBOARD_Read(void);

#endif /* MATRIXKEYBOARD_H_ */
