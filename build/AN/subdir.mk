# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./AN/ANDeclarations.cpp \
./AN/BitmapFont.cpp \
./AN/FontHelper.cpp \
./AN/GameLogic.cpp \
./AN/GameLoop.cpp \
./AN/Helpers.cpp \
./AN/TextureHelper.cpp 

OBJS += \
./build/AN/ANDeclarations.o \
./build/AN/BitmapFont.o \
./build/AN/FontHelper.o \
./build/AN/GameLogic.o \
./build/AN/GameLoop.o \
./build/AN/Helpers.o \
./build/AN/TextureHelper.o 

CPP_DEPS += \
./build/AN/ANDeclarations.d \
./build/AN/BitmapFont.d \
./build/AN/FontHelper.d \
./build/AN/GameLogic.d \
./build/AN/GameLoop.d \
./build/AN/Helpers.d \
./build/AN/TextureHelper.d 


# Each subdirectory must supply rules for building sources it contributes
build/AN/%.o: AN/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
