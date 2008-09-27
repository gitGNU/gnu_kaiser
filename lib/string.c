/*
 * string.c - string manipulation code
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

#include <lib/string.h>

/*
 * We make no guarantee these algorithms are correct since ignite played with them >_>
 */

unsigned int strlen (const char *s) {
	const char *p = s;

	while (*p) p++;
	return p - s;
}

void *memset (void *_s, int c, unsigned int len) {
	char *s = _s;

	for (; len; len--, s++) *s = c;
	return _s;
}

void *memcpy (void *_d, const void *_s, int len) {
	char *d = _d;
	const char *s = _s;

	for (; len; len--, d++)	*d = *(s++);
	return _d;
}
