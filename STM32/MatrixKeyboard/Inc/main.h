/*
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdint.h>

/* Reset and Clock Control registers */

typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
} RCC_TypeDef;

/* General Purpose I/O registers */

typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
} GPIO_TypeDef;

/* USART Registers */

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_TypeDef;

#define RCC_BASE	0x40021000UL	// RCC base address
#define GPIOB_BASE	0x40010C00UL	// GPIO Port B base address
#define USART1_BASE	0x40013800L 	// USART1 base address

#define RCC	(( RCC_TypeDef *) RCC_BASE)
#define GPIOB	(( GPIO_TypeDef *) GPIOB_BASE)
#define USART1	(( USART_TypeDef *) USART1_BASE)

#define RCC_APB2ENR_IOPBEN	0x1UL << 3U
#define RCC_APB2ENR_USART1EN	0x1UL << 14U

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

#endif /* MAIN_H_ */
