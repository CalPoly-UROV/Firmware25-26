################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/IMU/BNO080.c \
../Core/Inc/IMU/IMU.c \
../Core/Inc/IMU/Quaternion.c 

OBJS += \
./Core/Inc/IMU/BNO080.o \
./Core/Inc/IMU/IMU.o \
./Core/Inc/IMU/Quaternion.o 

C_DEPS += \
./Core/Inc/IMU/BNO080.d \
./Core/Inc/IMU/IMU.d \
./Core/Inc/IMU/Quaternion.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/IMU/%.o Core/Inc/IMU/%.su Core/Inc/IMU/%.cyclo: ../Core/Inc/IMU/%.c Core/Inc/IMU/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I/Users/liamduckworth/Documents/Robotics/UROV24-25/Embedded24-25/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/liamduckworth/Documents/Robotics/UROV24-25/Embedded24-25/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/liamduckworth/Documents/Robotics/UROV24-25/Embedded24-25/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/liamduckworth/Documents/Robotics/UROV24-25/Embedded24-25/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I/Users/liamduckworth/Documents/Robotics/UROV24-25/Embedded24-25/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/liamduckworth/Documents/Robotics/UROV24-25/Embedded24-25/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -IC:/Users/robot/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -IC:/Users/robot/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -IC:/Users/robot/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/robot/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -IC:/Users/robot/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/robot/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I/Users/eclypse/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/eclypse/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/eclypse/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/eclypse/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I/Users/eclypse/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/eclypse/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -I/Users/liamduckworth/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc -I/Users/liamduckworth/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/Users/liamduckworth/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I/Users/liamduckworth/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I/Users/liamduckworth/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/Users/liamduckworth/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.1/Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-IMU

clean-Core-2f-Inc-2f-IMU:
	-$(RM) ./Core/Inc/IMU/BNO080.cyclo ./Core/Inc/IMU/BNO080.d ./Core/Inc/IMU/BNO080.o ./Core/Inc/IMU/BNO080.su ./Core/Inc/IMU/IMU.cyclo ./Core/Inc/IMU/IMU.d ./Core/Inc/IMU/IMU.o ./Core/Inc/IMU/IMU.su ./Core/Inc/IMU/Quaternion.cyclo ./Core/Inc/IMU/Quaternion.d ./Core/Inc/IMU/Quaternion.o ./Core/Inc/IMU/Quaternion.su

.PHONY: clean-Core-2f-Inc-2f-IMU

