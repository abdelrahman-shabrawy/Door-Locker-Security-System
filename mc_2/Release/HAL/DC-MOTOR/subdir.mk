################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/DC-MOTOR/dc_motor.c 

OBJS += \
./HAL/DC-MOTOR/dc_motor.o 

C_DEPS += \
./HAL/DC-MOTOR/dc_motor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/DC-MOTOR/%.o: ../HAL/DC-MOTOR/%.c HAL/DC-MOTOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


