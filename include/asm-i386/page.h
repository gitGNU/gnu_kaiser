/*
 * page.h - define various things to do with paging
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

#ifndef __ASM_PAGE_H__
#define __ASM_PAGE_H__

#define PAGE_SIZE	0x00001000
#define PAGE_FP		(1 << 0)	/* present flag */
#define PAGE_FW		(1 << 1)	/* writable flag */
#define PAGE_MASK	(~(PAGE_SIZE - 1))
#define PAGE_ALIGN(x)	(((unsigned int) x + PAGE_SIZE - 1) & PAGE_MASK)

#endif /* !__ASM_PAGE_H__ */
