################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/drivers/display.c \
../hardware/kit/common/drivers/displayls013b7dh03.c \
../hardware/kit/common/drivers/displaypalemlib.c \
../hardware/kit/common/drivers/i2cspm.c \
../hardware/kit/common/drivers/mx25flash_spi.c \
../hardware/kit/common/drivers/retargetio.c \
../hardware/kit/common/drivers/retargetserial.c \
../hardware/kit/common/drivers/udelay.c 

OBJS += \
./hardware/kit/common/drivers/display.o \
./hardware/kit/common/drivers/displayls013b7dh03.o \
./hardware/kit/common/drivers/displaypalemlib.o \
./hardware/kit/common/drivers/i2cspm.o \
./hardware/kit/common/drivers/mx25flash_spi.o \
./hardware/kit/common/drivers/retargetio.o \
./hardware/kit/common/drivers/retargetserial.o \
./hardware/kit/common/drivers/udelay.o 

C_DEPS += \
./hardware/kit/common/drivers/display.d \
./hardware/kit/common/drivers/displayls013b7dh03.d \
./hardware/kit/common/drivers/displaypalemlib.d \
./hardware/kit/common/drivers/i2cspm.d \
./hardware/kit/common/drivers/mx25flash_spi.d \
./hardware/kit/common/drivers/retargetio.d \
./hardware/kit/common/drivers/retargetserial.d \
./hardware/kit/common/drivers/udelay.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/drivers/display.o: ../hardware/kit/common/drivers/display.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/display.d" -MT"hardware/kit/common/drivers/display.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/displayls013b7dh03.o: ../hardware/kit/common/drivers/displayls013b7dh03.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/displayls013b7dh03.d" -MT"hardware/kit/common/drivers/displayls013b7dh03.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/displaypalemlib.o: ../hardware/kit/common/drivers/displaypalemlib.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/displaypalemlib.d" -MT"hardware/kit/common/drivers/displaypalemlib.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/i2cspm.o: ../hardware/kit/common/drivers/i2cspm.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/i2cspm.d" -MT"hardware/kit/common/drivers/i2cspm.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/mx25flash_spi.o: ../hardware/kit/common/drivers/mx25flash_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/mx25flash_spi.d" -MT"hardware/kit/common/drivers/mx25flash_spi.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/retargetio.o: ../hardware/kit/common/drivers/retargetio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/retargetio.d" -MT"hardware/kit/common/drivers/retargetio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/retargetserial.o: ../hardware/kit/common/drivers/retargetserial.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/retargetserial.d" -MT"hardware/kit/common/drivers/retargetserial.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hardware/kit/common/drivers/udelay.o: ../hardware/kit/common/drivers/udelay.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DMESH_LIB_NATIVE=1' '-D__HEAP_SIZE=0x1200' '-D__STACK_SIZE=0x1000' '-DHAL_CONFIG=1' '-DINCLUDE_LOGGING=1' '-DEFR32BG13P632F512GM48=1' -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\drivers" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\CMSIS\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\bsp" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\EFR32BG13_BRD4104A\config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\soc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\inc\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emlib\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\common" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Include" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\protocol\bluetooth\bt_mesh\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source\GCC" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\bootloader\api" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\hardware\kit\common\halconfig" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\chip\efr32\efr32xg1x" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ble" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\common\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\src" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\radio\rail_lib\protocol\ieee802154" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\halconfig\inc\hal-config" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\Device\SiliconLabs\EFR32BG13P\Source" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\sleep\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\gpiointerrupt\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\emdrv\uartdrv\inc" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\dmd" -I"C:\Users\BS THITE\SimplicityStudio\v4_workspace\soc-btmesh-empty\platform\middleware\glib\glib" -O0 -fno-builtin -flto -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/drivers/udelay.d" -MT"hardware/kit/common/drivers/udelay.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


