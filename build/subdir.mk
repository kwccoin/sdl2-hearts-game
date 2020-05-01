# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
./main.cpp 

OBJS += \
./build/main.o 

CPP_DEPS += \
./build/main.d 


# Each subdirectory must supply rules for building sources it contributes
build/%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++11 -I/usr/include/SDL2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
