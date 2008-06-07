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
	lgdt (gdt_pointer)
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	/* We need a far jump here! */
	ret

idt_load:
	lidt (idt_pointer)
	ret

.global isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,  isr8,  isr9     /* better way? */
.global isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19
.global isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29
.global isr30, isr31

/*
 * This is so much code duplication is makes me want to cry
 * we're just registering all the ISRs with their unique
 * vector ID
 */

isr0:
	cli
	push $0
	push $0
	jmp isr_common
isr1:
	cli
	push $0
	push $1
	jmp isr_common
isr2:
        cli
        push $0
        push $2
        jmp isr_common
isr3:
        cli
        push $0
        push $3
        jmp isr_common
isr4:
        cli
        push $0
        push $4
        jmp isr_common
isr5:
        cli
        push $0
        push $5
        jmp isr_common
isr6:
        cli
        push $0
        push $6
        jmp isr_common
isr7:
        cli
        push $0
        push $7
        jmp isr_common
isr8:
	cli
	push $8
	jmp isr_common
isr9:
        cli
        push $0
        push $9
        jmp isr_common
isr10:
	cli
	push $10
	jmp isr_common
isr11:
	cli
	push $11
	jmp isr_common
isr12:
	cli
	push $12
	jmp isr_common
isr13:
	cli
	push $13
	jmp isr_common
isr14:
	cli
	push $14
	jmp isr_common
isr15:
	cli
	push $0
	push $15
	jmp isr_common
isr16:
	cli
	push $0
	push $16
	jmp isr_common
isr17:
        cli
        push $0
        push $17
        jmp isr_common
isr18:
        cli
        push $0
        push $18
        jmp isr_common
isr19:
        cli
        push $0
        push $19
        jmp isr_common
isr20:
        cli
        push $0
        push $20
        jmp isr_common
isr21:
        cli
        push $0
        push $21
        jmp isr_common
isr22:
        cli
        push $0
        push $22
        jmp isr_common
isr23:
        cli
        push $0
        push $23
        jmp isr_common
isr24:
        cli
        push $0
        push $24
        jmp isr_common
isr25:
        cli
        push $0
        push $25
        jmp isr_common
isr26:
        cli
        push $0
        push $25
        jmp isr_common
isr27:
        cli
        push $0
        push $27
        jmp isr_common
isr28:
        cli
        push $0
        push $28
        jmp isr_common
isr29:
        cli
        push $0
        push $29
        jmp isr_common
isr30:
        cli
        push $0
        push $30
        jmp isr_common
isr31:
        cli
        push $0
        push $31
        jmp isr_common

/* Phew, that's over with! */
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

irq0:
        cli
        push $0
        push $32
        jmp irq_common
irq1:
        cli
        push $0
        push $33
        jmp irq_common
irq2:
        cli
        push $0
        push $33
        jmp irq_common
irq3:
        cli
        push $0
        push $34
        jmp irq_common
irq4:
        cli
        push $0
        push $35
        jmp irq_common
irq5:
        cli
        push $0
        push $36
        jmp irq_common
irq6:
	cli
	push $0
	push $37
	jmp irq_common
irq7:
        cli
        push $0
        push $38
        jmp irq_common
irq8:
        cli
        push $0
        push $39
        jmp irq_common
irq9:
        cli
        push $0
        push $40
        jmp irq_common
irq10:
        cli
        push $0
        push $41
        jmp irq_common
irq11:
        cli
        push $0
        push $42
        jmp irq_common
irq12:
        cli
        push $0
        push $43
        jmp irq_common
irq13:
        cli
        push $0
        push $44
        jmp irq_common
irq14:
        cli
        push $0
        push $45
        jmp irq_common
irq15:
        cli
        push $0
        push $46
        jmp irq_common

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
