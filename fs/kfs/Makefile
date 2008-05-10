# Copyright (C) 2008 Austin 'thoughtpolice' Seipp
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

FILES = \
kfs.c

all: kfs

kfs:
	mkdir -p build
	$(CC) $(CFLAGS) -Wall $(FILES) -o build/kfs.ko  
clean:
	rm -f build/*
	rm -f *\.o
