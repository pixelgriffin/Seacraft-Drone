################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../includes/HealthBar.cpp \
../includes/Rect.cpp \
../includes/levelMgr.cpp 

OBJS += \
./includes/HealthBar.o \
./includes/Rect.o \
./includes/levelMgr.o 

CPP_DEPS += \
./includes/HealthBar.d \
./includes/Rect.d \
./includes/levelMgr.d 


# Each subdirectory must supply rules for building sources it contributes
includes/%.o: ../includes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I"/home/ecsl/workspace/DroneCraft/includes/micro" -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OGRE -I"/home/ecsl/workspace/DroneCraft/includes/ai" -I"/home/ecsl/workspace/DroneCraft/includes/gfx" -I"/home/ecsl/workspace/DroneCraft/includes/snd" -I"/home/ecsl/workspace/DroneCraft/includes/tactical" -I"/home/ecsl/workspace/DroneCraft/includes/net" -I/usr/include/OIS -I"/home/ecsl/workspace/DroneCraft/includes" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


