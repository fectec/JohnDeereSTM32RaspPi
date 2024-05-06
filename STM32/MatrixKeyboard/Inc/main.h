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
#define GPIOA_BASE	0x40010800UL	// GPIO Port A base address
#define GPIOB_BASE	0x40010C00UL	// GPIO Port B base address
#define USART1_BASE	0x40013800L 	// USART1 base address

#define RCC	(( RCC_TypeDef *) RCC_BASE)
#define GPIOA	(( GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB	(( GPIO_TypeDef *) GPIOB_BASE)
#define USART1	(( USART_TypeDef *) USART1_BASE)

#define RCC_APB2ENR_IOPAEN	0x1UL << 2U
#define RCC_APB2ENR_IOPBEN	0x1UL << 3U
#define RCC_APB2ENR_USART1EN	0x1UL << 14U

// PB1

#define GPIO_CRL_MODE1		0x3UL << 4U
#define GPIO_CRL_CNF1_0		0x1UL << 6U
#define GPIO_CRL_CNF1_1		0x2UL << 6U
#define GPIO_ODR1		0x1UL << 1U

// PB15

#define GPIO_CRH_MODE15		0x3UL << 28U
#define GPIO_CRH_CNF15_0	0x1UL << 30U
#define GPIO_CRH_CNF15_1	0x2UL << 30U
#define GPIO_ODR15		0x1UL << 15U

// PB14

#define GPIO_CRH_MODE14		0x3UL << 24U
#define GPIO_CRH_CNF14_0	0x1UL << 26U
#define GPIO_CRH_CNF14_1	0x2UL << 26U
#define GPIO_ODR14		0x1UL << 14U

// PB13

#define GPIO_CRH_MODE13		0x11UL << 20U
#define GPIO_CRH_CNF13_0	0x1UL << 22U
#define GPIO_CRH_CNF13_1	0x2UL << 22U
#define GPIO_ODR13		0x1UL << 13U

// PB10

#define GPIO_CRH_CNF10		0x3UL << 10U
#define GPIO_CRH_MODE10_0	0x2UL << 8U
#define GPIO_CRH_MODE10_1	0x1UL << 8U
#define GPIO_ODR_10		0x1UL << 10U

// PB6

#define GPIO_CRL_CNF6		0x3UL << 26U
#define GPIO_CRL_MODE6_0	0x2UL << 24U
#define GPIO_CRL_MODE6_1	0x1UL << 24U
#define GPIO_ODR6		0x1UL << 6U

// PB5

#define GPIO_CRL_CNF5		0x3UL << 22U
#define GPIO_CRL_MODE5_0	0x2UL << 20U
#define GPIO_CRL_MODE5_1	0x1UL << 20U
#define GPIO_ODR5		0x1UL << 5U

// PB7

#define GPIO_CRL_CNF7		0x3UL << 30U
#define GPIO_CRL_MODE7_0	0x2UL << 28U
#define GPIO_CRL_MODE7_1	0x1UL << 28U
#define GPIO_ODR7		0x1UL << 7U

// PA9

#define GPIO_CRH_CNF9_0		0x1UL <<  6U
#define GPIO_CRH_MODE9		0x2UL <<  4U
#define GPIO_CRH_CNF9		0x2UL <<  6U
#define GPIO_CRH_MODE9_0	0x1UL <<  4U

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

#endif /* MAIN_H_ */
