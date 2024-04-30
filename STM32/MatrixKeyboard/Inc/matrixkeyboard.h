/*
 * matrixkeyboard.h
 */

#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H_

#define R1	0x1UL << 10 // PB10
#define R2	0x1UL << 4  // PB4
#define R3	0x1UL << 5  // PB5
#define R4	0x1UL << 3  // PB3

#define C1	0x1UL << 1  // PB1
#define C2	0x1UL << 15 // PB15
#define C3	0x1UL << 14 // PB14
#define c4	0x1UL << 13 // PB13

void USER_MATRIX_KEYBOARD_Read( void );

#endif /* MATRIXKEYBOARD_H_ */
