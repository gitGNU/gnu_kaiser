/*
 * vga.h - low-level vga driver header
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

#ifndef __VGA_H__
#define __VGA_H__
/* using 80x25 because bochs uses it */
/* TODO: get textmode resolution from bios/vga */
#define VGA_XRES	80
#define VGA_YRES	25
#define VGA_ATTR	0x7	/* light grey on black */
#define VGA_TABSTOP	4
#define VGA_PAGES	16	/* 16 pages to scroll through :D */
#define VGA_CTEXTMEM	0xb8000	/* colour text memory */
#define BUGGER		"malloc failed :("

void vga_init (void);
void vga_write (const char *, int);
void vga_update (void);
void vga_clear (void);
void vga_setattr (char);
char vga_getattr (void);
void vga_setpos (int, int);
void vga_getpos (int *, int *);
void vga_setres (int, int);
void vga_getres (int *, int *);
int vga_setscroll (int);

/* some inlines for ease of use etc */
static inline int vga_pagescroll (int pages) {
	int xres, yres;

	vga_getres (&xres, &yres);
	return vga_setscroll (pages * yres);
}
static inline int vga_pageup (void) {
	return vga_pagescroll (-1);
}
static inline int vga_pagedown (void) {
	return vga_pagescroll (1);
}

#endif /* __VGA_H__ */
