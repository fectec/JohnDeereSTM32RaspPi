/*
 * main.c
 */

/* Libraries, Definitions and Global Declarations */

#include "libraries.h"
#include "main.h"
#include "GPIO.h"
#include "TIMER.h"
#include "SYSTICK.h"
#include "ADC.h"
#include "UART.h"
#include "I2C.h"
#include "MATRIX_KEYPAD.h"
#include "LCD.h"
#include "LEDS.h"
#include "OLED.h"
#include "PWM.h"

/* Model's header file */

#include "EngTrModel.h"
#include "rtwtypes.h"

// ADC

uint16_t conversionData = 0;
float voltageValue = 0.0, potentiometerThrottle = 0.0;

// Matrix keypad

char selectedKey = 'N';
float keyBrakeTorque = 0.0;

// LCD

char FirstLine_LCD_MSG[LCD_CHARS + 1];
char SecondLine_LCD_MSG[LCD_CHARS + 1];

// OLED

char oled_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS];
char OLED_MSGS[OLED_MSGS_NUMBER][OLED_SCREEN_COLUMNS];

/* Main function */

int main( void )
{
  USER_SYSCLK_Configuration();

  USER_TIM_Init( TIM_2 );
  USER_TIM_Init( TIM_3 );

  USER_SYSTICK_Init();
  USER_ADC_Init( ADC_1 );
  USER_USART_Init( USART_1 );
  USER_MATRIX_KEYPAD_Init();
  USER_LEDS_Init();
  //USER_LCD_Init();

  USER_OLED_Init_64( I2C_2 );
  USER_OLED_Animation( I2C_2, oled_buffer );

  USER_PWM_Init();

  EngTrModel_initialize();

  /* Loop forever */

  for(;;)
  {
    /* Read the ADC conversion, convert it to a voltage value,
     * and normalize it to within the range accepted by the model.
     */

    conversionData = USER_ADC_Convert( ADC_1 );
    voltageValue = 0.00080586 * conversionData;
    potentiometerThrottle = scaleVoltageValue( voltageValue, 0, 3.3 );

    /* Read the matrix keyboard and
     * adapt the brake value, LEDs states and
     * micro servo direction
     * based on the selected key.
     */

    selectedKey = USER_MATRIX_KEYPAD_Read();

    if(selectedKey == '5')
    {
      keyBrakeTorque = 100.0;

      USER_TIM_Delay( TIM_3, TIM_PSC_200MS, TIM_CNT_200MS );
    }
    else if(selectedKey == '4' || selectedKey == '6')
    {
      keyBrakeTorque = 50.0;

      if(selectedKey == '4')
      {
	  USER_GPIO_Write( PORTC, 2, 1 );
	  USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_12_5 );
      }
      else
      {
	  USER_GPIO_Write( PORTC, 3, 1 );
	  USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_2_5 );
      }
    }
    else
    {
      keyBrakeTorque = 0.0;

      USER_GPIO_Write( PORTC, 2, 0 );
      USER_GPIO_Write( PORTC, 3, 0 );

      USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_7_5 );
    }

    /* Feed the model with the normalized voltage
     * or throttle value and the brake value, take a step and
     * sanitize the output values.
     */

    EngTrModel_U.Throttle = potentiometerThrottle;
    EngTrModel_U.BrakeTorque = keyBrakeTorque;

    EngTrModel_step();

    if(isnan(EngTrModel_Y.VehicleSpeed) || EngTrModel_Y.VehicleSpeed < 0 || EngTrModel_Y.VehicleSpeed > 200)
    {
      EngTrModel_Y.VehicleSpeed = 0.0;
    }

    if(isnan(EngTrModel_Y.EngineSpeed) || EngTrModel_Y.EngineSpeed < 0)
    {
      EngTrModel_Y.EngineSpeed = 0.0;
    }

    if(isnan(EngTrModel_Y.Gear) || EngTrModel_Y.Gear < 0)
    {
      EngTrModel_Y.Gear = 0.0;
    }

    /* Send via UART the output values of the model,
     * subsequently received by the Raspberry Pi.
     */

    printf("%f,%f,%f,%f,%f\n\r", potentiometerThrottle, keyBrakeTorque, EngTrModel_Y.VehicleSpeed, EngTrModel_Y.EngineSpeed, EngTrModel_Y.Gear);

    /* Properly format the model output data
     * and display it on the LCD.
     */

    /* Extract the whole and decimal parts for Throttle,
     * Engine Speed and Vehicle Speed, and cast them
     * alongside Brake and Gear to integers.
     */

    int ThrottleWhole = (int) ( potentiometerThrottle );
    int ThrottleDecimal = (int) ( ( potentiometerThrottle - ThrottleWhole ) * 100 );

    int EngineSpeedWhole = (int)( EngTrModel_Y.EngineSpeed );
    int EngineSpeedDecimal = (int)( ( EngTrModel_Y.EngineSpeed - EngineSpeedWhole ) * 100 );

    int VehicleSpeedWhole = (int)( EngTrModel_Y.VehicleSpeed );
    int VehicleSpeedDecimal = (int)( ( EngTrModel_Y.VehicleSpeed - VehicleSpeedWhole ) * 100 );

    int BrakeWhole = (int) ( keyBrakeTorque );
    int GearWhole = (int) ( EngTrModel_Y.Gear );

    // Write the messages to send to the LCD

    snprintf( FirstLine_LCD_MSG, sizeof(FirstLine_LCD_MSG), "%03d.%01d  %03d.%01d m/s", ThrottleWhole, ThrottleDecimal, VehicleSpeedWhole, VehicleSpeedDecimal );
    snprintf( SecondLine_LCD_MSG, sizeof(SecondLine_LCD_MSG), "%03d %04d.%01d RPM %01d", BrakeWhole, EngineSpeedWhole, EngineSpeedDecimal, GearWhole );

    // Display values on the LCD

    //LCD_Set_Cursor( 1, 1 );
    //LCD_Put_Str( FirstLine_LCD_MSG );
    //LCD_Set_Cursor( 2, 1 );
    //LCD_Put_Str( SecondLine_LCD_MSG );

    /* Properly format the model output data
     * and display it on the OLED screen.
     */

    snprintf(OLED_MSGS[0], sizeof(OLED_MSGS[0]), "THROTTLE: %03d.%01d", ThrottleWhole, ThrottleDecimal);
    snprintf(OLED_MSGS[1], sizeof(OLED_MSGS[1]), "BRAKE: %03d", BrakeWhole);
    snprintf(OLED_MSGS[2], sizeof(OLED_MSGS[2]), "VEHICLE SPEED: %03d.%01d m/s", VehicleSpeedWhole, VehicleSpeedDecimal);
    snprintf(OLED_MSGS[3], sizeof(OLED_MSGS[3]), "ENGINE SPEED: %04d.%01d RPM", EngineSpeedWhole, EngineSpeedDecimal);
    snprintf(OLED_MSGS[4], sizeof(OLED_MSGS[4]), "GEAR: %01d", GearWhole);

    for (int i = 0; i < OLED_MSGS_NUMBER; ++i)
    {
	USER_OLED_Message( I2C_2, OLED_MSGS[i], 0, i );
    }

    USER_TIM_Delay( TIM_2, TIM_PSC_40MS, TIM_CNT_40MS );
  }
}

void USER_SYSCLK_Configuration( void )
{
  /* System Clock (SYSCLK) configuration for 64 MHz */

  // Two wait states latency, if SYSCLK > 48 MHz

  FLASH->ACR	&=	~( 0x5UL << 0U );	
  FLASH->ACR	|=	( 0x2UL << 0U );	
  
  // PLL HSI clock /2 selected as PLL input clock
  
  RCC->CFGR	&=	~( 0x1UL << 16U )
		&	~( 0x7UL << 11U )		// APB2 pre-scaler /1
		&	~( 0x3UL << 8U )        	// APB1 pre-scaler /2 (APB1 must not exceed 36 MHz)
		&	~( 0xFUL << 4U );		// AHB pre-scaler /1

  // PLL input clock x 16 (PLLMUL bits)

  RCC->CFGR	|=	( 0xFUL << 18U )	
		|	( 0X4UL << 8U );		// APB1 pre-scaler /2
  RCC->CR	|=	( 0x1UL << 24U );		// PLL2 ON

  // Wait until PLL is locked

  while( !(RCC->CR & ~( 0x1UL << 25U )));

  // PLL used as system clock (SW bits)

  RCC->CFGR	&=	~( 0x1UL << 0U );
  RCC->CFGR	|=	( 0x2UL << 0U );

  // Wait until PLL is switched

  while( 0x8UL != ( RCC->CFGR & 0xCUL ));
}
