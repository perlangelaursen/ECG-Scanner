################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../filter.c \
../index.c \
../main.c \
../peaks.c \
../sensor.c 

OBJS += \
./filter.o \
./index.o \
./main.o \
./peaks.o \
./sensor.o 

C_DEPS += \
./filter.d \
./index.d \
./main.d \
./peaks.d \
./sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<" -lm
	@echo 'Finished building: $<'
	@echo ' '


