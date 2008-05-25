# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

KERN=kaiser
KERN_OBJS=multiboot.o init.o init_paging.o kern.o
all: kernel
clean:
	$(RM) *.o *.bin $(KERN)

kernel: $(KERN)
kaiser: $(KERN_OBJS)
	$(LD) -s -Ttext 0xc0001000 -e 0x101000 $^ -o $@
multiboot.o: multiboot.S $(INCLUDE)/multiboot.h
init.o: init.S
kern.o:
