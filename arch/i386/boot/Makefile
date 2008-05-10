# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

IMG=fd0
IMGSZ=2880	# number of sectors
SECSZ=512
KERN=kaiser
KERN_OBJS=multiboot.o init.o init_paging.o kern.o
HELPERS=eof_kern
%.bin: %.o
	objcopy -O binary $< $@
all: bootstrap kernel image
clean:
	$(RM) *.o *.bin $(KERN) $(HELPERS) $(IMG)

kernel: $(KERN)
kaiser: $(KERN_OBJS)
	$(LD) -s -Ttext 0xc0001000 -e 0x101000 $^ -o $@
multiboot.o: multiboot.S $(INCLUDE)/multiboot.h
init.o: init.S
kern.o:

image: $(HELPERS)
	dd if=/dev/zero of=$(IMG) bs=$(SECSZ) count=$(IMGSZ)
	dd if=boot0.bin of=$(IMG) conv=notrunc
	dd if=boot1.bin of=$(IMG) bs=$(SECSZ) seek=1 conv=notrunc
	./eof_kern $(KERN)
	dd if=$(KERN) of=$(IMG) bs=$(SECSZ) seek=3 conv=notrunc
eof_kern: eof_kern.c
	$(CC) $(HELPER_CFLAGS) $^ -o $@

bootstrap: boot0.bin boot1.bin
boot0.bin: boot0.o
boot0.o:   boot0.S
boot1.bin: boot1.o
boot1.o:   boot1.S
