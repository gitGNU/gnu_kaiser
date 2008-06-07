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
/* These numbers are purely made up, are they good enough? */
#define KB_ERROR 128
#define KB_ESCAPE 27
#define KB_LEFT_CONTROL 129
#define KB_LEFT_SHIFT 130
#define KB_RIGHT_SHIFT 131
#define KB_LEFT_ALT 132
#define KB_CAPS_LOCK 133
#define KB_F1 134
#define KB_F2 135
#define KB_F3 136
#define KB_F4 137
#define KB_F5 138
#define KB_F6 139
#define KB_F7 140
#define KB_F8 141
#define KB_F9 142
#define KB_F10 143
#define KB_NUM_LOCK 144
#define KB_SCROLL_LOCK 145
#define KB_HOME 146
#define KB_UP 147
#define KB_PAGE_UP 148
#define KB_LEFT 149
#define KB_5 150
#define KB_RIGHT 151
#define KB_END 152
#define KB_DOWN 153
#define KB_PAGE_DOWN 154
#define KB_INS 155
#define KB_DEL 156
#define KB_ALT_SYSRQ 157
#define KB_BLANK 158
#define KB_F11 159
#define KB_F12 160


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
