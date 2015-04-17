################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/NWEN241\ A03.c 

OBJS += \
./src/NWEN241\ A03.o 

C_DEPS += \
./src/NWEN241\ A03.d 


# Each subdirectory must supply rules for building sources it contributes
src/NWEN241\ A03.o: ../src/NWEN241\ A03.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/NWEN241 A03.d" -MT"src/NWEN241\ A03.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


