################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include _1Wire/_1Wire/subdir.mk
-include _1Wire/System/subdir.mk
-include _1Wire/SigFox/subdir.mk
-include _1Wire/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
_1Wire.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
_1Wire.list \

OBJCOPY_BIN += \
_1Wire.bin \


# All Target
all: _1Wire.elf secondary-outputs

# Tool invocations
_1Wire.elf: $(OBJS) $(USER_OBJS) D:\OneDrive\DOCUMENTS\TP_BUSCOM\_1Wire\STM32F446RETX_FLASH.ld
	arm-none-eabi-gcc -o "_1Wire.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\OneDrive\DOCUMENTS\TP_BUSCOM\_1Wire\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="_1Wire.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

_1Wire.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "_1Wire.list"
	@echo 'Finished building: $@'
	@echo ' '

_1Wire.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "_1Wire.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
