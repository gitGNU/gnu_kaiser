/*
 * kb.c - keyboard driver code
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

#include <kb.h>
#include <isr.h>
#include <lib/kprintf.h>
#include <irq.h>
#include <vga.h>

/* A look-up table for all of our keypress values */
unsigned char keyboard_map[128] = {
	KB_ERROR, KB_ESCAPE,
	'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
	'\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
	KB_CTRL,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '#',
	KB_LEFT_SHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', KB_RIGHT_SHIFT,
	'*', KB_ALT, ' ', KB_CAPS_LOCK,
	KB_F1, KB_F2, KB_F3, KB_F4, KB_F5, KB_F6, KB_F7, KB_F8, KB_F9, KB_F10,
	KB_NUM_LOCK, KB_SCROLL_LOCK, KB_HOME, KB_UP, KB_PAGE_UP, '-',
	KB_LEFT, KB_5, KB_RIGHT, '+', KB_END, KB_DOWN, KB_PAGE_DOWN, KB_INS,
	KB_DEL, KB_ALT_GR, 0, KB_BLANK, KB_F11, KB_F12,
};

struct keyboard_status kb_status;

void keyboard_handler(stack_rep_t *rep){
	uint8_t key;
	key = read_byte(0x60);
	if(key&0x80){ /* Key released */
		key ^= 0x80;
		key = keyboard_map[key];
		switch(key){
			case KB_LEFT_SHIFT:
				kb_status.status ^= 0x08;
				break;
			case KB_RIGHT_SHIFT:
				kb_status.status ^= 0x10;
				break;
			case KB_ALT:
				kb_status.status ^= 0x40;
				break;
			case KB_ALT_GR:
				kb_status.status ^= 0x80;
				break;
			case KB_CTRL:
				kb_status.status ^= 0x20;
				break;
		}
	} else {
		key = keyboard_map[key];
		switch(key){
			case KB_LEFT_SHIFT:
				kb_status.status |= 0x08;
				break;
			case KB_RIGHT_SHIFT:
				kb_status.status |= 0x10;
				break;
			case KB_ALT:
				kb_status.status |= 0x40;
				break;
			case KB_ALT_GR:
				kb_status.status |= 0x80;
				break;
			case KB_CTRL:
				kb_status.status |= 0x20;
				break;
			case KB_NUM_LOCK:
				kb_status.status ^= 0x02;
				break;
			case KB_SCROLL_LOCK:
				kb_status.status ^= 0x04;
				break;
			case KB_CAPS_LOCK:
				kb_status.status ^= 0x01;
				break;
			default:{
				vga_write_char(key);
			}
		}
	}
}

void keyboard_install(){
	/* Install the keyboard to IRQ #1 */
        irq_create_handler(1, keyboard_handler);
}

