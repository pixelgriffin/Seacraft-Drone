################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tactical/flock.cpp \
../src/tactical/group.cpp \
../src/tactical/groupAI.cpp \
../src/tactical/groupMgr.cpp 

OBJS += \
./src/tactical/flock.o \
./src/tactical/group.o \
./src/tactical/groupAI.o \
./src/tactical/groupMgr.o 

CPP_DEPS += \
./src/tactical/flock.d \
./src/tactical/group.d \
./src/tactical/groupAI.d \
./src/tactical/groupMgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/tactical/%.o: ../src/tactical/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I"/home/ecsl/workspace/DroneCraft1.1/includes/micro" -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OGRE -I"/home/ecsl/workspace/DroneCraft1.1/includes/ai" -I"/home/ecsl/workspace/DroneCraft1.1/includes/gfx" -I"/home/ecsl/workspace/DroneCraft1.1/includes/snd" -I"/home/ecsl/workspace/DroneCraft1.1/includes/tactical" -I"/home/ecsl/workspace/DroneCraft1.1/includes/net" -I/usr/include/OIS -I"/home/ecsl/workspace/DroneCraft1.1/includes" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


