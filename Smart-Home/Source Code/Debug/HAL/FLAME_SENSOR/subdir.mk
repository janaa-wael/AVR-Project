################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/FLAME_SENSOR/FLAME_SENSOR.c 

OBJS += \
./HAL/FLAME_SENSOR/FLAME_SENSOR.o 

C_DEPS += \
./HAL/FLAME_SENSOR/FLAME_SENSOR.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/FLAME_SENSOR/%.o: ../HAL/FLAME_SENSOR/%.c HAL/FLAME_SENSOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


