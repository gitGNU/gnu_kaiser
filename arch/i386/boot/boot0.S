/*
 * arch/i368/boot/boot0.S - realmode bootsector
 *                          chainloader (loads the 2nd sector of fd0)
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
	.code16
	jmp	$0x7c0, $reloc
reloc:
	xor	%ax, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	$0x7c00, %si
	mov	$0x0600, %di
	mov	$512, %cx
	cld
	rep	movsw
	jmp	$0x0060, $chainload
reboot:
	mov	$errormsg, %si
	push	%cs
	pop	%ds
1:	lodsb
	cmp	$0, %al
	je	2f
	mov	$0x0e, %ah
	int	$0x10
	jmp	1b
2:	xor	%ax, %ax
	int	$0x16
	mov	$0x40, %ax
	mov	%ax, %ds
	movw	$0x1234, 0x72
	jmp	$0xffff, $0x0000
chainload:
	mov	$0x202, %ax
	mov	$2, %cx
	xor	%dx, %dx
	mov	%dx, %es
	mov	$0x7c00, %bx
	int	$0x13
	jc	reboot
	jmp	$0, $0x7c00
errormsg:
	.string "Error reading from fd0.\r\nPress any key..."
	.org	510
	.word	0xaa55
