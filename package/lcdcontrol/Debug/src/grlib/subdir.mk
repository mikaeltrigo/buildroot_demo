################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/grlib/circle.c \
../src/grlib/context.c \
../src/grlib/display.c \
../src/grlib/font.c \
../src/grlib/image.c \
../src/grlib/line.c \
../src/grlib/rectangle.c \
../src/grlib/string.c \
../src/grlib/swt.c \
../src/grlib/trigo.c 

OBJS += \
./src/grlib/circle.o \
./src/grlib/context.o \
./src/grlib/display.o \
./src/grlib/font.o \
./src/grlib/image.o \
./src/grlib/line.o \
./src/grlib/rectangle.o \
./src/grlib/string.o \
./src/grlib/swt.o \
./src/grlib/trigo.o 

C_DEPS += \
./src/grlib/circle.d \
./src/grlib/context.d \
./src/grlib/display.d \
./src/grlib/font.d \
./src/grlib/image.d \
./src/grlib/line.d \
./src/grlib/rectangle.d \
./src/grlib/string.d \
./src/grlib/swt.d \
./src/grlib/trigo.d 


# Each subdirectory must supply rules for building sources it contributes
src/grlib/%.o: ../src/grlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 Linux gcc compiler'
	arm-linux-gnueabi-gcc -Wall -O0 -g3 -I/usr/arm-linux-gnueabi/include -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


