################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CodeAPA/APA_HAL.c 

OBJS += \
./CodeAPA/APA_HAL.o 

C_DEPS += \
./CodeAPA/APA_HAL.d 


# Each subdirectory must supply rules for building sources it contributes
CodeAPA/APA_HAL.o: ../CodeAPA/APA_HAL.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../CodeAPA -I../CodeAPA/System -I../CodeAPA/ComUart -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"CodeAPA/APA_HAL.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

