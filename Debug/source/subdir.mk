################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/ass.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/ass.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/ass.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"E:\MCUXpressoIDE\Ass\board" -I"E:\MCUXpressoIDE\Ass\source" -I"E:\MCUXpressoIDE\Ass\drivers" -I"E:\MCUXpressoIDE\Ass\component\lists" -I"E:\MCUXpressoIDE\Ass\component\uart" -I"E:\MCUXpressoIDE\Ass\component\serial_manager" -I"E:\MCUXpressoIDE\Ass\utilities" -I"E:\MCUXpressoIDE\Ass\device" -I"E:\MCUXpressoIDE\Ass\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/ass.d ./source/ass.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

