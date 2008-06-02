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

unsigned char keyboard_map[128] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
        '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '#', /* first char ctrl */
        0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', /* first char left shift */
        0 /*right shift*/, '*',
        0/*alt*/, ' ', 0 /*caps*/, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0 /*f1->f10*/,
        0/*num lock*/, 0/*scroll lock*/, 0/*home*/, 0/*up*/, 0/*pg up*/, '-', 0/*left*/,
        0, 0/*right*/, '+', 0/*end*/, 0/*down*/, 0/*pg down*/, 0/*ins*/, 0/*del*/, 0, 0, 0,
        0, 0/*f11,f12*/, 0,/*all else undef'd*/
};

void keyboard_handler(stack_rep_t *rep){
	uint8_t key;
	key = read_byte(0x60);
	if(key&0x80){
	} else {
		kprintf("%d pressed\n", keyboard_map[key]);
	}
}

void keyboard_install(){
        irq_create_handler(1, keyboard_handler);
}

