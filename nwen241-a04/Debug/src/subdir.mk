################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/q1.c \
../src/q2.c \
../src/q3.c \
../src/q4.c 

OBJS += \
./src/q1.o \
./src/q2.o \
./src/q3.o \
./src/q4.o 

C_DEPS += \
./src/q1.d \
./src/q2.d \
./src/q3.d \
./src/q4.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


