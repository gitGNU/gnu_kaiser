# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

OBJS=kb.o pit.o

all: built-in.o

clean:
	$(RM) *.o

built-in.o: $(OBJS)
	$(CC) $(CFLAGS) -Wl,-r $^ -o $@

kb.o: kb.c

pit.o: pit.c

