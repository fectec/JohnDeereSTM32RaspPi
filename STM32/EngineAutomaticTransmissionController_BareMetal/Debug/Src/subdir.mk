################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ADC.c \
../Src/EngTrModel.c \
../Src/EngTrModel_data.c \
../Src/GPIO.c \
../Src/I2C.c \
../Src/LCD.c \
../Src/LEDS.c \
../Src/MATRIX_KEYPAD.c \
../Src/OLED.c \
../Src/SYSTICK.c \
../Src/TIMER.c \
../Src/UART.c \
../Src/main.c \
../Src/rtGetInf.c \
../Src/rtGetNaN.c \
../Src/rt_nonfinite.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/ADC.o \
./Src/EngTrModel.o \
./Src/EngTrModel_data.o \
./Src/GPIO.o \
./Src/I2C.o \
./Src/LCD.o \
./Src/LEDS.o \
./Src/MATRIX_KEYPAD.o \
./Src/OLED.o \
./Src/SYSTICK.o \
./Src/TIMER.o \
./Src/UART.o \
./Src/main.o \
./Src/rtGetInf.o \
./Src/rtGetNaN.o \
./Src/rt_nonfinite.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/ADC.d \
./Src/EngTrModel.d \
./Src/EngTrModel_data.d \
./Src/GPIO.d \
./Src/I2C.d \
./Src/LCD.d \
./Src/LEDS.d \
./Src/MATRIX_KEYPAD.d \
./Src/OLED.d \
./Src/SYSTICK.d \
./Src/TIMER.d \
./Src/UART.d \
./Src/main.d \
./Src/rtGetInf.d \
./Src/rtGetNaN.d \
./Src/rt_nonfinite.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -DNUCLEO_F103RB -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ADC.cyclo ./Src/ADC.d ./Src/ADC.o ./Src/ADC.su ./Src/EngTrModel.cyclo ./Src/EngTrModel.d ./Src/EngTrModel.o ./Src/EngTrModel.su ./Src/EngTrModel_data.cyclo ./Src/EngTrModel_data.d ./Src/EngTrModel_data.o ./Src/EngTrModel_data.su ./Src/GPIO.cyclo ./Src/GPIO.d ./Src/GPIO.o ./Src/GPIO.su ./Src/I2C.cyclo ./Src/I2C.d ./Src/I2C.o ./Src/I2C.su ./Src/LCD.cyclo ./Src/LCD.d ./Src/LCD.o ./Src/LCD.su ./Src/LEDS.cyclo ./Src/LEDS.d ./Src/LEDS.o ./Src/LEDS.su ./Src/MATRIX_KEYPAD.cyclo ./Src/MATRIX_KEYPAD.d ./Src/MATRIX_KEYPAD.o ./Src/MATRIX_KEYPAD.su ./Src/OLED.cyclo ./Src/OLED.d ./Src/OLED.o ./Src/OLED.su ./Src/SYSTICK.cyclo ./Src/SYSTICK.d ./Src/SYSTICK.o ./Src/SYSTICK.su ./Src/TIMER.cyclo ./Src/TIMER.d ./Src/TIMER.o ./Src/TIMER.su ./Src/UART.cyclo ./Src/UART.d ./Src/UART.o ./Src/UART.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/rtGetInf.cyclo ./Src/rtGetInf.d ./Src/rtGetInf.o ./Src/rtGetInf.su ./Src/rtGetNaN.cyclo ./Src/rtGetNaN.d ./Src/rtGetNaN.o ./Src/rtGetNaN.su ./Src/rt_nonfinite.cyclo ./Src/rt_nonfinite.d ./Src/rt_nonfinite.o ./Src/rt_nonfinite.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

