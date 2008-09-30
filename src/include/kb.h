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
#define __KB_H__

#include <isr.h>
#include <asm/stddef.h>
/* These numbers are purely made up, are they good enough? */
#define KB_ERROR 128
#define KB_ESCAPE 27
#define KB_CTRL 129
#define KB_LEFT_SHIFT 130
#define KB_RIGHT_SHIFT 131
#define KB_ALT 132
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
#define KB_ALT_GR 157
#define KB_BLANK 158
#define KB_F11 159
#define KB_F12 160

#define complement_scroll(x) (x->status ^= 0x01)
#define complement_num(x)    (x->status ^= 0x02)
#define complement_caps(x)   (x->status ^= 0x04)

#define set_lshift(x) (x->status |= 0x08)
#define set_rshift(x) (x->status |= 0x10)
#define set_ctrl(x)   (x->status |= 0x20)
#define set_alt(x)    (x->status |= 0x40)
#define set_altgr(x)  (x->status |= 0x80)
#define set_super(x)  (x->status |= 0x100)

#define unset_lshift(x) (x->status &= ~(0x08))
#define unset_rshift(x) (x->status &= ~(0x10))
#define unset_ctrl(x)   (x->status &= ~(0x20))
#define unset_alt(x)    (x->status &= ~(0x40))
#define unset_altgr(x)  (x->status &= ~(0x80))
#define unset_super(x)  (x->status &= ~(0x100))

typedef struct keyboard_status {
	/*
	 * Any keys which have memory need to be kept track of
	 *
	 * 0,1,2 = {scroll,num,caps}lock
	 * 3,4   = left/right shift
	 * 5     = ctrl
	 * 6,7   = alt/altgr
	 * 8     = super
	 *
	 */
	int status;
} keyboard_status_t;

void keyboard_handler(stack_rep_t *);
void keyboard_install();

#endif
