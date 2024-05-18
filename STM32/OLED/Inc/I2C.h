/*
 * I2C.h
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

#define RCC_APB2ENR_AFIOEN	0x1UL << 0U
#define RCC_APB1ENR_I2C1EN	0x1UL << 21U
#define RCC_APB1ENR_I2C2EN	0x1UL << 22U
#define I2C_CR1_SWRST		0x1UL << 15U
#define I2C_CR2_FREQ		0x8
#define I2C_FM			0x2D
#define I2C_SM			0xB4
#define I2C_TRISE_TRISE		0x9
#define	I2C_CR1_PE		0x1UL << 0U
#define I2C_CR1_START		0x1UL << 8U
#define I2C_SR1_SB		0x1UL << 0U
#define I2C_SR1_ADDR		0x1UL << 1U
#define I2C_SR1_TXE		0x1UL << 7U
#define I2C_CR1_STOP		0x1UL << 9U
#define I2C_1			0
#define I2C_2			1

void USER_I2C_Init( uint8_t, uint8_t );
void USER_I2C_Start( uint8_t );
void USER_I2C_Address( uint8_t, uint8_t, uint8_t );
void USER_I2C_Data( uint8_t, uint8_t );
void USER_I2C_Stop( uint8_t );
void USER_I2C_Write( uint8_t, uint8_t, uint8_t[] );

#endif /* I2C_H_ */
