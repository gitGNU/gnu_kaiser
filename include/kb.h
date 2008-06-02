/*
 * kb.h - keyboard driver header
 *
 * Copyright (C) 2008 Andrew 'Seadog' Etches
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

#ifndef __KB_H__
#  define __KB_H__

#define P_CAPSLOCK(status)	((status)&0x80 ? 1:0)
#include <isr.h>
#include <asm/stddef.h>

struct keyboard_status {
	/*
	 * Any keys which have memory need to be kept track of
	 *
	 * uint16_t status bits:
	 * 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
	 *
	 * 0,1,2 = {caps,num,scroll}lock
	 * 3,4   = left/right shift
	 * 5,6   = left/right ctrl
	 * 7     = alt
	 * 8     = super
	 *
	 */
	uint16_t status;
};

void keyboard_handler(stack_rep_t *);
void keyboard_install();

#endif
