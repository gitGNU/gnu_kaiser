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
#include <lib/elf_symtab.h>
#include <vga.h>
#include <lib/kprintf.h>
#include <gdt.h>
#include <idt.h>
#include <elf.h>
#include <panic.h>
#include <isr.h>
#include <pit.h>
#include <kb.h>
#include <irq.h>
#include <page.h>
#include <mm.h>
#include <kmalloc.h>
#include <kheap.h>
#include <cpuid.h>

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
	init_symtable((Elf32_Shdr *)mbi->u.elf_sec.addr, mbi->u.elf_sec.num);

	/* Initialise the VGA system and clear the screen */
	vga_init();
	vga_set_foreground_colour(VGA_FG_BROWN);
	vga_set_background_colour(VGA_BG_BLACK);
	vga_clear_screen();

	kprintf("Loading Kaiser...\n");
	kprintf("Initialising components...\n");

	kprintf("Initialising GDT:\t");
	gdt_install();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	kprintf("Initialising IDT:\t");
	idt_install();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	kprintf("Initialising ISRs:\t");
	isr_install();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	kprintf("Initialising IRQs:\t");
	irq_install();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	void *prepage = kmalloc(8);
	kprintf("Pre-paging, pointer: %x\n", prepage);
	kfree(prepage);

	kprintf("Initialising paging:\t");
	init_paging();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	void *postpage = kmalloc(8);
	kprintf("Post-paging, pointer: %x\n", postpage);
	kfree(postpage);

	char *cpu_vendor = kmalloc(13);
	kprintf("Detecting CPU vendor:\t");
	kprintf("%k%s\n", VGA_FG_LIGHT_GREEN, cpuid_get_vendor_string(cpu_vendor));

	cpuinfo_t *cpu_info = kmalloc(sizeof(*cpu_info));
	kprintf("Detecting CPU information:\n");
	cpuid_get_info(cpu_info);
	kprintf("\tStepping: %i\n", cpu_info->stepping);
	kprintf("\tModel: %i\n", cpu_info->model);
	kprintf("\tFamily: %i\n", cpu_info->family);
	kprintf("\tType: %i\n", cpu_info->type);
	kprintf("\tExtended Model: %i\n", cpu_info->ext_model);
	kprintf("\tExtended Family: %i\n", cpu_info->ext_family);

	kprintf("Installing system clock:\t");
	timer_install();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	kprintf("Installing keyboard:\t");
	keyboard_install();
	kprintf("%k[ok]\n", VGA_FG_LIGHT_GREEN);

	__asm__ __volatile__("sti"); /* Start interrupts */

	while (1) {
		/* we can simply halt here to wait for interrupts */
		__asm__ __volatile__("hlt");
	}
}

