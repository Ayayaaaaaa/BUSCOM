################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CodeAPA/SerialFifo/SerialFifo.c 

OBJS += \
./CodeAPA/SerialFifo/SerialFifo.o 

C_DEPS += \
./CodeAPA/SerialFifo/SerialFifo.d 


# Each subdirectory must supply rules for building sources it contributes
CodeAPA/SerialFifo/SerialFifo.o: ../CodeAPA/SerialFifo/SerialFifo.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CodeAPA/SerialFifo/SerialFifo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

