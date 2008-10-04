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
#include <lib/common.h>
#include <vga.h>


static void write_string(const char *str) {
	const char *p = str;
	while (*p != '\0') {
		vga_write_char(*p);
		p++;
	}
}

void kprintf(const char *fmt, ...) {
	const char *p = fmt;
	char **args = (char **) &fmt;
	char c;
	uint8_t orig_clr = vga_get_foreground_colour() | vga_get_background_colour();
	int reset_colour = 0;
	args++;

	while ((c = *p++) != '\0') {
		if (c != '%') {
			vga_write_char(c);
		}
		else {
			char buf[256];
			int iarg;
			char *sarg;
			c = *p++;
			switch (c) {
			case 'd':
			case 'i':
				iarg = (int) *args;
				int_to_ascii(buf, 256, 10, iarg);
				write_string(buf);
				args++;
				break;
			case 'u':
				iarg = (unsigned int)*args;
				int_to_ascii(buf, 256, 10, iarg);
				write_string(buf);
				args++;
				break;
			case 'x':
				iarg = (unsigned int)*args;
				write_string("0x");
				write_string(int_to_hex(iarg));
				args++;
				break;
			case '%':
				vga_write_char(c);
				break;
			case 's':
				sarg = (char *) *args;
				write_string(sarg);
				args++;
				break;
			case 'k':
				if (reset_colour) {
					reset_colour = 0;
					vga_set_foreground_colour(orig_clr);
					vga_set_background_colour(orig_clr);
				}
				else {
					reset_colour = 1;
					if ((int) *args > 0) {
						vga_set_foreground_colour((uint8_t)(int)*args);
						vga_set_background_colour(((uint8_t)(int)*args));
					}
					args++;
				}
				break;
			}
		}
	}
	if (reset_colour == 1) {
		vga_set_foreground_colour(orig_clr);
		vga_set_background_colour(orig_clr);
	}
}

