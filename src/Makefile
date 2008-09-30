# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

ARCH=$(shell uname -m | \
	sed s/i.86/i386/)
BUILTINS=lib/built-in.o kern/built-in.o arch/i386/video/built-in.o drivers/built-in.o
INCLUDE=$(BASE)/src/include
CFLAGS= -I$(INCLUDE) -nostdlib -nostdinc -O0 -ffreestanding -Wall -Wextra
ASFLAGS=$(CFLAGS)
SYMLINK=ln -s
LDFLAGS=-T../../../link.ld

export ARCH INCLUDE CFLAGS ASFLAGS SYMLINK LDFLAGS

all: bootstrap arch/$(ARCH)/boot/kern.o
	$(MAKE) all   -C fs
	$(MAKE) all   -C arch

# Prepare the environment for building
bootstrap:
	$(MAKE) setarch -C include

clean:
	$(MAKE) clean -C lib
	$(MAKE) clean -C arch
	$(MAKE) clean -C kern
	$(MAKE) clean -C fs
	$(MAKE) clean -C include
	$(MAKE) clean -C drivers

arch/$(ARCH)/boot/kern.o: $(BUILTINS)
	$(CC) $(CFLAGS) -Wl,-r $^ -o $@
lib/built-in.o:
	$(MAKE) all -C lib
kern/built-in.o:
	$(MAKE) all -C kern
drivers/built-in.o:
	$(MAKE) all -C drivers
arch/$(ARCH)/video/built-in.o:
	$(MAKE) all -C arch/$(ARCH)/video
