# Makefile

###############################################################################

PROGRAM  = stm32-uart
CROSS   ?= arm-none-eabi
OBJS     = uart.o 

###############################################################################

ARCH_FLAGS = -DSTM32F1 -mthumb -mcpu=cortex-m3 -msoft-float -mfix-cortex-m3-ldrd
LDSCRIPT   = ../libopencm3/lib/stm32/f1/stm32f103xb.ld
LIBOPENCM3 = ../libopencm3/lib/libopencm3_stm32f1.a
OPENCM3_MK = lib/stm32/f1

###############################################################################

CC       = $(CROSS)-gcc
LD       = $(CROSS)-ld
OBJCOPY  = $(CROSS)-objcopy
OBJDUMP  = $(CROSS)-objdump
SIZE     = $(CROSS)-size

ELF      = $(PROGRAM).elf
BIN      = $(PROGRAM).bin
MAP      = $(PROGRAM).map
DMP      = $(PROGRAM).out

all:
	@make firmware

CFLAGS  += -O3 -Wall -g
CFLAGS  += -fno-common -ffunction-sections -fdata-sections
CFLAGS  += $(ARCH_FLAGS) -I../libopencm3/include/ $(EXTRA_CFLAGS)

LIBC     = $(shell $(CC) $(CFLAGS) --print-file-name=libc.a)
LIBNOSYS = $(shell $(CC) $(CFLAGS) --print-file-name=libnosys.a)
LIBGCC   = $(shell $(CC) $(CFLAGS) --print-libgcc-file-name)

# LDPATH is required for libopencm3 ld scripts to work.
LDPATH   = ../libopencm3/lib/
LDFLAGS += -L$(LDPATH) -T$(LDSCRIPT) -Map $(MAP) --gc-sections
LDLIBS  += $(LIBOPENCM3) $(LIBC) $(LIBNOSYS) $(LIBGCC)

firmware: $(LIBOPENCM3) $(BIN) $(DMP) size

$(ELF): $(LDSCRIPT) $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LDLIBS)

$(DMP): $(ELF)
	$(OBJDUMP) -d $< > $@

%.bin: %.elf
	$(OBJCOPY) -S -O binary $< $@

%.o: %.c board.h
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBOPENCM3):
	CFLAGS="$(CFLAGS)" make -C ../libopencm3 $(OPENCM3_MK) V=1


.PHONY: clean size

clean:
	rm -f $(OBJS) $(ELF) $(BIN) $(MAP) $(DMP) 


size: $(PROGRAM).elf
	@echo ""
	@$(SIZE) $(PROGRAM).elf
	@echo ""
