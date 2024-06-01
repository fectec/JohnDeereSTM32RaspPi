/*
 * main.h
 */

#ifndef MAIN_H_
#define MAIN_H_

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

/* SysTick registers */

typedef struct
{
  volatile uint32_t CTRL;
  volatile uint32_t LOAD;
  volatile uint32_t VAL;
  volatile uint32_t CALIB;
} SYSTICK_TypeDef;

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

/* I2C registers */

typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t OAR1;
  volatile uint32_t OAR2;
  volatile uint32_t DR;
  volatile uint32_t SR1;
  volatile uint32_t SR2;
  volatile uint32_t CCR;
  volatile uint32_t TRISE;
} I2C_TypeDef;

/* Flash memory interface registers */

typedef struct
{
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t reserved;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
} FLASH_TypeDef;

// RCC

#define RCC_BASE	0x40021000UL			// RCC base address
#define RCC	(( RCC_TypeDef *) RCC_BASE)

#define RCC_APB2ENR_IOPAEN	0x1UL << 2U		// GPIO Ports Clock Enable
#define RCC_APB2ENR_IOPBEN	0x1UL << 3U
#define RCC_APB2ENR_IOPCEN	0x1UL << 4U
#define RCC_APB2ENR_IOPDEN	0x1UL << 5U
#define RCC_APB2ENR_IOPEEN	0x1UL << 6U
#define RCC_APB2ENR_IOPFEN	0x1UL << 7U
#define RCC_APB2ENR_IOPGEN	0x1UL << 8U

#define RCC_APB1ENR_TIM2EN	0x1UL << 0U		// TIM Clock Enable
#define RCC_APB1ENR_TIM3EN	0x1UL << 1U
#define RCC_APB1ENR_TIM4EN	0x1UL << 2U
#define RCC_APB1ENR_TIM5EN	0x1UL << 3U

#define RCC_APB2ENR_ADC1EN	0x1UL << 9U		// ADC Clock Enable
#define RCC_APB2ENR_ADC2EN	0x1UL << 10U
#define RCC_APB2ENR_ADC3EN	0x1UL << 15U
#define RCC_CFGR_ADCPRE		0x3UL << 14U

#define RCC_APB2ENR_USART1EN	0x1UL << 14U		// USART Clock Enable
#define RCC_APB1ENR_USART2EN	0x1UL << 17U
#define RCC_APB1ENR_USART3EN	0x1UL << 18U

#define RCC_APB1ENR_I2C1EN	0x1UL << 21U		// I2C Clock Enable
#define RCC_APB1ENR_I2C2EN	0x1UL << 22U
#define RCC_APB2ENR_AFIOEN	0x1UL << 0U

// GPIO

#define GPIOA_BASE	0x40010800UL			// GPIO Port A base address
#define GPIOB_BASE	0x40010C00UL			// GPIO Port B base address
#define GPIOC_BASE	0x40011000UL			// GPIO Port C base address
#define GPIOD_BASE	0x40011400UL			// GPIO Port D base address
#define GPIOE_BASE	0x40011800UL			// GPIO Port E base address
#define GPIOF_BASE	0x40011C00UL			// GPIO Port F base address
#define GPIOG_BASE	0x40012000UL			// GPIO Port G base address

#define GPIOA	(( GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB	(( GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC	(( GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD	(( GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE	(( GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF	(( GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG	(( GPIO_TypeDef *) GPIOG_BASE)

// TIM

#define TIM2_BASE	0x40000000UL 			// TIM2 timer base address
#define TIM3_BASE	0x40000400UL 			// TIM3 timer base address
#define TIM4_BASE	0x40000800UL 			// TIM4 timer base address
#define TIM5_BASE	0x40000C00UL 			// TIM5 timer base address

#define TIM2	(( TIM_TypeDef *) TIM2_BASE)
#define TIM3	(( TIM_TypeDef *) TIM3_BASE)
#define TIM4	(( TIM_TypeDef *) TIM4_BASE)
#define TIM5	(( TIM_TypeDef *) TIM5_BASE)

// SYSTICK

#define SYSTICK_BASE	0xE000E010UL			// SysTick base address
#define SYSTICK (( SYSTICK_TypeDef *) SYSTICK_BASE)

// ADC

#define ADC1_BASE	0x40012400UL			// ADC1 base address
#define ADC2_BASE	0x40012800UL			// ADC2 base address
#define ADC3_BASE	0x40013C00UL			// ADC3 base address

#define ADC1	(( ADC_TypeDef *) ADC1_BASE)
#define ADC2	(( ADC_TypeDef *) ADC2_BASE)
#define ADC3	(( ADC_TypeDef *) ADC3_BASE)

// USART

#define USART1_BASE	0x40013800UL 			// USART1 base address
#define USART2_BASE	0x40004400UL 			// USART2 base address
#define USART3_BASE	0x40004800UL 			// USART3 base address

#define USART1	(( USART_TypeDef *) USART1_BASE)
#define USART2	(( USART_TypeDef *) USART2_BASE)
#define USART3	(( USART_TypeDef *) USART3_BASE)

// I2C

#define I2C1_BASE	0x40005400UL			// I2C1 base address
#define I2C2_BASE	0x40005800UL			// I2C2 base address

#define I2C1	(( I2C_TypeDef *) I2C1_BASE)
#define I2C2	(( I2C_TypeDef *) I2C2_BASE)

// FLASH

#define FLASH_BASE	0x40022000UL			// FLASH base address
#define FLASH	(( FLASH_TypeDef *) FLASH_BASE )

// Functions

void USER_RCC_ClockEnable( void );

#endif /* MAIN_H_ */
