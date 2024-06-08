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

// UART

uint8_t receivedThrottle = 0;

// Matrix keypad

char selectedKey = 'N';
float keyBrakeTorque = 0.0;

// LCD

char FirstLine_LCD_MSG[LCD_CHARS + 1];
char SecondLine_LCD_MSG[LCD_CHARS + 1];

// OLED

char oled_buffer[OLED_SCREEN_ROWS][OLED_SCREEN_COLUMNS];
char OLED_MSGS[OLED_MSGS_NUMBER][OLED_SCREEN_COLUMNS];

// Mode select

uint8_t operationMode = 0;

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
  USER_LCD_Init();

  USER_OLED_Init_64( I2C_2 );
  USER_OLED_Animation( I2C_2, oled_buffer );

  USER_PWM_Init();

  EngTrModel_initialize();

  /* Loop forever */

  for(;;)
  {
    /* Read the ADC conversion, convert it to a voltage value,
     * and normalize it to within the range accepted by the model,
     * this for manual mode.
     */

    conversionData = USER_ADC_Convert( ADC_1 );
    voltageValue = 0.00080586 * conversionData;
    potentiometerThrottle = scaleVoltageValue( voltageValue, 0, 3.3 );

    /* Read the matrix keyboard and
     * adapt the brake value, LEDs states,
     * micro servo direction and operation mode
     * based on the selected key.
     */

    selectedKey = USER_MATRIX_KEYPAD_Read();

    if(selectedKey == '5')							// Brake action
    {
      keyBrakeTorque = 100.0;							// Full brake torque

      USER_TIM_Delay( TIM_3, TIM_PSC_200MS, TIM_CNT_200MS );			// LEDs blinking
    }
    else if(selectedKey == '4' || selectedKey == '6')				// Left or right action
    {
      keyBrakeTorque = 50.0;							// Half brake torque

      if(selectedKey == '4')							// Left action
      {
	  USER_GPIO_Write( PORTC, 2, 1 );					// Left LED turned on
	  USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_12_5 );	// The micro servo rotates to a 180° position
      }
      else									// Right action
      {
	  USER_GPIO_Write( PORTC, 3, 1 );					// Right LED turned on
	  USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_2_5 );	// The micro servo rotates to a 0° position
      }
    }
    else if(selectedKey == 'A')							// Select manual mode action
    {
	operationMode = 0;							// Manual mode
    }
    else if(selectedKey == 'B')							// Select simulation mode action
    {
	operationMode = 1;							// Simulation mode
    }
    else									// No action
    {
      keyBrakeTorque = 0.0;							// No brake torque

      USER_GPIO_Write( PORTC, 2, 0 );						// LEDs turned off
      USER_GPIO_Write( PORTC, 3, 0 );

      USER_PWM_Generate( PWM_PSC_20MS, PWM_ARR_20MS, PWM_CCRX_7_5 );		// The micro servo rotates to a 90° position
    }

    /* Read the throttle value sent via UART by the Raspeberry Pi
     * for simulation mode.
     */

    if( USART1->SR & USART_SR_RXNE )						// If USART_DR is not empty
    {
	receivedThrottle = USART1->DR;						// Receive data
    }

    /* Feed the model with the throttle value
     * and the brake value, take a step and
     * sanitize the output values.
     */

    if(operationMode == 0)							// Manual mode
    {
	EngTrModel_U.Throttle = potentiometerThrottle;				// Model feed with potentiometer throttle value
    }
    else									// Simulation mode
    {
      EngTrModel_U.Throttle = (float) receivedThrottle;				// Model feed with received throttle value
    }

    EngTrModel_U.BrakeTorque = keyBrakeTorque;					// Model feed with brake value

    EngTrModel_step();								// Take a step

    // Sanitize the output values

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
     * and display it on the LCD
     */

    /* Extract the whole and decimal parts for Throttle,
     * Engine Speed and Vehicle Speed, and cast them
     * alongside Brake and Gear to integers.
     */

    int ThrottleWhole = (int) ( potentiometerThrottle );
    int ThrottleDecimal = (int) ( ( potentiometerThrottle - ThrottleWhole ) * 100 );

    int VehicleSpeedWhole = (int)( EngTrModel_Y.VehicleSpeed );
    int VehicleSpeedDecimal = (int)( ( EngTrModel_Y.VehicleSpeed - VehicleSpeedWhole ) * 100 );

    int EngineSpeedWhole = (int)( EngTrModel_Y.EngineSpeed );
    int EngineSpeedDecimal = (int)( ( EngTrModel_Y.EngineSpeed - EngineSpeedWhole ) * 100 );

    int BrakeWhole = (int) ( keyBrakeTorque );
    int GearWhole = (int) ( EngTrModel_Y.Gear );

    // Write the messages to send to the LCD

    snprintf( FirstLine_LCD_MSG, sizeof(FirstLine_LCD_MSG), "%03d.%01d  %03d.%01d m/s", ThrottleWhole, ThrottleDecimal / 10, VehicleSpeedWhole, VehicleSpeedDecimal / 10 );
    snprintf( SecondLine_LCD_MSG, sizeof(SecondLine_LCD_MSG), "%03d %01d %04d.%01d RPM", BrakeWhole, GearWhole, EngineSpeedWhole, EngineSpeedDecimal / 10 );

    // Display values on the LCD

    LCD_Set_Cursor( 1, 1 );
    LCD_Put_Str( FirstLine_LCD_MSG );
    LCD_Set_Cursor( 2, 1 );
    LCD_Put_Str( SecondLine_LCD_MSG );

    /* Display the output model data
     *  on the OLED screen.
     */

    // Write the messages to send to the OLED screen

    if(operationMode == 0)							// Manuel mode
    {
	snprintf(OLED_MSGS[0], sizeof(OLED_MSGS[0]), "MODE: Man");
    }
    else									// Simulation mode
    {
	snprintf(OLED_MSGS[0], sizeof(OLED_MSGS[0]), "MODE: Sim");
    }

    snprintf(OLED_MSGS[1], sizeof(OLED_MSGS[1]), "MANUAL THROTTLE: %03d.%02d", ThrottleWhole, ThrottleDecimal);
    snprintf(OLED_MSGS[2], sizeof(OLED_MSGS[2]), "SIMULATION THROTTLE: %03d", receivedThrottle);
    snprintf(OLED_MSGS[3], sizeof(OLED_MSGS[3]), "BRAKE: %03d", BrakeWhole);
    snprintf(OLED_MSGS[4], sizeof(OLED_MSGS[4]), "VEHICLE SPEED: %03d.%02d m/s", VehicleSpeedWhole, VehicleSpeedDecimal);
    snprintf(OLED_MSGS[5], sizeof(OLED_MSGS[5]), "ENGINE SPEED: %04d.%02d RPM", EngineSpeedWhole, EngineSpeedDecimal);
    snprintf(OLED_MSGS[6], sizeof(OLED_MSGS[6]), "GEAR: %01d", GearWhole);

    // Display values on the OLED screen

    for (int i = 0; i < OLED_MSGS_NUMBER; ++i)
    {
	USER_OLED_Message( I2C_2, OLED_MSGS[i], 0, i );
    }

    USER_TIM_Delay( TIM_2, TIM_PSC_200MS, TIM_CNT_200MS );
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
