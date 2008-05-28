/*
 * kprintf.c - Print to the display when in text mode.
 *
 * Copyright (C) 2008 Oliver 'Ignite' Heard
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

#include <lib/kprintf.h>
#include <vga.h>

void kprintf(const char *fmt, ...) {
	const char *p = fmt;
	char **args = (char **) &fmt;
	int c;
	args++;

	while ((c = *p++) != '\0') {
		if ((c == '%' && *(p + 1) == '%') || c != '%') {
			vga_write_char(c);
			if (*(p + 1) == '%')
				*p++;
			continue;
		}/*
		else {
			c = *p++;
			switch (c) {
			case 'd':
			case 'i':
				
			}
		}*/
	}
}

