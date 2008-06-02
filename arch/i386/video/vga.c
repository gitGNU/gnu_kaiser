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

#define TAB_SIZE 8 /* XXX: This could possibly be made dynamic */

static uint16_t xpos;			/* Current X position */
static uint16_t ypos;			/* Current Y position */
static uint16_t columns;		/* Number of columns */
static uint16_t lines;			/* Number of lines */
static volatile unsigned char *video;	/* Video memory address */
static unsigned char attribute;		/* Attribute byte used to write the
					 * next character. */

/* Initialise the VGA system */
void vga_init(void) {
	/* TODO: We need to probe the hardware to find appropriate values for
	 * all this stuff. For now, we just enter some values that should work
	 * for the majority of systems. */
	xpos = ypos = 0;
	columns = 80;
	lines = 25;
	video = (unsigned char *) 0xB8000;
	attribute = 0;
}

/* Clear the screen contents are reset x and y positions. */
void vga_clear_screen(void) {
	int i;

	for (i = 0; i < (columns * lines) * 2; i++)
		*(video + i) = 0;
	xpos = ypos = 0;
}

void vga_write_char(int c) {
	int i;

	if (c == '\r') {
		xpos = 0;
		return;
	}
	if (xpos >= columns || c == '\n') {
		xpos = 0;
		ypos++;
		if (ypos >= lines)
			ypos = 0;
		if (c == '\n')
			return;
	}
	if (c == '\t')
		while (xpos % TAB_SIZE) {
			if (columns - xpos < TAB_SIZE) {
				xpos = 0;
				ypos++;
				break;
			}
			vga_write_char(' ');
		}
	else {
		*(video + (xpos + ypos * columns) * 2) = c & 0xFF;
		*(video + (xpos + ypos * columns) * 2 + 1) = attribute;
		xpos++;
	}
}

/* Set the position to write to next on screen.
 * Returns 1 if successful, 0 if x or y (or both), are out of range. */
int vga_set_pos(uint16_t x, uint16_t y) {
	if (x > columns || y > lines)
		return 0;
	xpos = x;
	ypos = y;
	return 1;
}

/* Write a char to a specific location on screen.
 * Returns 1 if successful, 0 if x or y (or both), are out of range. */
int vga_set_char(int c, uint16_t x, uint16_t y) {
	if (x > columns || y > lines)
		return 0;
	*(video + (x + y * columns) * 2) = c & 0xFF;
	*(video + (x + y * columns) * 2 + 1) = attribute;
	return 1;
}

void vga_set_foreground_colour(uint8_t colour) {
	colour &= 0x0F;		/* clear the first 4 bits of colour */
	attribute &= 0xF0;	/* clear the last 4 bits of attribute */
	attribute |= colour;	/* assign the last 4 bits of colour to the last */
}

void vga_set_background_colour(uint8_t colour) {
	colour <<= 4;		/* move the value to where we need it */
	colour &= 0xF0;		/* clear the last 4 bits of colour */
	attribute &= 0x0F;	/* clear the first 4 bits of attribute */
	attribute |= colour;	/* assign the first 4 bits of colour to the
				 * first 4 bits of attribute */
}

