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


unsigned char keyboard_map[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '#', /* first char ctrl */
	0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', /* first char left shift */
	0 /*right shift*/, '*'
	0/*alt*/, ' ', 0 /*caps*/, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0 /*f1->f10*/,
	0/*num lock*/, 0/*scroll lock*/, 0/*home*/, 0/*up*/, 0/*pg up*/, '-', 0/*left*/,
	0, 0/*right*/, '+', 0/*end*/, 0/*down*/, 0/*pg down*/, 0/*ins*/, 0/*del*/, 0, 0, 0,
	0, 0/*f11,f12*/, 0,/*all else undef'd*/
};

static struct keyboard_status {
	/*
	 * BIG ASSUMPTION: ONLY ONE KEYBOARD PRESENT
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
} keyboard_status;

inline int p_capslock(uint16_t status){ return status&0x01; }
inline int p_numlock(uint16_t status){ return status&0x02; }
inline int p_scrolllock(uint16_t status){ return status&0x04; }
inline int p_leftshift(uint16_t status){ return status&0x08; }
inline int p_rightshift(uint16_t status){ return status&0x10; }
inline int p_leftctrl(uint16_t status){ return status&0x20; }
inline int p_rightctrl(uint16_t status){ return status&0x40; }
inline int p_alt(uint16_t status){ return status&0x80; }
inline int p_super(uint16_t status){ return status&0x0100; }

#endif
