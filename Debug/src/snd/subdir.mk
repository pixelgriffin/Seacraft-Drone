################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/snd/SoundMgr.cpp 

OBJS += \
./src/snd/SoundMgr.o 

CPP_DEPS += \
./src/snd/SoundMgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/snd/%.o: ../src/snd/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I"/home/ecsl/workspace/Seacraft-Drone/includes/micro" -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OGRE -I"/home/ecsl/workspace/Seacraft-Drone/includes/ai" -I"/home/ecsl/workspace/Seacraft-Drone/includes/gfx" -I"/home/ecsl/workspace/Seacraft-Drone/includes/snd" -I"/home/ecsl/workspace/Seacraft-Drone/includes/tactical" -I"/home/ecsl/workspace/Seacraft-Drone/includes/net" -I/usr/include/OIS -I"/home/ecsl/workspace/Seacraft-Drone/includes" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


