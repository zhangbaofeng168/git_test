
DRIVERS-y := start.o
DRIVERS-y += init/build-in.o

objs := $(DRIVERS-y)

CROSS_COMPILE=arm-linux-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
NM=$(CROSS_COMPILE)nm


CFLAGS=-Wall -g -O2
DIR_INCLUDE = -I$(shell pwd)/include
TOPDIR	:= $(shell pwd)

export CC LD OBJCOPY OBJDUMP DIR_INCLUDE TOPDIR CFLAGS

boot.bin:subdirs $(objs)
	$(LD) -T./boot.lds -o boot.elf $(objs)
	$(OBJCOPY) -O binary -S boot.elf $@ 
	$(OBJDUMP) -D boot.elf > boot.dis
	$(NM) -n boot.elf > boot.map

.PHONY:clean
clean:
	find . \( -name '*.o' -o -name core -o -name ".*.flags" \) -type f -print \
	| grep -v lxdialog/ | xargs rm -f
	rm -f  boot.dis boot.bin boot boot.map boot.elf
	
include Rules.make
