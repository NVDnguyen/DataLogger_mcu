################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/mw/sensor_service.c 

C_DEPS += \
./source/mw/sensor_service.d 

OBJS += \
./source/mw/sensor_service.o 


# Each subdirectory must supply rules for building sources it contributes
source/mw/%.o: ../source/mw/%.c source/mw/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"E:\MCUXpressoIDE\Datalogger\board" -I"E:\MCUXpressoIDE\Datalogger\middleware" -I"E:\MCUXpressoIDE\Datalogger\source" -I"E:\MCUXpressoIDE\Datalogger\drivers" -I"E:\MCUXpressoIDE\Datalogger\component\lists" -I"E:\MCUXpressoIDE\Datalogger\component\uart" -I"E:\MCUXpressoIDE\Datalogger\component\serial_manager" -I"E:\MCUXpressoIDE\Datalogger\utilities" -I"E:\MCUXpressoIDE\Datalogger\device" -I"E:\MCUXpressoIDE\Datalogger\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-mw

clean-source-2f-mw:
	-$(RM) ./source/mw/sensor_service.d ./source/mw/sensor_service.o

.PHONY: clean-source-2f-mw

