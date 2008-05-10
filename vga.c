/*
 * vga.c - generic VGA driver
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
#include <vga.h>
#include <errno.h>

static short	*vga_backbuffer, *vga_mem;
//short		*vga_backbuffer, *vga_mem;
static char	vga_attr;
static int	vga_ts;
static int	vga_xpos, vga_ypos;
static int	vga_xres, vga_yres;
static int	vga_scroll;

void vga_init () {
	vga_xres = VGA_XRES;
	vga_yres = VGA_YRES;
	vga_attr = VGA_ATTR;
	vga_ts = VGA_TABSTOP;
	vga_scroll = 0;
	vga_mem = (short *) mm_vmap (NULL, VGA_CTEXTMEM, VGA_MEMSZ);
	memset (vga_mem, 0, VGA_MEMSZ);
	vga_backbuffer = mm_valloc (NULL, VGA_MEMSZ / PAGE_SZ + 1);
	if (PTR_ISERR (vga_backbuffer)) {
		memcpy (vga_mem, BUGGER, strlen (BUGGER));
		halt();
	}
	memset (vga_backbuffer, 0, VGA_MEMSZ * VGA_PAGES);
	vga_xpos = vga_ypos = 0;
}

/*
 * XXX: maybe have this simply write whatever is thrown at it to
 * 	VGA memory and have a tty driver (abstracting this and
 * 	the keyboard driver (TODO)) handle special characters
 */
void vga_write (const char *s, int len) {
	int i, tab;
	short c, *vga_page;

	vga_page = vga_backbuffer + vga_scroll * vga_xres;
	for (i = 0; i < len; ++i) {
		switch (s[i]) {
			case '\b':
				vga_xpos--;
				break;
			case '\t':
				tab = vga_xpos % vga_ts;
				tab = tab ? tab : vga_ts;
				vga_xpos += tab;
				if (vga_xpos > vga_xres) vga_xpos = vga_xres;
				break;
			case '\n':
				vga_ypos += 1;
			case '\r':
				vga_xpos = 0;
				break;
		}
		if (s[i] < 0x20 || s[i] > 0x7e) continue;
		c = (short)((vga_attr << 8) | s[i]);
		vga_page[vga_ypos * vga_xres + vga_xpos] = c;
		vga_xpos++;
		if (vga_xpos > vga_xres) {
			vga_xpos = 0;
			vga_ypos++;
		}
		if (vga_ypos > vga_yres)
			vga_setscroll (1);
	}
	vga_update();
}

void vga_update () {
	short *vga_page;

	vga_page = vga_backbuffer + vga_scroll * vga_xres;
	memcpy (vga_mem, vga_page,
		vga_xres * vga_yres * sizeof (*vga_mem));
}

void vga_clear () {
	memset (vga_backbuffer, 0,
		VGA_PAGES * vga_xres * vga_yres * sizeof (*vga_backbuffer));
	vga_xpos = vga_ypos = vga_scroll = 0;
	vga_update();
}

void vga_setattr (char attr) {
	vga_attr = attr;
}

char vga_getattr () {
	return vga_attr;
}

void vga_setpos (int x, int y) {
	vga_xpos = x;
	vga_ypos = y;
}

void vga_getpos (int *x, int *y) {
	*x = vga_xpos;
	*y = vga_ypos;
}

void vga_setres (int xres, int yres) {
	vga_xres = xres;
	vga_yres = yres;
}

void vga_getres (int *xres, int *yres) {
	*xres = vga_xres;
	*yres = vga_yres;
}

int vga_setscroll (int n) {
	int newscroll, r, total_lines;

	newscroll = vga_scroll + n;
	total_lines = VGA_PAGES * vga_yres;
	if (newscroll < 0) {
		vga_scroll = 0;
		vga_update();
		return vga_scroll;
	}
	if (newscroll < total_lines) {
		vga_scroll = newscroll;
		vga_update();
		return vga_scroll;
	}
	/* number of lines to scroll off */
	r = newscroll - total_lines - 1;
	vga_scroll = total_lines - 1;
	memcpy (vga_backbuffer,
		vga_backbuffer + r * vga_yres, (total_lines - r) * vga_yres);
	/* zero the new lines */
	memset (vga_backbuffer + (total_lines - r) * vga_yres, 0, r * vga_yres);
	vga_update();
	return vga_scroll;
}
