/*
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h> 
#include <stdint.h>
#include <stddef.h>

/* Model's header file */

#include "EngTrModel.h"         
#include "rtwtypes.h"

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

/* Timer registers */
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMCR;
  volatile uint32_t DIER;
  volatile uint32_t SR;
  volatile uint32_t EGR;
  volatile uint32_t CCMR1;
  volatile uint32_t CCMR2;
  volatile uint32_t CCER;
  volatile uint32_t CNT;
  volatile uint32_t PSC;
  volatile uint32_t ARR;
  volatile uint32_t RESERVED1;
  volatile uint32_t CCR1;
  volatile uint32_t CCR2;
  volatile uint32_t CCR3;
  volatile uint32_t CCR4;
  volatile uint32_t RESERVED2;
  volatile uint32_t DCR;
  volatile uint32_t DMAR;
} TIM_TypeDef;

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
#define TIM2_BASE 	0x40000000UL 	// TIM2 timer base address
#define ADC1_BASE	0x40012400UL	// ADC1 base address
#define USART1_BASE	0x40013800UL 	// USART1 base address

#define RCC	(( RCC_TypeDef *) RCC_BASE)
#define GPIOA	(( GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB	(( GPIO_TypeDef *) GPIOB_BASE)
#define TIM2	(( TIM_TypeDef *) TIM2_BASE)
#define ADC1	(( ADC_TypeDef *) ADC1_BASE)
#define USART1	(( USART_TypeDef *) USART1_BASE)

#define RCC_APB2ENR_IOPAEN	0x1UL << 2U
#define RCC_APB2ENR_IOPBEN	0x1UL << 3U
#define RCC_APB1ENR_TIM2EN	0x1UL << 0U
#define RCC_APB2ENR_USART1EN	0x1UL << 14U
#define RCC_APB2ENR_ADC1EN	0x1UL << 9U
#define RCC_CFGR_ADCPRE		0x3UL << 14U

// PA1 (ADC1 Input)

#define GPIO_CRL_MODE0		0x3UL << 0U
#define GPIO_CRL_CNF0		0x3UL << 2U

// PA9 (USART1_TX)

#define GPIO_CRH_CNF9_0		0x1UL <<  6U
#define GPIO_CRH_MODE9		0x2UL <<  4U
#define GPIO_CRH_CNF9		0x2UL <<  6U
#define GPIO_CRH_MODE9_0	0x1UL <<  4U

// PB10 (Matrix Keyboard Row 1)

#define GPIO_CRH_CNF10		0x3UL << 10U
#define GPIO_CRH_MODE10_0	0x2UL << 8U
#define GPIO_CRH_MODE10_1	0x1UL << 8U
#define GPIO_ODR_10		0x1UL << 10U

// PB6 (Matrix Keyboard Row 2)

#define GPIO_CRL_CNF6		0x3UL << 26U
#define GPIO_CRL_MODE6_0	0x2UL << 24U
#define GPIO_CRL_MODE6_1	0x1UL << 24U
#define GPIO_ODR6		0x1UL << 6U

// PB5 (Matrix Keyboard Row 3)

#define GPIO_CRL_CNF5		0x3UL << 22U
#define GPIO_CRL_MODE5_0	0x2UL << 20U
#define GPIO_CRL_MODE5_1	0x1UL << 20U
#define GPIO_ODR5		0x1UL << 5U

// PB7 (Matrix Keyboard Row 4)

#define GPIO_CRL_CNF7		0x3UL << 30U
#define GPIO_CRL_MODE7_0	0x2UL << 28U
#define GPIO_CRL_MODE7_1	0x1UL << 28U
#define GPIO_ODR7		0x1UL << 7U

// PB1 (Matrix Keyboard Col 1)

#define GPIO_CRL_MODE1		0x3UL << 4U
#define GPIO_CRL_CNF1_0		0x1UL << 6U
#define GPIO_CRL_CNF1_1		0x2UL << 6U
#define GPIO_ODR1		0x1UL << 1U

// PB15 (Matrix Keyboard Col 2)

#define GPIO_CRH_MODE15		0x3UL << 28U
#define GPIO_CRH_CNF15_0	0x1UL << 30U
#define GPIO_CRH_CNF15_1	0x2UL << 30U
#define GPIO_ODR15		0x1UL << 15U

// PB14 (Matrix Keyboard Col 3)

#define GPIO_CRH_MODE14		0x3UL << 24U
#define GPIO_CRH_CNF14_0	0x1UL << 26U
#define GPIO_CRH_CNF14_1	0x2UL << 26U
#define GPIO_ODR14		0x1UL << 14U

// PB13 (Matrix Keyboard Col 4)

#define GPIO_CRH_MODE13		0x11UL << 20U
#define GPIO_CRH_CNF13_0	0x1UL << 22U
#define GPIO_CRH_CNF13_1	0x2UL << 22U
#define GPIO_ODR13		0x1UL << 13U

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

#endif /* MAIN_H_ */
