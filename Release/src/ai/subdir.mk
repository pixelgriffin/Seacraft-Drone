################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ai/gather.cpp 

OBJS += \
./src/ai/gather.o 

CPP_DEPS += \
./src/ai/gather.d 


# Each subdirectory must supply rules for building sources it contributes
src/ai/%.o: ../src/ai/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I"/home/sushil/workspace/Seacraft-Drone/includes/micro" -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OGRE -I"/home/sushil/workspace/Seacraft-Drone/includes/ai" -I"/home/sushil/workspace/Seacraft-Drone/includes/gfx" -I"/home/sushil/workspace/Seacraft-Drone/includes/snd" -I"/home/sushil/workspace/Seacraft-Drone/includes/tactical" -I"/home/sushil/workspace/Seacraft-Drone/includes/net" -I/usr/include/OIS -I"/home/sushil/workspace/Seacraft-Drone/includes" -O3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


