################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../_1Wire/CPWD_HAL.c 

OBJS += \
./_1Wire/CPWD_HAL.o 

C_DEPS += \
./_1Wire/CPWD_HAL.d 


# Each subdirectory must supply rules for building sources it contributes
_1Wire/CPWD_HAL.o: ../_1Wire/CPWD_HAL.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../_1Wire -I../_1Wire/System -I../_1Wire/SigFox -I../_1Wire/_1Wire -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"_1Wire/CPWD_HAL.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

