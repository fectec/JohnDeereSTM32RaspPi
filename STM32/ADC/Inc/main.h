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

/* ADC registers */

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
} ADC_TypeDef;

#define RCC_BASE	0x40021000UL //	RCC base address
#define GPIOA_BASE	0x40010800UL //	GPIO Port A base address
#define ADC1_BASE	0x40010800UL //	ADCX base address

#define RCC		(( RCC_TypeDef *) RCC_BASE)
#define GPIOA	(( GPIO_TypeDef *) GPIOA_BASE)
#define ADC1	(( ADC_TypeDef *) ADC1_BASE)

#define RCC_APB2ENR_IOPAEN		( 0x1UL << 2U )

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

#endif /* MAIN_H_ */
