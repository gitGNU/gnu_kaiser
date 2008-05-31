/*
 * idt.c - IDT initialisation code
 *
 * Copyright (C) 2008 Andrew 'Seadog' Etches
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <idt.h>

idt_entry_t idt[256];
idt_ptr_t idt_pointer;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel,
		  unsigned char flags){
	idt[num].sel     = sel;
	idt[num].always0 = 0x00;
	idt[num].flags   = flags;
	idt[num].base_lo = (base & 0xFFFF); /* bottom 16 bits */
	idt[num].base_hi = (base >> 16) & 0xFFFF; /* top 16 bits */
}

void idt_install(){
	idt_pointer.limit = sizeof(idt_entry_t) * 256 - 1;
	idt_pointer.base = (int)&idt;
	memset(&idt, 0, sizeof(idt_entry_t)*256);

	/* load some ISRs here */

	idt_load();
}
