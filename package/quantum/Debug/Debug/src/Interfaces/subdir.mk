################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Interfaces/iFPGA.c 

OBJS += \
./src/Interfaces/iFPGA.o 

C_DEPS += \
./src/Interfaces/iFPGA.d 


# Each subdirectory must supply rules for building sources it contributes
src/Interfaces/%.o: ../src/Interfaces/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabi-gcc -Wall -O0 -g -I"/home/mybbubuntu/workspace/testQuantum/src/Utils" -I"/home/mybbubuntu/workspace/testQuantum/src/Interfaces" -I"/home/mybbubuntu/workspace/testQuantum/src/Modules" -I"/home/mybbubuntu/workspace/testQuantum/src/Gestionnaires" -I/usr/arm-linux-gnueabi/include -I/home/mybbubuntu/Zynq/bsp-swt/out_swt_deploysys_MarsZX2/xilinx-linux/tools/include -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


