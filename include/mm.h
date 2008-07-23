/*
 * mm.h - memory management struct and function definitions
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
 
#ifndef __MM_H__
#define __MM_H__
#define MM_BASE   0x400000    /* 4MB */
#define PAGE_SZ   4096      /* 4KiB pages */
#define PG_BOUND  0x00100000    /* 1MB page group boundary */
#define VM_BASE   0xc0000000
#define PG_SZ    (PG_BOUND / PAGE_SZ)  /* size in pages */
#define PG_FLAG_BASE  (1 << 0)
#define PG_FLAG_FULL  (1 << 1)
#define MM_FLAG_ALLOCD  (1 << 0)
#ifndef __ASM__
#undef MM_BASE
#define MM_BASE    (mm_pgroup_t *)0x400000 /* 4MB */
/* non ASM stuff goes here */

typedef struct mm_pgroup mm_pgroup_t;
typedef struct mm_mmap mm_mmap_t;

struct mm_pgroup {
	unsigned int  pg_magic;  /* magic value */
	unsigned int  pg_flags;  /* flags */
	mm_pgroup_t  *prev, *next;  /* doubly linked */
} __attribute__ ((packed));

struct mm_mmap {
	unsigned int  mm_flags;  /* flags */
	unsigned int  mm_vaddr;  /* used for paging */
	unsigned int  mm_base;  /* physical base address */
	unsigned short  mm_limit;  /* limit in pages */
	unsigned short  mm_tid;    /* the tid that owns the mmap */
} __attribute__ ((packed));

void mm_init (void);
void *mm_alloc (void *, unsigned short);

mm_pgroup_t *mm_pgalloc (void);

static void __mm_flag_if_full (mm_pgroup_t *);
void *__mm_pagedir (void);

int __mm_paging (void);

int __mm_highmem (void);

#endif /* __ASM__ */
#endif /* __MM_H__ */
