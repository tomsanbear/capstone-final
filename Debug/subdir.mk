################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ekgRead.cpp \
../main.cpp \
../matlabFunctions.cpp \
../myFilter.cpp \
../userClass.cpp 

OBJS += \
./ekgRead.o \
./main.o \
./matlabFunctions.o \
./myFilter.o \
./userClass.o 

CPP_DEPS += \
./ekgRead.d \
./main.d \
./matlabFunctions.d \
./myFilter.d \
./userClass.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


