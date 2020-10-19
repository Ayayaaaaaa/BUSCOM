################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CodeAPA/ComUart/ComUart.c \
../CodeAPA/ComUart/ComUart_App.c 

OBJS += \
./CodeAPA/ComUart/ComUart.o \
./CodeAPA/ComUart/ComUart_App.o 

C_DEPS += \
./CodeAPA/ComUart/ComUart.d \
./CodeAPA/ComUart/ComUart_App.d 


# Each subdirectory must supply rules for building sources it contributes
CodeAPA/ComUart/ComUart.o: ../CodeAPA/ComUart/ComUart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../CodeAPA -I../CodeAPA/System -I../CodeAPA/ComUart -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CodeAPA/ComUart/ComUart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
CodeAPA/ComUart/ComUart_App.o: ../CodeAPA/ComUart/ComUart_App.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../CodeAPA -I../CodeAPA/System -I../CodeAPA/ComUart -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CodeAPA/ComUart/ComUart_App.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

