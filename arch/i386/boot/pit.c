/*
 * pit.c - PIT driver
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

#include <isr.h>
#include <asm/stddef.h>
#include <irq.h>
#include <pit.h>
#include <lib/kprintf.h>

int pit_ticks = 0;

void timer_handler(stack_rep_t *r){
	pit_ticks++;
	if(!(pit_ticks%100)){
		kprintf("\r%d seconds passed", pit_ticks/100);
	}
}

void timer_install(){
	uint32_t time = PIT_FREQUENCY / WANTED_FREQUENCY;  /* Inaccuracy in division! */
	send_byte(PIT_COMMAND_REGISTER, 0x36); /*generates a square wave without sending BCD data*/
	send_byte(PIT_CHANNEL1, time & 0xFF);
	send_byte(PIT_CHANNEL1, (time >> 8));
	irq_create_handler(0, timer_handler);
}

