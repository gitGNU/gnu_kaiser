/*
 * multiboot.h - define stuff for the multiboot standard
 *
 * Copyright (C) 2008 John 'Ykstort' Doyle
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

#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__
#define MULTIBOOT_HEADER_MAGIC	0x1BADB002
#define MULTIBOOT_HEADER_FLAGS	0x00000001
#define MBIF_MEM	(1 << 0)	/* mbi_mem_lower and mbi_mem_higher */
#define MBIF_MAPS	(1 << 6)	/* mbi_mmaps */
#define MBIF_NAME	(1 << 9)	/* mbi_name */
#ifndef __ASM__
/* non asm stuff goes here */

#include <asm/stddef.h>

typedef struct elf_section_header_table {
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
} elf_section_header_table_t;

typedef struct multiboot_header {
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
} multiboot_header_t;

typedef struct multiboot_info {
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	union {
		elf_section_header_table_t elf_sec;
	} u;
	uint32_t mmap_length;
	uint32_t mmap_addr;
} multiboot_info_t;

#endif /* __ASM__ */
#endif /* __MULTIBOOT_H__ */
