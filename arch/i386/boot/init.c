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
#include <irq.h>
#include <page.h>
#include <mm.h>
#include <kmalloc.h>
#include <kheap.h>

/*
 * This whole file really needs over-hauling with a new way to
 * start the whole boot procedure, our ideas so far have been
 * a set of function pointers pointing to our initialisation
 * functions that get looped over and called in turn in order
 * to allow for easy extensibility within the kernel without
 * having to edit this file constantly
 */
void init(unsigned long magic, unsigned long addr) {
	/* we need to check our magic flags and things here really */
	multiboot_info_t *mbi;
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
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	kprintf("Initialising IDT:\t");
	idt_install();
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	kprintf("Initialising ISRs:\t");
	isr_install();
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	kprintf("Initialising IRQs:\t");
	irq_install();
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	void *prepage = kmalloc(8);
	kprintf("Pre-paging, pointer: %x\n", prepage);
	kfree(prepage);

	kprintf("Initialising paging:\t");
	init_paging();
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	void *postpage = kmalloc(8);
	kprintf("Post-paging, pointer: %x\n", postpage);
	kfree(postpage);

	kprintf("Installing system clock:\t");
	timer_install();
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	kprintf("Installing keyboard:\t");
	keyboard_install();
	kprintf("%k[ok]\n", VGA_COLOUR_LIGHT_GREEN, -1);

	__asm__ __volatile__("sti"); /* Start interrupts */

	while (1) {
		/* we can simply halt here to wait for interrupts */
		__asm__ __volatile__("hlt");
	}
}

