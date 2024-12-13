################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc12.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpi2c.c \
../drivers/fsl_lpit.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_smc.c \
../drivers/fsl_trgmux.c \
../drivers/my_adc.c \
../drivers/my_gpio.c \
../drivers/my_lpit.c 

C_DEPS += \
./drivers/fsl_adc12.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpi2c.d \
./drivers/fsl_lpit.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_smc.d \
./drivers/fsl_trgmux.d \
./drivers/my_adc.d \
./drivers/my_gpio.d \
./drivers/my_lpit.d 

OBJS += \
./drivers/fsl_adc12.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpi2c.o \
./drivers/fsl_lpit.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_smc.o \
./drivers/fsl_trgmux.o \
./drivers/my_adc.o \
./drivers/my_gpio.o \
./drivers/my_lpit.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKE16Z64VLF4 -DCPU_MKE16Z64VLF4_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"E:\MCUXpressoIDE\Ass\board" -I"E:\MCUXpressoIDE\Ass\source" -I"E:\MCUXpressoIDE\Ass\drivers" -I"E:\MCUXpressoIDE\Ass\component\lists" -I"E:\MCUXpressoIDE\Ass\component\uart" -I"E:\MCUXpressoIDE\Ass\component\serial_manager" -I"E:\MCUXpressoIDE\Ass\utilities" -I"E:\MCUXpressoIDE\Ass\device" -I"E:\MCUXpressoIDE\Ass\CMSIS" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_adc12.d ./drivers/fsl_adc12.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpi2c.d ./drivers/fsl_lpi2c.o ./drivers/fsl_lpit.d ./drivers/fsl_lpit.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_smc.d ./drivers/fsl_smc.o ./drivers/fsl_trgmux.d ./drivers/fsl_trgmux.o ./drivers/my_adc.d ./drivers/my_adc.o ./drivers/my_gpio.d ./drivers/my_gpio.o ./drivers/my_lpit.d ./drivers/my_lpit.o

.PHONY: clean-drivers

