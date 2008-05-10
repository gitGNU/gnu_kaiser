/*
 * mm.c - memory management code
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

#include <mm.h>
#include <errno.h>
#include <klibc/string.h>

/* initialise memory management system */
void mm_init () {
	mm_pgroup_t *pg;
	mm_mmap_t *mem;

	pg = MM_BASE;
	memset (pg, 0, PAGE_SZ); /* zero the pagegroup */
	pg->pg_flags |= PG_FLAG_BASE; /* set the pagegroup base flag */
	/* fill in first mmap entry (counts free space) */
	mem = (mm_mmap_t *)(++pg);
	mem->mm_base = (unsigned int) pg + PAGE_SZ - sizeof (*pg);
	mem->mm_limit = PG_SZ - 1;
}

/* allocate a page group */
mm_pgroup_t *mm_pgalloc () {
	mm_pgroup_t *pg, *retval;
	mm_mmap_t *mem;

	for (pg = __mm_paging() ? VM_BASE : MM_BASE; pg->next; pg = pg->next);
	retval = (mm_pgroup_t *) PTR_ERR (ENOMEM);
	if ((unsigned int) pg + PG_BOUND * 2 > __mm_highmem())
		return retval;
	pg->next = pg + PG_BOUND / sizeof (*pg);
	memset (pg->next, 0, PAGE_SZ);
	pg->next->prev = pg;
	pg = pg->next;
	mem = (mm_mmap_t *)(++pg);
	mem->mm_base = (unsigned int) pg + PAGE_SZ - sizeof (*pg);
	mem->mm_limit = PG_SZ - 1;
	return pg;
}

/* allocate an mmap */
void *mm_alloc (void *vaddr, unsigned short limit) {
	mm_pgroup_t *pg;
	mm_mmap_t *mem, tmp;
	int found;
	void *retval;

	/* first find a pg with free space */
	retval = (void *) PTR_ERR (EINVAL);
	if (limit >= PG_SZ)
		return retval;
	for (pg = __mm_paging() ? VM_BASE : MM_BASE;
		pg && (pg->pg_flags & PG_FLAG_FULL); pg = pg->next);
	if (!pg) {
		retval = pg = mm_pgalloc();
		if (PTR_ISERR (retval)) return retval;
	}
	found = 0;
	while (!found) {
		for (mem = (mm_mmap_t *)(++pg);
			mem < (mm_mmap_t *)(pg + PAGE_SZ / sizeof (*mem) - 1);
			++mem)
		{
			if (mem->mm_flags & MM_FLAG_ALLOCD) continue;
			if (mem->mm_limit < limit) continue;
			mem->mm_flags |= MM_FLAG_ALLOCD;
			found = 1;
			break;
		}
		if (found) break;
		if (pg->next) {
			pg = pg->next;
			continue;
		}
		retval = pg = mm_pgalloc();
		if (PTR_ISERR (retval)) return retval;
	}
	__mm_flag_if_full (pg);
	retval = (void *) mem->mm_base;
	if (limit == mem->mm_limit) return retval;
	memset (&tmp, 0, sizeof (tmp));
	tmp.mm_base = mem->mm_base + limit * PAGE_SZ;
	tmp.mm_limit = mem->mm_limit - limit;
	tmp.mm_vaddr = NULL;
	mem->mm_limit = limit;
	mem->mm_vaddr = vaddr;
	for (mem = (mm_mmap_t *)(++pg);
		mem < (mm_mmap_t *)(pg + PAGE_SZ / sizeof (*mem) - 1); ++mem)
	{
		if (mem->mm_base) continue;
		memcpy (mem, &tmp, sizeof (tmp));
	}
	return retval;
}

static void __mm_flag_if_full (mm_pgroup_t *pg) {
	mm_mmap_t *mem;
	int full;

	for (mem = (mm_mmap_t *)(++pg), full = 1;
		mem < (mm_mmap_t *)(pg + PAGE_SZ / sizeof (*mem) - 1); ++mem)
		if (!(mem->mm_flags & MM_FLAG_ALLOCD)) full = 0;
	if (full) pg->pg_flags |= PG_FLAG_FULL;
}
