# Based on the Eclipse CDT generated makefile

RM := rm -rf

.DEFAULT_GOAL := all

# All of the sources participating in the build are defined here
-include build/sources.mk
-include build/Game/Extras/subdir.mk
-include build/Game/subdir.mk
-include build/AN/subdir.mk
-include build/subdir.mk
-include build/objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: sdl2-hearts-game

# Tool invocations
sdl2-hearts-game: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L/usr/lib/x86_64-linux-gnu -o "sdl2-hearts-game" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) sdl2-hearts-game
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
