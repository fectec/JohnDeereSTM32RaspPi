/*
 * OLED.h
 */

#ifndef OLED_H_
#define OLED_H_

#define OLED_PRIMARY_ADDRESS	0x78
#define OLED_SECONDARY_ADDRESS	0x7A

#include <stdint.h>

void USER_OLED_SendCMD_1_Byte( uint8_t I2C, uint8_t data );
void USER_OLED_SendCMD_2_Byte( uint8_t, uint8_t[] );
void USER_OLED_Init( uint8_t );

#endif /* OLED_H_ */
