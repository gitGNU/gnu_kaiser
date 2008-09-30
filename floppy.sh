#/bin/sh

losetup /dev/loop0 floppy.img
mount /dev/loop0 ./flop
cp kaiser ./flop/kaiser
umount flop
losetup -d /dev/loop0
