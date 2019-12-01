################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display.c \
../src/gecko_ble_errors.c \
../src/gpio.c \
../src/i2c_interrupt.c \
../src/letimer0.c \
../src/log.c \
../src/main.c \
../src/state_machine.c 

OBJS += \
./src/display.o \
./src/gecko_ble_errors.o \
./src/gpio.o \
./src/i2c_interrupt.o \
./src/letimer0.o \
./src/log.o \
./src/main.o \
./src/state_machine.o 

C_DEPS += \
./src/display.d \
./src/gecko_ble_errors.d \
./src/gpio.d \
./src/i2c_interrupt.d \
./src/letimer0.d \
./src/log.d \
./src/main.d \
./src/state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
src/display.o: ../src/display.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/display.d" -MT"src/display.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gecko_ble_errors.o: ../src/gecko_ble_errors.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/gecko_ble_errors.d" -MT"src/gecko_ble_errors.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/gpio.o: ../src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/gpio.d" -MT"src/gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/i2c_interrupt.o: ../src/i2c_interrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/i2c_interrupt.d" -MT"src/i2c_interrupt.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/letimer0.o: ../src/letimer0.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/letimer0.d" -MT"src/letimer0.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/log.o: ../src/log.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/log.d" -MT"src/log.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/state_machine.o: ../src/state_machine.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -Os -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"src/state_machine.d" -MT"src/state_machine.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


