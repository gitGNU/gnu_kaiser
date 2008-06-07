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
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <pit.h>
#include <kb.h>

#define PRINT_COLOUR_CHANGE(msg, start, delta) vga_set_foreground_colour(delta);\
			     kprintf(msg);\
			     vga_set_foreground_colour(start)
/*
 * This whole file really needs over-hauling with a new way to
 * start the whole boot procedure, our ideas so far have been
 * a set of function pointers pointing to our initialisation
 * functions that get looped over and called in turn in order
 * to allow for easy extensibility within the kernel without
 * having to edit this file constantly
 */
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

	kprintf("Initialising GDT:\t");
	gdt_install();
	PRINT_COLOUR_CHANGE("[ok]\n", VGA_COLOUR_BROWN, VGA_COLOUR_LIGHT_GREEN);

	kprintf("Initialising IDT:\t");
	idt_install();
	PRINT_COLOUR_CHANGE("[ok]\n", VGA_COLOUR_BROWN, VGA_COLOUR_LIGHT_GREEN);

	kprintf("Initialising ISRs:\t");
	isr_install();
	PRINT_COLOUR_CHANGE("[ok]\n", VGA_COLOUR_BROWN, VGA_COLOUR_LIGHT_GREEN);

	kprintf("Initialising IRQs:\t");
	irq_install();
	PRINT_COLOUR_CHANGE("[ok]\n", VGA_COLOUR_BROWN, VGA_COLOUR_LIGHT_GREEN);

	kprintf("Installing system clock:\t");
	timer_install();
	PRINT_COLOUR_CHANGE("[ok]\n", VGA_COLOUR_BROWN, VGA_COLOUR_LIGHT_GREEN);

	kprintf("Installing keyboard:\t");
	keyboard_install();
	PRINT_COLOUR_CHANGE("[ok]\n", VGA_COLOUR_BROWN, VGA_COLOUR_LIGHT_GREEN);

	kprintf("%khai, I'm blue%k\n", VGA_COLOUR_LIGHT_BLUE);

	__asm__ __volatile__("sti"); /* Start interrupts */
	while (1) {
		/* we can simply halt here to wait for interrupts */
		__asm__ __volatile__("hlt");
	}
}

