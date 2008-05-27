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
	int i;
	mbi = (multiboot_info_t *)addr;

	/* Initialise the VGA system and clear the screen */
	vga_init();
	vga_clear_screen();
	for (i = 0; i < 81; i++)
		vga_write_char('@');
}

