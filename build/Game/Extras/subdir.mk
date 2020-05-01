# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./Game/Extras/Card.cpp \
./Game/Extras/CardHand.cpp \
./Game/Extras/CardSpriteManager.cpp \
./Game/Extras/ExtraDeclarations.cpp \
./Game/Extras/OtherHand.cpp \
./Game/Extras/SomeHand.cpp 

OBJS += \
./build/Game/Extras/Card.o \
./build/Game/Extras/CardHand.o \
./build/Game/Extras/CardSpriteManager.o \
./build/Game/Extras/ExtraDeclarations.o \
./build/Game/Extras/OtherHand.o \
./build/Game/Extras/SomeHand.o 

CPP_DEPS += \
./build/Game/Extras/Card.d \
./build/Game/Extras/CardHand.d \
./build/Game/Extras/CardSpriteManager.d \
./build/Game/Extras/ExtraDeclarations.d \
./build/Game/Extras/OtherHand.d \
./build/Game/Extras/SomeHand.d 


# Each subdirectory must supply rules for building sources it contributes
build/Game/Extras/%.o: Game/Extras/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
