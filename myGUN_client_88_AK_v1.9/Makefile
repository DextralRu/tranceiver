GUNTYPE = AK

#MCU = atmega8
#MCU = atmega16
#MCU = atmega48
MCU = atmega88pa
#MCU = atmega328p
#MCU = atmega168
#MCU = at90usb162

## General Flags
PROJECT = gun_$(GUNTYPE)_$(MCU)




TARGET = $(PROJECT).elf
CC = avr-gcc

## Defines
#DEFINES = -D_9DATA_
#DEFINES = -D_RS485_

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -DF_CPU=16000000UL -Os -fsigned-char -std=gnu99
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d $(DEFINES)

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += 


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
#INCLUDES = -I".." -I"../../usbdrv" -I/opt/avr-toolchain/avr/include
INCLUDES = -I. -I./include -I./lib/cc1101/include -I/opt/avr-toolchain/avr/include

## Objects that must be built in order to link
OBJECTS = main.o lib/spi/spi.o lib/i2chw/twimaster.o lib/l3g4200d/l3g4200d.o lib/cc1101/wr_settings.o lib/cc1101/wr_burst_reg_flash.o lib/cc1101/wr_reg.o lib/cc1101/rd_reg.o lib/cc1101/wr_strobe.o lib/cc1101/send_pkt.o lib/cc1101/rd_burst_reg.o

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss size

## Compile
main.o: ./main.c lib/spi/spi.c lib/i2chw/twimaster.c lib/l3g4200d/l3g4200d.c lib/cc1101/wr_settings.c lib/cc1101/wr_burst_reg_flash.c lib/cc1101/wr_reg.c lib/cc1101/rd_reg.c lib/cc1101/wr_strobe.c lib/cc1101/send_pkt.c lib/cc1101/rd_burst_reg.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

erase: ${TARGET}
	@echo "======================FIRMWARE!======================"
	@avrdude -c usbasp -p m88p -B 8 -e


## Burn Firmware
flash: ${TARGET}
	@echo "======================FIRMWARE!======================"
	@avrdude -c usbasp -p m88p -B 8 -U flash:w:"$(PROJECT).hex":i -U lfuse:w:0xFF:m -U hfuse:w:0xDE:m -U efuse:w:0x01:m
#	@avrdude -c usbasp -p m88p -B 4 -U flash:w:"$(PROJECT).hex":i -U lfuse:w:0xFF:m -U hfuse:w:0xDF:m -U efuse:w:0x01:m

## Read Firmware
readflash: ${TARGET}
	@echo "======================READ FIRMWARE!======================"
	@avrdude -c usbasp -p m88p -B 4 -U flash:r:"firmware_readed.hex":r
## Read Firmware
readeeprom: ${TARGET}
	@echo "======================READ FIRMWARE!======================"
	@avrdude -c usbasp -p m88p -B 2 -U eeprom:r:"eeprom_readed.hex":r


## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) $(PROJECT).elf dep/* $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss

## Other dependencies
#-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

