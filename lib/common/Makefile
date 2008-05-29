# Copyright (C) 2008 Oliver 'Ignite' Heard
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

OBJS=typeconv.o

all: ../common.o

clean:
	$(RM) *.o

../common.o: $(OBJS)
	$(CC) $(CFLAGS) -Wl,-r $^ -o $@

typeconv.o: typeconv.c

