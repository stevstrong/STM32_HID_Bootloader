TARGET = hid_bootloader

DEVICE = STM32F10X_MD

VECTOR_TABLE_OFFSET = 0x0000

SRCS = main.c usb.c hid.c led.c

DEVICE_SRCS += CMSIS/Device/ST/STM32F10x/Source/Templates/gcc/startup_stm32f10x_md.s
DEVICE_SRCS += system_stm32f10x.c

INCLUDE_DIRS += -I .
INCLUDE_DIRS += -I CMSIS/Device/ST/STM32F10x/Include 
INCLUDE_DIRS += -I CMSIS/Include

#LINKER_SCRIPT = STM32F103C8T6.ld
#TARGETFLAGS= -DTARGET_GENERIC_F103_PC13
#LINKER_SCRIPT = STM32F103CBT6.ld
#TARGETFLAGS= -DTARGET_MAPLE_MINI

SRCS += $(DEVICE_SRCS)
OBJS = $(addsuffix .o,  $(basename $(SRCS)))

ASFLAGS += -mcpu=cortex-m3 -mthumb

CFLAGS += -mcpu=cortex-m3 -mthumb -Wall -Os
CFLAGS += -fno-common -static
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -specs=nano.specs -specs=nosys.specs
CFLAGS += $(INCLUDE_DIRS)
CFLAGS += -D$(DEVICE)
CFLAGS += -DVECTOR_TABLE_OFFSET=$(VECTOR_TABLE_OFFSET)
CFLAGS += $(TARGETFLAGS)

LDFLAGS += -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--print-memory-usage
LDFLAGS += -T$(LINKER_SCRIPT)

CC = compiler/bin/arm-none-eabi-gcc
AS = compiler/bin/arm-none-eabi-as
LD = compiler/bin/arm-none-eabi-ld
OBJDUMP = compiler/bin/arm-none-eabi-objdump
OBJCOPY = compiler/bin/arm-none-eabi-objcopy
SIZE = compiler/bin/arm-none-eabi-size
GDB = compiler/bin/arm-none-eabi-gdb

ECHO = echo
RM = rm

.PHONY: all build output info size clean flash

all: $(SRCS) clean gccversion build output info size

maple-mini: $(SRCS) clean gccversion build_maple-mini copy_maple_mini info size
generic-pc13: $(SRCS) clean gccversion build_generic-pc13 copy_generic-pc13 info size

build: $(TARGET).elf

build_maple-mini: TARGETFLAGS= -DTARGET_MAPLE_MINI
build_maple-mini: LINKER_SCRIPT=STM32F103CBT6.ld
build_maple-mini: $(TARGET).elf $(TARGET).bin
copy_maple_mini:
	cp $(TARGET).bin bootloader_only_binaries/hid_maple_mini.bin

build_generic-pc13: TARGETFLAGS= -DTARGET_GENERIC_F103_PC13
build_generic-pc13: LINKER_SCRIPT=STM32F103C8T6.ld
build_generic-pc13: $(TARGET).elf $(TARGET).bin
copy_generic-pc13:
	cp $(TARGET).bin bootloader_only_binaries/hid_generic_pc13.bin

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) -o "$@"

#.SECONDARY: $(OBJS)

#%.o: %.c
#	$(CC) $(CFLAGS) -c "$<" -o "$@"

#%.o: %.s
#	$(AS) $(ASFLAGS) -c "$<" -o "$@"

#%.s : %.c
#	$(CC) -S $(CFLAGS) $< -o $@

output: $(TARGET).hex $(TARGET).bin

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

gccversion:
	@$(CC) --version

info: $(TARGET).elf
	$(OBJDUMP) -x -S $(TARGET).elf > $(TARGET).lst
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis
	$(SIZE) $(TARGET).elf > $(TARGET).size

size: $(TARGET).elf
	$(SIZE) $(TARGET).elf

clean:
	$(RM) -f $(TARGET).elf
	$(RM) -f $(TARGET).bin
	$(RM) -f $(TARGET).hex
	$(RM) -f $(TARGET).size
	$(RM) -f $(TARGET).lst
	$(RM) -f $(TARGET).dis
	$(RM) -f $(TARGET).map
	$(RM) -f $(OBJS)

