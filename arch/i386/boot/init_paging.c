/*
 * init_paging.c - Initialises memory paging
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

/* Physical address the kernrel image is loaded to by the bootloader.  */
#define PM_BASE		0x00100000
/* Virtual address to offset addresses with.  */
#define VM_BASE		0xc0000000
#define OFF(x)	(x - (VM_BASE - PM_BASE) / sizeof (*x))
#include <elf.h>
#include <asm/page.h>
#include <lib/string.h>

extern unsigned int init_pdir[];
extern unsigned int init_ptable[];

void init_vmap (void *, void *, unsigned int, long);
void init_paging (void);

void init_paging () {
	elf_ehdr_t *kern_ehdr;
	elf_phdr_t *phdr;
	unsigned int nr_phdrs, p;
	int i;

	p = (unsigned int) PM_BASE;
	kern_ehdr = (elf_ehdr_t *) PM_BASE;
	nr_phdrs = kern_ehdr->e_phnum;
	phdr = (elf_phdr_t *)(p + kern_ehdr->e_phoff);
	for (i = 0; i < nr_phdrs; ++i) {
		if (phdr->p_type == PT_LOAD
			&& phdr->p_memsz > phdr->p_filesz)
		{
			memset (phdr->p_offset + phdr->p_filesz, 0,
				PAGE_ALIGN (phdr->p_memsz
				- phdr->p_filesz));
		}
		++phdr;
	}
	init_vmap ((void *) PM_BASE, (void *) VM_BASE, PAGE_SIZE, PF_R);
	phdr = (elf_phdr_t *)(p + kern_ehdr->e_phoff);
	for (i = 0; i < nr_phdrs; ++i) {
		if (phdr->p_type == PT_LOAD) {
			init_vmap ((void *) (PM_BASE + phdr->p_offset),
					(void *) phdr->p_vaddr,
					phdr->p_memsz, phdr->p_flags);
		}
		++phdr;
	}
}

void init_vmap (void *_p, void *_v, unsigned int len, long flags) {
	unsigned int p, v, *pd, *pt, pde, pte;

	p = PAGE_ALIGN (_p);
	v = PAGE_ALIGN (_v);
	for (len = PAGE_ALIGN (len); len; len -= PAGE_SIZE) {
		pd = OFF (init_pdir);
		pde = v >> 22;
		if (pde != VM_BASE >> 22)
			return;
		if (!pd[pde])
			pd[pde] = ((unsigned int) OFF (init_ptable)
					| PAGE_FW | PAGE_FP);
		pt = (unsigned int *) (pd[pde] & 0xfffff000);
		pte = (v >> 12) & 0x3ff;
		if (!pt[pte])
			pt[pte] = (p | (flags & PAGE_FW) | PAGE_FP);
		v += PAGE_SIZE;
		p += PAGE_SIZE;
	}
}
