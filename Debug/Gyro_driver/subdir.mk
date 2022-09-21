################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gyro_driver/Gyro_l3g4200.c 

OBJS += \
./Gyro_driver/Gyro_l3g4200.o 

C_DEPS += \
./Gyro_driver/Gyro_l3g4200.d 


# Each subdirectory must supply rules for building sources it contributes
Gyro_driver/%.o: ../Gyro_driver/%.c Gyro_driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx '-DCMSIS_device_header=<stm32g0xx.h>' -c -I../Core/Inc -I"D:/STM_PROJECTS/NUCLEO-G070RB/Gyro_L3G4200D/Gyro_driver" -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM0 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Gyro_driver

clean-Gyro_driver:
	-$(RM) ./Gyro_driver/Gyro_l3g4200.d ./Gyro_driver/Gyro_l3g4200.o

.PHONY: clean-Gyro_driver

