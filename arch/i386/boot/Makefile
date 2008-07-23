# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

KERN=kaiser
KERN_OBJS=multiboot.o init.o kern.o gdt.o idt.o isr.o irq.o page.o asm.o mm.o
all: kernel
clean:
	$(RM) *.o *.bin $(KERN)

kernel: $(KERN)

kaiser: $(KERN_OBJS)
	$(LD) -Ttext 0x100000 -s $^ -o $@

multiboot.o: multiboot.S $(INCLUDE)/multiboot.h

init.o: init.c

gdt.o: gdt.c

idt.o: idt.c

asm.o: asm.S

isr.o: isr.c

irq.o: irq.c

pit.o: pit.c

kb.o: kb.c

mm.o: mm.c

page.o: page.c

kern.o:
