# Copyright (C) 2008 Austin 'thoughtpolice' Siepp
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.

FILESYSTEMS =

all: fs

fs: 
	for x in $(FILESYSTEMS); do make -C $$x || exit 1; done

clean:
	for x in $(FILESYSTEMS); do make -C $$x clean || exit 1; done
