################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CAN.cpp \
../src/DisP.cpp \
../src/DisP2.0.cpp \
../src/HighResTimer.cpp \
../src/I2C.cpp \
../src/LCD.cpp \
../src/MPU9250.cpp \
../src/MadgwickFilter.cpp \
../src/PinsConfig.cpp \
../src/RTC.cpp \
../src/SD.cpp \
../src/SPI.cpp \
../src/Timers.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc175x_6x.cpp \
../src/interrupt.cpp 

C_SRCS += \
../src/crp.c \
../src/sysinit.c 

OBJS += \
./src/CAN.o \
./src/DisP.o \
./src/DisP2.0.o \
./src/HighResTimer.o \
./src/I2C.o \
./src/LCD.o \
./src/MPU9250.o \
./src/MadgwickFilter.o \
./src/PinsConfig.o \
./src/RTC.o \
./src/SD.o \
./src/SPI.o \
./src/Timers.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/interrupt.o \
./src/sysinit.o 

CPP_DEPS += \
./src/CAN.d \
./src/DisP.d \
./src/DisP2.0.d \
./src/HighResTimer.d \
./src/I2C.d \
./src/LCD.d \
./src/MPU9250.d \
./src/MadgwickFilter.d \
./src/PinsConfig.d \
./src/RTC.d \
./src/SD.d \
./src/SPI.d \
./src/Timers.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc175x_6x.d \
./src/interrupt.d 

C_DEPS += \
./src/crp.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DNO_BOARD_LIB -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\Marc-Antoine\Desktop\SessionHiver2020\61D_Projet_Integrateur\DisP2.0\inc" -I"C:\Users\Marc-Antoine\Desktop\Session_Automne_2019\516_Processeurs_Embarques\MCUXpresso\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Marc-Antoine\Desktop\Session_Automne_2019\516_Processeurs_Embarques\MCUXpresso\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DNO_BOARD_LIB -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\Marc-Antoine\Desktop\SessionHiver2020\61D_Projet_Integrateur\DisP2.0\inc" -I"C:\Users\Marc-Antoine\Desktop\Session_Automne_2019\516_Processeurs_Embarques\MCUXpresso\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Marc-Antoine\Desktop\Session_Automne_2019\516_Processeurs_Embarques\MCUXpresso\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


