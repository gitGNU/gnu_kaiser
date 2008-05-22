# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

ARCH=$(shell uname -m | \
	sed s/i.86/i386/)
BUILTINS=lib/built-in.o kern/built-in.o
INCLUDE=$(PWD)/include
CFLAGS= -I$(INCLUDE) -nostdlib -nostdinc -O0 -ffreestanding
ASFLAGS=$(CFLAGS)

export ARCH INCLUDE CFLAGS ASFLAGS

all: arch/$(ARCH)/boot/kern.o
	$(MAKE) all   -C arch
	$(MAKE) all   -C fs
clean:
	$(MAKE) clean -C lib
	$(MAKE) clean -C arch
	$(MAKE) clean -C kern
	$(MAKE) clean -C fs

arch/$(ARCH)/boot/kern.o: $(BUILTINS)
	$(CC) $(CFLAGS) -Wl,-r $^ -o $@
lib/built-in.o:
	$(MAKE) all -C lib
kern/built-in.o:
	$(MAKE) all -C kern
