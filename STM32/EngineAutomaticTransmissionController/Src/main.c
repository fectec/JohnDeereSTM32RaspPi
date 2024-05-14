/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "main.h"
#include "timer.h"
#include "ADC.h"
#include "uart.h"
#include "matrixkeyboard.h"
#include "lcd.h"

// ADC1

uint16_t conversionData = 0;
float voltageValue = 0, normalizedVoltageValue = 0;

// Matrix Keyboard

char selectedKey;
char action = 'F';
float keyBrakeTorque;

// LCD

uint8_t col = 16;
char FirstLine_LCD_MSG[LCD_CHARS + 1];
char SecondLine_LCD_MSG[LCD_CHARS + 1];

/* Function prototypes */

void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

int main( void )
{

  EngTrModel_initialize();

  USER_RCC_ClockEnable();
  USER_GPIO_Init();
  USER_TIM2_Init( );
  USER_ADC1_Init();
  USER_USART1_Init();
  LCD_Init();

  /* Loop forever */

  for(;;)
  {

    // ADC1

    conversionData = USER_ADC1_Convert();
    voltageValue = 0.00080586 * conversionData;

    // Matrix Keyboard

    selectedKey = USER_MATRIX_KEYBOARD_Read();

    // printf("%f_%c\n\r", voltageValue, selectedKey); // Debug ADC1 and Matrix Keyboard

    if(selectedKey == '5')
    {
	keyBrakeTorque = 100.0;
	action = 'B';

    }
    else if(selectedKey == '4' || selectedKey == '6')
    {
	voltageValue -= 1;

	if(selectedKey == '4')
	{
	    action = 'R';
	}
	else
	{
	    action = 'L';
	}
    }
    else
    {
	keyBrakeTorque = 0.0;
	action = 'F';
    }

    normalizedVoltageValue = scaleVoltageValue(voltageValue, 0, 3.3);

    // printf("%f_%f\n\r", normalizedVoltageValue, keyBrakeTorque); // Debug normalizedVoltageValue and keyBrakeTorque

    // Update the values for the Throttle and Brake commands

    EngTrModel_U.Throttle = normalizedVoltageValue;
    EngTrModel_U.BrakeTorque = keyBrakeTorque;

    // Update the values into the vehicle model

    EngTrModel_step();

    // Send the output values

    printf("%f,%f,%f\n\r", EngTrModel_Y.EngineSpeed, EngTrModel_Y.VehicleSpeed, EngTrModel_Y.Gear);

    USER_TIM2_Delay(TIM_PSC_40MS, TIM_CNT_40MS);		// 40 ms delay

    // Extract the whole and decimal parts for Engine Speed and Vehicle Speed, and cast them alongside Gear to integers

    int EngineSpeedWhole = (int)(EngTrModel_Y.EngineSpeed);
    int EngineSpeedDecimal = (int)((EngTrModel_Y.EngineSpeed - EngineSpeedWhole) * 100);

    int VehicleSpeedWhole = (int)(EngTrModel_Y.VehicleSpeed);
    int VehicleSpeedDecimal = (int)((EngTrModel_Y.VehicleSpeed - VehicleSpeedWhole) * 100);

    int GearWhole = (int) (EngTrModel_Y.Gear);

    // Write the messages to send to the LCD

    snprintf(FirstLine_LCD_MSG, sizeof(FirstLine_LCD_MSG), "E:%04d.%02d G:%01d  %c", EngineSpeedWhole, EngineSpeedDecimal, GearWhole, action);
    snprintf(SecondLine_LCD_MSG, sizeof(SecondLine_LCD_MSG), "V:%03d.%02d        ", VehicleSpeedWhole, VehicleSpeedDecimal);

    // Display values on the LCD

    LCD_Set_Cursor( 1, 1 );
    LCD_Put_Str(FirstLine_LCD_MSG);
    LCD_Set_Cursor( 2, 1 );
    LCD_Put_Str(SecondLine_LCD_MSG);

    USER_TIM2_Delay(TIM_PSC_200MS, TIM_CNT_200MS);		// 200 ms delay

  }

}

void USER_RCC_ClockEnable( void )
{

  // RCC_APB2ENR modified to IO port A clock enable

  RCC->APB2ENR |= 	RCC_APB2ENR_IOPAEN;	// To set IOPAEN bit

  // RCC_APB2ENR modified to IO port B clock enable

  RCC->APB2ENR |= 	RCC_APB2ENR_IOPBEN;	// To set IOPBEN bit

  // RCC_APB2ENR modified to IO port C clock enable

  RCC->APB2ENR	|=	RCC_APB2ENR_IOPCEN;	// To set IOPCEN bit

  // RCC_APB1ENR modified to enable the clock for TIM2

  RCC->APB1ENR |= 	RCC_APB1ENR_TIM2EN;	// To set TIM2EN bit

  // RCC_APB2ENR and RCC_CFGR modified to enable and adjust the clock for ADC1

  RCC->APB2ENR	|=	RCC_APB2ENR_ADC1EN;	// Enable clock for ADC1
  RCC->CFGR	|=	RCC_CFGR_ADCPRE;        // Adjust ADC input clock

  // RCC_APB2ENR modified to enable the clock for USART1

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 	// To set USART1EN bit

  /* System Clock (SYSCLK) configuration for 64 MHz */

  // Two wait states latency, if SYSCLK > 48 MHz

  FLASH->ACR	&=	~( 0x5UL << 0U );	
  FLASH->ACR	|=	( 0x2UL << 0U );	
  
  // PLL HSI clock /2 selected as PLL input clock
  
  RCC->CFGR	&=	~( 0x1UL << 16U )
		&	~( 0x7UL << 11U )	// APB2 pre-scaler /1
		&	~( 0x3UL << 8U )        // APB1 pre-scaler /2 (APB1 must not exceed 36 MHz)
		&	~( 0xFUL << 4U );	// AHB pre-scaler /1

  // PLL input clock x 16 (PLLMUL bits)

  RCC->CFGR	|=	( 0xFUL << 18U )	
		|	( 0X4UL << 8U );	// APB1 pre-scaler /2
  RCC->CR	|=	( 0x1UL << 24U );	// PLL2 ON

  // Wait until PLL is locked

  while( !(RCC->CR & ~( 0x1UL << 25U )));

  // PLL used as system clock (SW bits)

  RCC->CFGR	&=	~( 0x1UL << 0U );
  RCC->CFGR	|=	( 0x2UL << 0U );

  // Wait until PLL is switched

  while( 0x8UL != ( RCC->CFGR & 0xCUL ));

}

void USER_GPIO_Init( void )
{
  // Pin PA0 as analog input

  GPIOA->CRL	&=	~( GPIO_CRL_MODE0 )
		&	~( GPIO_CRL_CNF0 );

  // Pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz

  GPIOA->CRH	&=	~( GPIO_CRH_CNF9_0 )
  		&	~( GPIO_CRH_MODE9 );

  GPIOA->CRH	|=	 ( GPIO_CRH_CNF9 )
  		|	 ( GPIO_CRH_MODE9_0 );
   		
  // Pin PB10 (Row 1) as output

  GPIOB->CRH	&=	~( GPIO_CRH_CNF10 )
		&	~( GPIO_CRH_MODE10_0 );

  GPIOB->CRH 	|=	 ( GPIO_CRH_MODE10_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR_10 );

  // Pin PB6 (Row 2) as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF6 )
		&	~( GPIO_CRL_MODE6_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE6_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR6 );

  // Pin PB5 (Row 3) as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF5 )
		&	~( GPIO_CRL_MODE5_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE5_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR5 );

  // Pin PB7 (Row 4) as output

  GPIOB->CRL	&=	~( GPIO_CRL_CNF7 )
		&	~( GPIO_CRL_MODE7_0 );

  GPIOB->CRL 	|=	 ( GPIO_CRL_MODE7_1 );
  GPIOB->ODR 	|=	 ( GPIO_ODR7 );

  // Pin PB1 (Col 1) as input pull up

  GPIOB->CRL	&=	~( GPIO_CRL_MODE1 )
		&	~( GPIO_CRL_CNF1_0 );

  GPIOB->CRL	|= 	 ( GPIO_CRL_CNF1_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR1 );

  // Pin PB15 (Col 2) as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE15 )
		&	~( GPIO_CRH_CNF15_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF15_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR15 );

  // Pin PB14 (Col 3) as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE14 )
		&	~( GPIO_CRH_CNF14_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF14_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR14 );

  // Pin PB13 (Col 4) as input pull up

  GPIOB->CRH	&=	~( GPIO_CRH_MODE13 )
		&	~( GPIO_CRH_CNF13_0 );

  GPIOB->CRH	|= 	 ( GPIO_CRH_CNF13_1 );
  GPIOB->ODR	|=	 ( GPIO_ODR13 );
}
