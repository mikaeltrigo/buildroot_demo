################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Gestionnaires/gEvent.c \
../src/Gestionnaires/gGPS.c \
../src/Gestionnaires/gHostCmd.c \
../src/Gestionnaires/gPrinter.c 

OBJS += \
./src/Gestionnaires/gEvent.o \
./src/Gestionnaires/gGPS.o \
./src/Gestionnaires/gHostCmd.o \
./src/Gestionnaires/gPrinter.o 

C_DEPS += \
./src/Gestionnaires/gEvent.d \
./src/Gestionnaires/gGPS.d \
./src/Gestionnaires/gHostCmd.d \
./src/Gestionnaires/gPrinter.d 


# Each subdirectory must supply rules for building sources it contributes
src/Gestionnaires/%.o: ../src/Gestionnaires/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabi-gcc -Wall -O3 -I"/home/mybbubuntu/workspace/testQuantum/src/Utils" -I"/home/mybbubuntu/workspace/testQuantum/src/Interfaces" -I"/home/mybbubuntu/workspace/testQuantum/src/Modules" -I"/home/mybbubuntu/workspace/testQuantum/src/Gestionnaires" -I/usr/arm-linux-gnueabi/include -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


