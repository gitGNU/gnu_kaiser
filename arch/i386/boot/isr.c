/*
 * isr.c - ISRs initialisation / handler code
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
#include <idt.h>
#include <lib/kprintf.h>

char *exception_text[] = { /* Exception messages table */
/*0*/   "Division Error",
/*1*/   "Debug",
/*2*/   "NMI",
/*3*/   "Breakpoint",
/*4*/   "Overflow",
/*5*/   "BOUND Range Exceeded",
/*6*/   "Invalid Opcode",
/*7*/   "Device Not Available",
/*8*/   "Double Fault",
/*9*/   "Coprocessor Segment Overrun",
/*10*/  "Invalid TSS Exception",
/*11*/  "Segment Not Present",
/*12*/  "Stack Fault",
/*13*/  "General Protection",
/*14*/  "Page Fault",
/*15*/  "Unknown Interrupt",
/*16*/  "x87 FPU Error",
/*17*/  "Alignment Check",
/*18*/  "Machine-Check",
/*19*/  "SIMD Floating-Point",
/*20*/  "Reserved",
/*21*/  "Reserved",
/*22*/  "Reserved",
/*23*/  "Reserved",
/*24*/  "Reserved",
/*25*/  "Reserved",
/*26*/  "Reserved",
/*27*/  "Reserved",
/*28*/  "Reserved",
/*29*/  "Reserved",
/*30*/  "Reserved",
/*31*/  "Reserved",
};

void isr_install(){
	/* Install all of our ISRs onto their IDT numbers */
	idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
}

void fault_handler(stack_rep_t *r){
	if(r->int_no < 32){ /* Not kernel defined? */
		kprintf("Exception, Number: %d, Message: %s\n", (unsigned)r->int_no, exception_text[r->int_no]);
		kprintf("Contents of registers:\n");
		kprintf("ds: %d, es: %d, fs: %d, es: %d\n", r->ds, r->es, r->fs, r->gs);
		kprintf("eax: %d, ebx: %d, ecx: %d, edx: %d\n", r->eax, r->ebx, r->ecx, r->edx);
		kprintf("esp: %d, ebp: %d, esi: %d, edi: %d\n", r->esp, r->ebp, r->esi, r->edi);
		kprintf("err: %d, eip: %d, cs: %d\n", r->err_no, r->eip, r->cs);
		kprintf("eflags: %d, useresp: %d, ss: %d\n", r->eflags, r->useresp, r->ss);
	}
	__asm__("hlt"); /*just hlt the CPU for now*/
}
