/*
 * init.c - C entry point
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

#include <multiboot.h>
#include <vga.h>
#include <lib/kprintf.h>

#define CHECK_FLAG(flags,bit) ((flags) & (1<<(bit)))

void init(unsigned long magic, unsigned long addr) {
	multiboot_info_t *mbi;
	char buf[4];
	mbi = (multiboot_info_t *)addr;

	/* Initialise the VGA system and clear the screen */
	vga_init();
	vga_set_foreground_colour(VGA_COLOUR_BROWN);
	vga_set_background_colour(VGA_COLOUR_BLACK);
	vga_clear_screen();

	kprintf("Loading Kaiser...\n");
	kprintf("Initialising components...\n");
	/*test GDT*/
	kprintf("Initialising GDT:\t");
	gdt_install();
	kprintf("[ok]\n");
}

