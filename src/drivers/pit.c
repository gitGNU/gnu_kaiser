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
#include <procio.h>

uint32_t pit_ticks = 0;

void timer_handler(stack_rep_t *r){
	pit_ticks++;
}

void timer_swait(uint32_t seconds){
	uint32_t dticks;
	dticks = pit_ticks + (seconds*PIT_INTERRUPT_FREQUENCY);
	while(pit_ticks < dticks);
}

void timer_install(){
	uint32_t time = PIT_CORE_FREQUENCY / PIT_INTERRUPT_FREQUENCY;
	/* Inaccuracy in division! Any way to sort this out? */
	send_byte(PIT_COMMAND_REGISTER, 0x36); /*generates a square wave without sending BCD data*/
	send_byte(PIT_CHANNEL1, time & 0xFF);
	send_byte(PIT_CHANNEL1, (time >> 8));
	irq_create_handler(0, timer_handler);
}

void play_sound(uint32_t frequency){
	uint32_t freq;
	freq = PIT_CORE_FREQUENCY / frequency;
	/* Set our frequency */
	send_byte(0x43, 0xb6);
	send_byte(PIT_CHANNEL3, (uint8_t)freq);
	send_byte(PIT_CHANNEL3, (uint8_t)(freq >> 8));

	uint8_t tmp;
	tmp = read_byte(0x61);
	if(tmp != (tmp|3)){
		send_byte(0x61, tmp|3);
	}
}

void stop_sound(){
	uint8_t tmp = read_byte(0x61) & 0xFC;
	send_byte(0x61, tmp);
}

void beep(){
	play_sound(1000);
	timer_swait(10);
	stop_sound();
}
