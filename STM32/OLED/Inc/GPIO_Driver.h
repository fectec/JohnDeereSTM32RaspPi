/*
 * GPIO_Driver.h
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

// Ports

#define PORTA	0
#define PORTB	1
#define PORTC	2
#define PORTD	3
#define PORTE	4
#define PORTF	5
#define PORTG	6

// Directions

#define	INP	0		// Input
#define OUT_10	1		// Maximum output speed 10 MHz
#define OUT_2	2		// Maximum output speed 2 MHz
#define OUT_50	3		// Maximum output speed 50 MHz

// Direction options for input

#define	INP_AN	0		// Analog input
#define	INP_F	1		// Input floating
#define	INP_PP	2		// Input pull-down / pull-up

// Direction options for output

#define OUT_GP_PP	0	// General purpose output - Push-pull
#define OUT_GP_OD	1	// General purpose output - Open-drain
#define OUT_AF_PP	2	// Alternate Function output - Push-pull
#define OUT_AF_OD	3	// Alternate Function output - Open-drain

void USER_GPIO_Define( uint8_t, uint8_t, uint8_t, uint8_t );
uint8_t USER_GPIO_Read( uint8_t, uint8_t );
void USER_GPIO_Write( uint8_t, uint8_t, uint8_t );
void USER_GPIO_Toggle( uint8_t, uint8_t );

#endif /* GPIO_DRIVER_H_ */
