# Copyright (C) 2008 John 'Ykstort' Doyle
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

BASE=$(PWD)
export BASE

all:
	$(MAKE) all   -C src
clean:
	$(RM) kaiser
	$(MAKE) clean	-C src
