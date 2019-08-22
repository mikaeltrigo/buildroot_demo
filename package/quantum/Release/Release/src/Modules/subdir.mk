################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Modules/mFPGA.c \
../src/Modules/mGPS.c \
../src/Modules/mHostCmd.c \
../src/Modules/mPrintBuffer.c \
../src/Modules/mPulseBuffer.c \
../src/Modules/mRollingtimeBuffer.c \
../src/Modules/mRs232.c \
../src/Modules/mScugic.c 

OBJS += \
./src/Modules/mFPGA.o \
./src/Modules/mGPS.o \
./src/Modules/mHostCmd.o \
./src/Modules/mPrintBuffer.o \
./src/Modules/mPulseBuffer.o \
./src/Modules/mRollingtimeBuffer.o \
./src/Modules/mRs232.o \
./src/Modules/mScugic.o 

C_DEPS += \
./src/Modules/mFPGA.d \
./src/Modules/mGPS.d \
./src/Modules/mHostCmd.d \
./src/Modules/mPrintBuffer.d \
./src/Modules/mPulseBuffer.d \
./src/Modules/mRollingtimeBuffer.d \
./src/Modules/mRs232.d \
./src/Modules/mScugic.d 


# Each subdirectory must supply rules for building sources it contributes
src/Modules/%.o: ../src/Modules/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabi-gcc -Wall -O3 -I"/home/mybbubuntu/workspace/testQuantum/src/Utils" -I"/home/mybbubuntu/workspace/testQuantum/src/Interfaces" -I"/home/mybbubuntu/workspace/testQuantum/src/Modules" -I"/home/mybbubuntu/workspace/testQuantum/src/Gestionnaires" -I/usr/arm-linux-gnueabi/include -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


