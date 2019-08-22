################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Utils/FPGA_Registers.c \
../src/Utils/IpAddress.c \
../src/Utils/TimerDef.c \
../src/Utils/event.c \
../src/Utils/utils.c 

OBJS += \
./src/Utils/FPGA_Registers.o \
./src/Utils/IpAddress.o \
./src/Utils/TimerDef.o \
./src/Utils/event.o \
./src/Utils/utils.o 

C_DEPS += \
./src/Utils/FPGA_Registers.d \
./src/Utils/IpAddress.d \
./src/Utils/TimerDef.d \
./src/Utils/event.d \
./src/Utils/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utils/%.o: ../src/Utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabi-gcc -Wall -O0 -g -I"/home/mybbubuntu/workspace/testQuantum/src/Utils" -I"/home/mybbubuntu/workspace/testQuantum/src/Interfaces" -I"/home/mybbubuntu/workspace/testQuantum/src/Modules" -I"/home/mybbubuntu/workspace/testQuantum/src/Gestionnaires" -I/usr/arm-linux-gnueabi/include -I/home/mybbubuntu/Zynq/bsp-swt/out_swt_deploysys_MarsZX2/xilinx-linux/tools/include -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


