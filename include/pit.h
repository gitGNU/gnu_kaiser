/*
 * pit.h - PIT driver header
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

#ifndef __PIT_H__
#define __PIT_H__
#include <isr.h>
#include <asm/stddef.h>

#define WANTED_FREQUENCY 100  /* 100Hz */
#define PIT_FREQUENCY 1193182 /* rounded up from 1193181.666 Hz can we be nicer here? */
#define PIT_COMMAND_REGISTER 0x43
#define PIT_CHANNEL1 0x40
#define PIT_CHANNEL2 0x41
#define PIT_CHANNEL3 0x42

void timer_install();
void timer_handler(stack_rep_t *);

#endif
