SOURCES  = $(wildcard src/*.c)
OBJECTS  = $(patsubst %.c,%.o,$(SOURCES))
MAP      = main.map
MAKEFILE = Makefile

ifeq ($(OS),Windows_NT)
	ifeq ($(shell uname -o),Cygwin)
		RM= rm -rf
	else
		RM= del /q
	endif
else
	RM= rm -rf
endif

GCC_DIR = $(MSPGCC)/bin
SUPPORT_FILE_DIRECTORY = $(MSPGCC)/include
LDDIR = $(MSPGCC)/include/$(shell echo $(DEVICE) | tr A-Z a-z)

DEVICE  = MSP430FR5969
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb
OBJCOPY = $(GCC_DIR)/msp430-elf-objcopy
FLASHER = $(MSPFLASER)/MSP430Flasher
MAKETXT = srec_cat

CFLAGS   = -mmcu=$(DEVICE) -mlarge -mcode-region=either -mdata-region=lower -Og -Wall -g
LDFLAGS  = -T $(LDDIR).ld -L $(SUPPORT_FILE_DIRECTORY) -Wl,-Map,$(MAP),--gc-sections
INCLUDES = -I $(SUPPORT_FILE_DIRECTORY) -I driverlib

DRIVERLIB_SRC     = $(wildcard driverlib/*.c)
DRIVERLIB_OBJECTS = $(patsubst %.c,%.o,$(DRIVERLIB_SRC))

all: $(DEVICE).out $(DEVICE).txt 

$(DEVICE).out: $(OBJECTS) $(DRIVERLIB_OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(DEVICE).out

%.hex: %.out
	$(OBJCOPY) -O ihex $< $@

%.txt: %.hex
	$(MAKETXT) -O $@ -TITXT $< -I

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) $(OBJECTS)
	$(RM) $(MAP)
	$(RM) *.out
	$(RM) *.txt
	$(RM) *.hex

debug: all
	$(GDB) $(DEVICE).out

upload:
	LD_LIBRARY_PATH=$(MSPFLASER) DYLD_LIBRARY_PATH=$(MSPFLASER) $(FLASHER) -w $(DEVICE).txt -v -g -z [VCC]
