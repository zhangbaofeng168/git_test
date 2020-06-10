CROSS_COMPILE=arm-linux-
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
NM=$(CROSS_COMPILE)nm
CFLAGS=-Wall -g

objs:=start.o

boot.bin:$(objs)
	$(LD) -Ttext 0x33e00000 -o boot.elf $^
	$(OBJCOPY) -O binary -S boot.elf $@ 
	$(OBJDUMP) -D boot.elf > boot.dis
	$(NM) -n boot.elf > boot.map
%o:%c
	$(CC) $(CFLAGS) -c -o $@ $<
%o:%S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(objs) boot.elf boot.dis boot.map boot.bin
	