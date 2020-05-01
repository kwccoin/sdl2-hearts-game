# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./Game/Game.cpp \
./Game/GameDeclarations.cpp \
./Game/GameState.cpp \
./Game/MoveButton.cpp 

OBJS += \
./build/Game/Game.o \
./build/Game/GameDeclarations.o \
./build/Game/GameState.o \
./build/Game/MoveButton.o 

CPP_DEPS += \
./build/Game/Game.d \
./build/Game/GameDeclarations.d \
./build/Game/GameState.d \
./build/Game/MoveButton.d 


# Each subdirectory must supply rules for building sources it contributes
build/Game/%.o: Game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
