################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabi-gcc -Wall -O3 -I"/home/mybbubuntu/workspace/testQuantum/src/Utils" -I"/home/mybbubuntu/workspace/testQuantum/src/Interfaces" -I"/home/mybbubuntu/workspace/testQuantum/src/Modules" -I"/home/mybbubuntu/workspace/testQuantum/src/Gestionnaires" -I/usr/arm-linux-gnueabi/include -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


