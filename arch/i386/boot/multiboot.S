// multiboot.S - multiboot information processing and header for bootloader
// Copyright (C) 2008 Oliver 'Ignite' Heard & Andrew 'Seadog' Etches
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

// Random stack size of 16KB
#define STACK_SIZE 0x4000

.globl _start

_start:
	jmp multiboot_entry

// Align 32 bits boundary
.align 4

// Multiboot header for multiboot compliant bootloaders
multiboot_header:
	.long MULTIBOOT_HEADER_MAGIC
	.long MULTIBOOT_HEADER_FLAGS
	.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

multiboot_entry:
	// Initialise stack pointer
	movl $(stack + STACK_SIZE), %esp

	// Reset EFLAGS
	pushl $0
	popf

	////
	// Push arguments for init() function onto the stack
	////
	pushl %ebx // Pointer to the multiboot info struct
	pushl %eax // Magic value

	// Enter C init() function
	call init

loop:
	hlt
	jmp loop

// Stack area
.comm stack, STACK_SIZE

