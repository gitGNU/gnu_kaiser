// multiboot.S - multiboot information processing and header for bootloader
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

// we'll have this in .text and linked first to ensure it comes within
// the first 8kB of the kernel image
.text

#define __ASM__
#include <multiboot.h>
#define OFF(x) (x-0xc0000000+0x100000)

.globl _start

_start:
	jmp copy_mbi

// this is the multiboot header, for GRUB (or any other
// multiboot compliant boot loader) to recognise our kernel
// as multiboot compliant and load it
mboot_hdr:
	_mboot_magic:
		.long MULTIBOOT_HEADER_MAGIC
	_mboot_flags:
		.long MULTIBOOT_HEADER_FLAGS
	_mboot_cksum:
		.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

copy_mbi:
	// ebx should contain a pointer to the mbi struct
	mov %ebx, %esi
	mov OFF(multiboot_info), %edi
	mov $mbi_sz, %ecx
	mov %ds, %ax			// copying ds to es just to be sure
	mov %ax, %es
	rep
	movsb
	// copying the mbi should do for now, init will further process it later
	// NOTE: jmp not call as we don't have a stack yet and don't need to ret
	//	to here anyway
	jmp init

// multiboot information structure
// provided by the bootloader
.data
.globl mutliboot_info
multiboot_info:
	_mbi_flags:
		.long 0
	_mbi_mem:
		.long 0, 0
	_mbi_boot_dev:
		.long 0
	_mbi_cmdline:
		.long 0
	_mbi_mods:
		.long 0, 0
	_mbi_syms:
		.long 0, 0, 0
	_mbi_mmap:
		.long 0, 0
	_mbi_drives:
		.long 0, 0
	_mbi_config:
		.long 0
	_mbi_name:
		.long 0
	_mbi_apm:
		.long 0
	_mbi_vbe:
		.long 0, 0, 0
		.word 0, 0, 0
.set mbi_sz, . - multiboot_info

