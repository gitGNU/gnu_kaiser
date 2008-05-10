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
#define MB_MAGIC	0x1badb002
#define MB_FLAGS	0x00000001
#define MBIF_MEM	(1 << 0)	/* mbi_mem_lower and mbi_mem_higher */
#define MBIF_MAPS	(1 << 6)	/* mbi_mmaps */
#define MBIF_NAME	(1 << 9)	/* mbi_name */
#ifndef __ASM__
/* non asm stuff goes here */

/* im goddamn lazy */
extern long multiboot_info;

/*struct mbi {
 *	long	flags;
 *	long	mem;
 *	long	bootdev;
 *	char	*cmdline;
 */

#endif /* __ASM__ */
#endif /* __MULTIBOOT_H__ */
