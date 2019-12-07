################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP/Source/CommonTables/arm_common_tables.c \
../DSP/Source/CommonTables/arm_const_structs.c 

OBJS += \
./DSP/Source/CommonTables/arm_common_tables.o \
./DSP/Source/CommonTables/arm_const_structs.o 

C_DEPS += \
./DSP/Source/CommonTables/arm_common_tables.d \
./DSP/Source/CommonTables/arm_const_structs.d 


# Each subdirectory must supply rules for building sources it contributes
DSP/Source/CommonTables/arm_common_tables.o: ../DSP/Source/CommonTables/arm_common_tables.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DUSE_FULL_LL_DRIVER -DDEBUG -DSTM32F407xx '-D__FPU_PRESENT=1u' -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/Daniel/STM32CubeIDE/workspace_1.1.0/FinalProject/DSP/Include" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"DSP/Source/CommonTables/arm_common_tables.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
DSP/Source/CommonTables/arm_const_structs.o: ../DSP/Source/CommonTables/arm_const_structs.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM4 -DUSE_FULL_LL_DRIVER -DDEBUG -DSTM32F407xx '-D__FPU_PRESENT=1u' -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/Daniel/STM32CubeIDE/workspace_1.1.0/FinalProject/DSP/Include" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"DSP/Source/CommonTables/arm_const_structs.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

