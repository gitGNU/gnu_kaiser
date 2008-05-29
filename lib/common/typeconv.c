/*
 * typeconv.c - commonly used type conversion code
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

#include <asm/stddef.h>

/* Convert an integer to an ASCII string.
 * buf: The place to store the output.
 * buflen: The number of chars in buf.
 * base: Base to be used to represent the number.
 * num: The integer to convert.
 *
 * Returns 1 on success, 0 if buf is too small to hold the resulting string.
 * WARNING: If 0 is returned, the contents of buf is undefined.
 */
int int_to_ascii(char *buf, size_t buflen, int base, int32_t num) {
	char *p = buf;
	char *p1, *p2;
	int rem; /* remainder */
	uint32_t unum = num;

	if (base == 10 && num < 0) {
		*p++ = '-';
		buflen--;
		buf++; /* So we don't put the minus sign at the end when
			* reversing */
		unum = -num;
	}

	/* Convert the integer to a string, being careful not to cause of BoF */
	do {
		rem = unum % base;
		*p++ = (rem < 10) ? rem + '0' : rem + 'a' - 10;
		buflen--;
	} while ((unum /= base) && buflen);

	if (!buflen)
		return 0;

	/* Terminate the string */
	*p = 0;

	/* Reverse the digits */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return 1;
}

