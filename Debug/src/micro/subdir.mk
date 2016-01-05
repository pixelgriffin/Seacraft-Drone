################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/micro/GA.cpp \
../src/micro/IMEnemy.cpp \
../src/micro/IMEnemy3D.cpp \
../src/micro/IMTerrain.cpp \
../src/micro/InfluenceMap.cpp \
../src/micro/InfluenceMap3D.cpp \
../src/micro/MicroAspect.cpp \
../src/micro/SquadMgr.cpp \
../src/micro/infoMgr.cpp 

OBJS += \
./src/micro/GA.o \
./src/micro/IMEnemy.o \
./src/micro/IMEnemy3D.o \
./src/micro/IMTerrain.o \
./src/micro/InfluenceMap.o \
./src/micro/InfluenceMap3D.o \
./src/micro/MicroAspect.o \
./src/micro/SquadMgr.o \
./src/micro/infoMgr.o 

CPP_DEPS += \
./src/micro/GA.d \
./src/micro/IMEnemy.d \
./src/micro/IMEnemy3D.d \
./src/micro/IMTerrain.d \
./src/micro/InfluenceMap.d \
./src/micro/InfluenceMap3D.d \
./src/micro/MicroAspect.d \
./src/micro/SquadMgr.d \
./src/micro/infoMgr.d 


# Each subdirectory must supply rules for building sources it contributes
src/micro/%.o: ../src/micro/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I"/home/ecsl/workspace/DroneCraft1.1/includes/micro" -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OGRE -I"/home/ecsl/workspace/DroneCraft1.1/includes/ai" -I"/home/ecsl/workspace/DroneCraft1.1/includes/gfx" -I"/home/ecsl/workspace/DroneCraft1.1/includes/snd" -I"/home/ecsl/workspace/DroneCraft1.1/includes/tactical" -I"/home/ecsl/workspace/DroneCraft1.1/includes/net" -I/usr/include/OIS -I"/home/ecsl/workspace/DroneCraft1.1/includes" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


