/*
 * vga.h - VGA driver
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

#ifndef __VGA_H__
#define __VGA_H__

#include <asm/stddef.h>

#define	VGA_FG_BLACK 0
#define	VGA_FG_BLUE 1
#define	VGA_FG_GREEN 2
#define	VGA_FG_CYAN 3
#define	VGA_FG_RED 4
#define	VGA_FG_MAGENTA 5
#define	VGA_FG_BROWN 6
#define	VGA_FG_LIGHT_GREY 7
#define	VGA_FG_DARK_GREY 8
#define	VGA_FG_LIGHT_BLUE 9
#define	VGA_FG_LIGHT_GREEN 10
#define	VGA_FG_LIGHT_CYAN 11
#define	VGA_FG_LIGHT_RED 12
#define	VGA_FG_LIGHT_MAGENTA 13
#define	VGA_FG_LIGHT_BROWN 14
#define	VGA_FG_WHITE 15

/*
 * They made me do this, I wanted to use a macro, but ooooooh nooooo, gotta be
 * an idiot. - Oliver
 */
#define	VGA_BG_BLACK					(VGA_FG_BLACK << 4)
#define	VGA_BG_BLUE						(VGA_FG_BLUE << 4)
#define	VGA_BG_GREEN					(VGA_FG_GREEN << 4)
#define	VGA_BG_CYAN						(VGA_FG_CYAN << 4)
#define	VGA_BG_RED						(VGA_FG_RED << 4)
#define	VGA_BG_MAGENTA				(VGA_FG_MAGENTA << 4)
#define	VGA_BG_BROWN					(VGA_FG_BROWN << 4)
#define	VGA_BG_LIGHT_GREY			(VGA_FG_LIGHT_GREY << 4)
#define	VGA_BG_DARK_GREY			(VGA_FG_DARK_GREY << 4)
#define	VGA_BG_LIGHT_BLUE			(VGA_FG_LIGHT_BLUE << 4)
#define	VGA_BG_LIGHT_GREEN		(VGA_FG_LIGHT_GREEN << 4)
#define	VGA_BG_LIGHT_CYAN			(VGA_FG_LIGHT_CYAN << 4)
#define	VGA_BG_LIGHT_RED			(VGA_FG_LIGHT_RED << 4)
#define	VGA_BG_LIGHT_MAGENTA	(VGA_FG_LIGHT_MAGENTA << 4)
#define	VGA_BG_LIGHT_BROWN		(VGA_FG_LIGHT_BROWN << 4)
#define	VGA_BG_WHITE					(VGA_FG_WHITE << 4)

void vga_init(void);
void vga_clear_screen(void);
void vga_write_char(int);
int vga_set_pos(uint16_t, uint16_t);
int vga_set_char(int, uint16_t, uint16_t);
void vga_set_foreground_colour(uint8_t);
void vga_set_background_colour(uint8_t);
uint8_t vga_get_foreground_colour(void);
uint8_t vga_get_background_colour(void);
void vga_scroll(void);

#endif /* __VGA_H__ */
