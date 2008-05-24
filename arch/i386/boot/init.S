// init.S - low level kernel initialisation, mainly for paging
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

#define OFF(x) (x - 0xc0000000 + 0x100000)

.text
.globl init

// we get passed here from multiboot.S
init:
	mov %ds, %ax
	mov %ax, %ss
	mov $OFF(init_stack_top), %esp
	call init_paging
	mov $OFF(init_pdir), %eax
	mov %eax, %cr3
	// for the jmp after enabling paging, we need to temporarily
	// map the page containing that instruction to the same address
	// but in virtual memory
	call get_eip

get_eip:
	pop %edx
	add $magic - get_eip, %edx
	mov %edx, %ebx
	shr $22, %ebx
	mov $OFF(init_ptable2), %eax
	or $3, %eax
	mov %cr3, %esi
	mov %eax, (%esi, %ebx, 4)
	mov %edx, %ebx
	shr $12, %ebx
	and $0x3ff, %ebx
	mov %edx, %eax
	and $0xfffff000, %eax
	or $3, %eax
	mov $OFF(init_ptable2), %esi
	mov %eax, (%esi, %ebx, 4)
	mov $init_stack_top, %esp
	mov $paged, %ecx
	mov %cr0, %eax
	or $0x80000000, %eax
	mov %eax, %cr0

magic:
	jmp *%ecx

// yeah, we're just going to halt now, so what's the difference?
// we're halting in virtual memory! :D
paged:
	// get rid of the no longer needed PDE and PTE
	xor %eax, %eax
	mov %edx, %ebx
	shr $22, %ebx
	mov $init_pdir, %esi
	mov %eax, (%esi, %ebx, 4)
	shr $12, %edx
	and $0x3ff, %edx
	mov $init_ptable2, %esi
	mov %eax, (%esi, %edx, 4)
	hlt
	.bss
	.align 4096
	.lcomm init_stack, 4096

init_stack_top:	
	.globl init_pdir
	.lcomm init_pdir, 4096
	.globl init_ptable
	.lcomm init_ptable, 4096
	.lcomm init_ptable2, 4096

