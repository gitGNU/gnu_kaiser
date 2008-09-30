/*
 * asm.S - GDT/IDT loading functions and ISR/IRQ code
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

.global gdt_flush, idt_load
.extern gdt_pointer, idt_pointer
gdt_flush:
	push %ebp
	mov %esp, %ebp

	lgdt (gdt_pointer)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	jmp %cs:flush /* far jmp */
flush:
	mov %ebp, %esp
	pop %ebp
	ret

idt_load:
	push %ebp
	mov %esp, %ebp
	lidt (idt_pointer)
	mov %ebp, %esp
	pop %ebp
	ret

.global isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,  isr8,  isr9     /* better way? */
.global isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19
.global isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29
.global isr30, isr31

/*
 * We're just registering all the ISRs with their unique
 * vector ID
 */

#define ISR_QUIRK(x) \
	isr##x: \
		cli; \
		push $0; \
		push $##x; \
		jmp isr_common

#define ISR(x) \
	isr##x: \
		cli; \
		push $##x; \
		jmp isr_common

ISR_QUIRK(0);
ISR_QUIRK(1);
ISR_QUIRK(2);
ISR_QUIRK(3);
ISR_QUIRK(4);
ISR_QUIRK(5);
ISR_QUIRK(6);
ISR_QUIRK(7);
ISR(8);
ISR(9);
ISR(10);
ISR(11);
ISR(12);
ISR(13);
ISR(14);
ISR_QUIRK(15);
ISR_QUIRK(16);
ISR_QUIRK(17);
ISR_QUIRK(18);
ISR_QUIRK(19);
ISR_QUIRK(20);
ISR_QUIRK(21);
ISR_QUIRK(22);
ISR_QUIRK(23);
ISR_QUIRK(24);
ISR_QUIRK(25);
ISR_QUIRK(26);
ISR_QUIRK(27);
ISR_QUIRK(28);
ISR_QUIRK(29);
ISR_QUIRK(30);
ISR_QUIRK(31);

.extern fault_handler /* In our isr.c file */
isr_common:
	pusha
	push %ds /* store all of these for later then overwrite them */
	push %es
	push %fs
	push %gs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp, %eax
	push %eax
	call fault_handler
	pop %eax /* time to reverse what we just did! */
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	add $8, %esp
	iret

/* IRQ time */
.global irq0,  irq1,  irq2,  irq3,  irq4,  irq5, irq6, irq7, irq8, irq9
.global irq10, irq11, irq12, irq13, irq14, irq15

#define IRQ(x,y) \
irq##x: \
	cli;\
	push $0;\
	push $##y;\
	jmp irq_common

IRQ(0, 32);
IRQ(1, 33);
IRQ(2, 34);
IRQ(3, 35);
IRQ(4, 36);
IRQ(5, 37);
IRQ(6, 38);
IRQ(7, 39);
IRQ(8, 40);
IRQ(9, 41);
IRQ(10, 42);
IRQ(11, 43);
IRQ(12, 44);
IRQ(13, 45);
IRQ(14, 46);
IRQ(15, 47);

.extern irq_handler
irq_common: /* same as the ISR version but calling a different routine... */
	pusha
	push %ds
	push %es
	push %fs
	push %gs
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %esp, %eax
	push %eax
	call irq_handler
	pop %eax
	pop %gs
	pop %fs
	pop %es
	pop %ds
	popa
	add $8, %esp
	iret
