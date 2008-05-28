# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.


# these are the files that will go into the kernel,
# please organize them
FILES = \
vga.c            

# we may need to mod this a little later so it's possible
# to have easier control of what is put into seperate object files
# and, how they can perhaps be linked together more efficiently
# - austin

all: built-in.o
clean:
	$(RM) *\.o
built-in.o: $(FILES)
	$(CC) $(CFLAGS) -Wl,-r $^ -o $@
