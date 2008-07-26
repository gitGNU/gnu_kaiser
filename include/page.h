/*
 * page.h - page initialisation header
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __PAGE_H__
#define __PAGE_H__

#include <asm/stddef.h>

typedef struct page page_t;
typedef struct page_table page_table_t;
typedef struct page_directory page_directory_t;

struct page {
	int present  :1;
	int rw       :1;
	int user     :1;
	int accessed :1;
	int dirty    :1;
	int unused   :7;
	int frame    :20;
} __attribute__((packed));

struct page_table {
	page_t pages[1024];
} __attribute__((packed));

struct page_directory {
	page_table_t *tables[1024];
	uint32_t physical_tables[1024];
	uint32_t physical_address;
} __attribute__((packed));

void init_paging();
void switch_page_directory(page_directory_t *new);
page_t *get_page(uint32_t address, uint8_t make, page_directory_t *dir);

page_directory_t *kernel_directory;
page_directory_t *current_directory;

extern page_directory_t *kernel_directory;
extern page_directory_t *current_directory;
#endif
