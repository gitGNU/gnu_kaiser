/*
 * gdt.h - GDT structs and function declarations
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

#ifndef __GDT_H__
# define __GDT_H__
/*
 * A GDT entry, containing the info we'll push
 * onto the processor during initialisation.
 */
struct gdt_entry {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed)); /*prevent compiler optimisation*/

struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed)); /*prevent compiler optimisation*/

typedef struct gdt_entry gdt_entry_t;
typedef struct gdt_ptr   gdt_ptr_t;

extern void gdt_flush();
void gdt_install();
void gdt_set_gate(int, unsigned long, unsigned long, unsigned char, unsigned char);
#endif
