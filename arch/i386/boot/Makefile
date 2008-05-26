# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

KERN=kaiser
KERN_OBJS=multiboot.o init.o kern.o
all: kernel
clean:
	$(RM) *.o *.bin $(KERN)

kernel: $(KERN)

kaiser: $(KERN_OBJS)
	$(LD) -s $^ -o $@

multiboot.o: multiboot.S $(INCLUDE)/multiboot.h

init.o: init.c

kern.o:
