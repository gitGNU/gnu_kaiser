# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

OBJS=string.o kprintf.o common.o elf_symtab.o

all: built-in.o

clean:
	$(RM) *.o
	$(MAKE) clean -C common

built-in.o: $(OBJS)
	$(CC) $(CFLAGS) -Wl,-r $^ -o $@

string.o: string.c $(INCLUDE)/lib/string.h

kprintf.o: kprintf.c

elf_symtab.o: elf_symtab.c

common.o:
	$(MAKE) all -C common

