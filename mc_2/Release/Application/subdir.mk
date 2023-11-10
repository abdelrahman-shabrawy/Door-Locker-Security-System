################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/CONTROL\ _ECU.c 

OBJS += \
./Application/CONTROL\ _ECU.o 

C_DEPS += \
./Application/CONTROL\ _ECU.d 


# Each subdirectory must supply rules for building sources it contributes
Application/CONTROL\ _ECU.o: ../Application/CONTROL\ _ECU.c Application/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"Application/CONTROL _ECU.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


