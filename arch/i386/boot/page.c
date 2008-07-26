/*
 * page.c - page init code
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

#include <page.h>
#include <kmalloc.h>
#include <isr.h>
#include <asm/stddef.h>
#include <lib/string.h>
#include <lib/kprintf.h>
#include <kheap.h>

extern heap_t *kheap;

/* first, let's sort out our bitmap */

#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

uint32_t *frames;
uint32_t number_frames;
/* start_address defined for us in kmalloc.h */

static void set_frame(uint32_t frame_address){
	uint32_t frame = frame_address/0x1000;
	uint32_t index = INDEX_FROM_BIT(frame);
	uint32_t offset = OFFSET_FROM_BIT(frame);
	frames[index] |= (0x1 << offset);
}

static uint32_t clear_frame(uint32_t frame_address){
	uint32_t frame = frame_address/0x1000;
	uint32_t index = INDEX_FROM_BIT(frame);
	uint32_t offset = OFFSET_FROM_BIT(frame);
	return (frames[index] & (0x1 << offset));
}

static uint32_t first_frame(){
	uint32_t i, j;
	for(i=0; i<INDEX_FROM_BIT(number_frames); i++){
		if(frames[i] != 0xFFFFFFFF){
			for(j=0; j<32;j++){
				uint32_t to_test = 0x1<<j;
				if(!(frames[i]&to_test))
					return i*4*8+j;
			}
		}
	}
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable){
	if(page->frame != 0)
		return;
	uint32_t index = first_frame();
	if(index == (uint32_t)-1)
		/* NO FREE FRAMES! we need to panic! */
		;
	set_frame(index*0x1000);
	page->present = 1;
	page->rw = (is_writeable)?1:0;
	page->user = (is_kernel)?0:1;
	page->frame = index;
}

void free_frame(page_t *page){
	uint32_t frame;
	if(!(frame=page->frame))
		return;
	clear_frame(frame);
	page->frame = 0x0;
}

void init_paging(){
	uint32_t mem_end_page = 0x1000000;
	number_frames = mem_end_page / 0x1000;
	frames = (uint32_t *)kmalloc(INDEX_FROM_BIT(number_frames));
	memset(frames, 0, INDEX_FROM_BIT(number_frames));
	
	kernel_directory = (page_directory_t *)kmalloc_a(sizeof(page_directory_t));
	memset(kernel_directory, 0, sizeof(page_directory_t));
	current_directory = kernel_directory;

	int i=0;
	for(i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		get_page(i, 1, kernel_directory);
	i = 0;
	while(i<start_address+0x1000){
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
		i += 0x1000;
	}
	
	for (i = KHEAP_START; i < KHEAP_START+KHEAP_INITIAL_SIZE; i += 0x1000)
		alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
	switch_page_directory(kernel_directory);
	kheap = create_heap(KHEAP_START, KHEAP_START+KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
}

void switch_page_directory(page_directory_t *directory){
	current_directory = directory;
	__asm__ __volatile__("mov %0, %%cr3":: "r"(&directory->physical_tables));
	uint32_t cr0;
	__asm__ __volatile__("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000;
	__asm__ __volatile__("mov %0, %%cr0":: "r"(cr0));
}
page_t *get_page(uint32_t address, uint8_t make, page_directory_t *dir){
	address /= 0x1000;

	uint32_t table_index = address/1024;
	if(dir->tables[table_index])
		return &dir->tables[table_index]->pages[address%1024];
	else if(make){
		uint32_t tmp;
		dir->tables[table_index] = (page_table_t *)kmalloc_ap(sizeof(page_table_t), &tmp);
		memset(dir->tables[table_index], 0, 0x1000);
		dir->physical_tables[table_index] = tmp | 0x7;
		return &dir->tables[table_index]->pages[address%1024];
	} else
		return 0;
}
