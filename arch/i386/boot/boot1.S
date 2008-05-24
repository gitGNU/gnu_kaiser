// boot1.S - Crude stage1 bootloader for testing, loads sectors from the first
//	     cylinder of fd0 until it finds a sector with the word 0x0E0F in
//	     the final 2 bytes or an error occurs. Note that the second case
//	     will occur if boot1.S doesn't find an 0x0E0F marker in the first
//	     cylinder because it will simply try to read cylinder 0, sector
//	     x + 1, where x is the last sector on cylinder 0.
//	     boot1.S then loads a flat GDT, turns on protected mode, moves the
//	     kernel to 0x100000 (highmem) and finally jumps to the address in
//	     the kernel's ELF header's entry field.
// Copyright (C) 2008 John 'Ykstort' Doyle
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

.code16

#define __ASM__
#include <multiboot.h>
MBI_FLAGS = MBIF_MEM
ORG = 0x7c00
#define OFF(x) (ORG + x)
#define E_ENTRY(x) (x + 0x18)

ljmp $0, $OFF(_start)

// Error message incase something goes wrong
err:
	.string "Error loading kernel from fd0.\nPress any key..."

// Multiboot Information (filled in later according to MBI_FLAGS)
mbi:
	mbi_flags:
		.long MBI_FLAGS
	mbi_mem:
		.long 0, 0
	mbi_boot_dev:
		.long 0
	mbi_cmdline:
		.long 0
	mbi_mods:
		.long 0, 0
	mbi_syms:
		.long 0, 0, 0
	mbi_mmap:
		.long 0, 0
	mbi_drives:
		.long 0, 0
	mbi_config:
		.long 0
#ifdef LOADER_NAME
	mbi_name:
		.long OFF(LOADER_NAME)
#else
	mbi_name:
		.long 0
#endif
	mbi_apm:
		.long 0
	mbi_vbe:
		.long 0, 0, 0
		.word 0, 0, 0

// The all powerful GDT, we'll just have a simple flat setup
gdt:
	.long 0, 0	// null entry
	// code entry
	.word 0xffff	// limit
	.byte 0, 0, 0	// lower 3 bytes of base addr
	.byte 0x9a	// type byte
	.byte 0xcf	// flags nibble (higher) and top nibble of
			// limit (lower)
	.byte 0		// 4th and highest byte of base

	// data entry
	.word 0xffff
	.byte 0, 0, 0
	.byte 0x92
	.byte 0xcf
	.byte 0
.set gdt_sz, . - gdt
	
// gdtr, used to load the GDT
gdtr:
	.word gdt_sz
	.long OFF(gdt)

// number of sectors in the kernel, saved here
// for when copying from lower mem to higher mem
ksecs:
	.byte 0

// sectors per track on the floppy disc
dsecs:
	.byte 0

// cylinders per head - 1 (logical last index)
dcyls:
	.word 0

// heads per track - 1
dheds:
	.byte 0

// rest of the code starts here
_start:
	xor %ax, %ax
	mov %ax, %ds
	mov $ORG, %sp
	call fillmbi
	call loader
	call enable_a20
	cli
	lgdt OFF(gdtr)
	mov %cr0, %eax
	or $1, %al
	mov %eax, %cr0
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ljmp $0x8, $OFF(protmode)

// loader loads the kernel from subsequent sectors of
// the floppy drive one at a time to 0x10000 until it
// sees 0xE0F at the last word of a sector, denoting
// the last sector containing kernel code
//
// TODO: modify loader to work in protected mode and run it after
//	the switch so kernels bigger than 0x90000 can be loaded
// 	loader will also need to be modified to continue reading
//	sectors past the first cylinder for kernels bigger than
//	0xe000 can be loaded
loader:
	// query the disc parameters for a more robust loader
	mov $8, %ah
	mov $0, %dl
	int $0x13
	jc die
	movb %dh, OFF(dheds)
	mov %cl, %al
	and $0x3f, %al
	movb %al, OFF(dsecs)
	mov %ch, %al
	shr $6, %cl
	mov %cl, %ah
	movw %ax, OFF(dcyls)
	xor %cx, %cx
	mov %cx, %dx
	mov $4, %cl
	mov $0x1000, %ax
	mov %ax, %es
	mov %dx, %bx
1:
	mov $0x201, %ax
	int $0x13
	jc die
	inc %cl
	incb OFF(ksecs)
	add $0x200, %bx
	push %ds
	push %es
	pop %ds
	movw -2(%bx), %ax
	pop %ds
	cmp $0xe0f, %ax
	je 2f
	// kernel got too big, we have to do multiple cylinders
	// XXX: turns out you cycle heads before changing cylinders
	mov %cl, %al
	and $0x3f, %al
	cmpb OFF(dsecs), %al
	jle 1b
	inc %dh
	andw $0xffc0, %cx
	inc %cl
	cmpb OFF(dheds), %dh
	jle 1b
	mov $0, %dh
	mov %ch, %al
	shr $6, %cl
	mov %cl, %ah
	inc %ax
	mov %ah, %cl
	shl $6, %cl
	inc %cl
	mov %al, %ch
	cmpw OFF(dcyls), %ax
	jg die
2:
	ret

// this function enables the a20 gate for full highmem
enable_a20:
	cli
	mov $1, %ah
	call a20wait
	mov $0xad, %al	// disable keyboard cmd
	out %al, $0x64
	call a20wait
	mov $0xd0, %al	// read input cmd
	out %al, $0x64
	mov $2, %ah
	call a20wait
	in $0x60, %al	// read input
	push %eax
	mov $1, %ah
	call a20wait
	mov $0xd1, %al	// write output cmd
	out %al, $0x64
	call a20wait
	pop %eax
	or $2, %al	// enable a20 bit
	out %al, $0x60	// write output
	call a20wait
	mov $0xae, %al	// enable keyboard cmd
	out %al, $0x64
	call a20wait
	sti
	ret

a20wait:
3:
	in $0x64, %al
	test $2, %al
	jnz 3b
	ret

// fillmbi fills the mbi structure based on mbi_flags
SMAP = 0x50414d53
fillmbi:
	mov OFF(mbi_flags), %ebx
	test $MBIF_MEM, %ebx
	jz fillmbi_maps
	int $0x12		// lowmem bios call
	mov %ax, OFF(mbi_mem)
	mov $0x88, %ah		// extmem bios call
	int $0x15
	mov %ax, OFF(mbi_mem + 4)

fillmbi_maps:
	test $MBIF_MAPS, %ebx
	jz fillmbi_out
	xor %ebx, %ebx
	mov %ebx, %eax
	mov $0x1000, %ax
	mov %ax, %es
	shl $4, %eax
	add $4, %eax
	mov %eax, OFF(mbi_mmap + 4)
	mov $4, %di
	mov $20, %ecx
	mov $SMAP, %edx

fillmbi_maps_1:
	mov $0xe820, %ax	// mmap bios call
	int $0x15
	jc die
	cmp $SMAP, %eax
	jne die
	add $4, %ecx
	add %ecx, OFF(mbi_mmap)	// add to length
	mov %ecx, %es:-4(%di)
	add %cx, %di
	test %ebx, %ebx
	jnz fillbmi_maps_1

fillmbi_out:
	ret

// this is called if there is a problem in loader
die:
	mov $OFF(err), %si
	xor %ax, %ax
	mov %ax, %es
	mov $0x0e, %ah
4:
	lodsb
	test %al, %al
	jz 6f
	cmp $10, %al
	jne 5f
	mov $13, %al
	int $0x10
	mov $10, %al
5:
	int $0x10
	jmp 4b
6:
	xor %ax, %ax
	int $0x16
	movw $0x1234, 0x47c
	ljmp $0xffff, $0

// 32 bit protected mode code to copy the kernel into
// highmem and then jump to it
.code32

protmode:
	mov $0x010000, %esi
	mov $0x100000, %edi
	mov $0x80, %ecx
	xor %eax, %eax
	mov OFF(ksecs), %al
	imul %eax, %ecx
	rep movsl
	mov $OFF(mbi), %ebx
	mov E_ENTRY(0x100000), %ecx
	// TODO: setup a multiboot info struct and set %ebx to its location
	jmp *%ecx

