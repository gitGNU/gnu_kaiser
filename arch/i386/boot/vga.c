/*
 * vga.c - VGA driver
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
#include <vga.h>
#include <asm/stddef.h> /* XXX: stddef.h may not reside in asm in the future */

static uint16_t xpos;			/* Current X position */
static uint16_t ypos;			/* Current Y position */
static uint16_t columns;		/* Number of columns */
static uint16_t lines;			/* Number of lines */
static volatile unsigned char *video;	/* Video memory address */

/* Initialise the VGA system */
void vga_init(void)
{
	/* TODO: We need to probe the hardware to find appropriate values for
	 * all this stuff. For now, we just enter some values that should work
	 * for the majority of systems. */
	xpos = ypos = 0;
	columns = 80;
	lines = 24;
	video = (unsigned char *) 0xB8000;
}

/* Clear the screen contents are reset x and y positions. */
void vga_clear_screen(void)
{
	int i;

	for (i = 0; i < (columns * lines); i++)
		*(video + i) = 0;
	xpos = ypos = 0;
}


