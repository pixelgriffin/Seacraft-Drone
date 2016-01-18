################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/net/listener.cpp \
../src/net/messages.cpp \
../src/net/netAspect.cpp \
../src/net/netCommon.cpp \
../src/net/netLobby.cpp \
../src/net/netThread.cpp \
../src/net/sender.cpp \
../src/net/socket.cpp 

OBJS += \
./src/net/listener.o \
./src/net/messages.o \
./src/net/netAspect.o \
./src/net/netCommon.o \
./src/net/netLobby.o \
./src/net/netThread.o \
./src/net/sender.o \
./src/net/socket.o 

CPP_DEPS += \
./src/net/listener.d \
./src/net/messages.d \
./src/net/netAspect.d \
./src/net/netCommon.d \
./src/net/netLobby.d \
./src/net/netThread.d \
./src/net/sender.d \
./src/net/socket.d 


# Each subdirectory must supply rules for building sources it contributes
src/net/%.o: ../src/net/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include -I"/home/ecsl/workspace/Seacraft-Drone/includes/micro" -I/usr/include/OGRE -I/usr/include/boost -I/usr/local/include/OGRE -I"/home/ecsl/workspace/Seacraft-Drone/includes/ai" -I"/home/ecsl/workspace/Seacraft-Drone/includes/gfx" -I"/home/ecsl/workspace/Seacraft-Drone/includes/snd" -I"/home/ecsl/workspace/Seacraft-Drone/includes/tactical" -I"/home/ecsl/workspace/Seacraft-Drone/includes/net" -I/usr/include/OIS -I"/home/ecsl/workspace/Seacraft-Drone/includes" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


