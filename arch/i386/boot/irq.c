/*
 * irq.c - IRQ code
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

#include <asm/stddef.h>
#include <irq.h>
#include <idt.h>
#include <isr.h>
#include <procio.h>

/* function pointers, 0=no pointer */
void *irq_handlers[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

/* add a function pointer to that particular irq number, so when
 * it's fired that function is called
 */
void irq_create_handler(uint32_t irq, void (*handler)(stack_rep_t *r)){
	irq_handlers[irq] = handler;
}

/* 0 is a null-handler */
void irq_clear_handler(uint32_t irq){
	irq_handlers[irq] = 0;
}

/* IRQs are by default mapped onto processor reserved
 * ISR numbers, thus we need to change them into something
 * we're allowed to actually use
 */
void irq_remap(){
	send_byte(MASTER_PIC, 0x11); /* master */
	send_byte(SLAVE_PIC, 0x11); /* slave */
	send_byte(0x21, EOI_PIC);
	send_byte(0xA1, 0x28);
	send_byte(0x21, 0x04);
	send_byte(0xA1, 0x02);
	send_byte(0x21, 0x01);
	send_byte(0xA1, 0x01);
	send_byte(0x21, 0x00);
	send_byte(0xA1, 0x00);
}

void irq_install(){
	irq_remap();
	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E); /* same as for isr */
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

void irq_handler(stack_rep_t *rep){
	void (* handler)(stack_rep_t *rep); /*function pointer (blank)*/
	handler = irq_handlers[rep->int_no - 32];
	/*both master and slave PICs are here*/
	if(handler){
		handler(rep);
	}
	/*if it was from the slave we have to do extra work*/
	if(rep->int_no > 39){
		send_byte(SLAVE_PIC, EOI_PIC);/*send EOI to slave*/
	}
	send_byte(MASTER_PIC, EOI_PIC); /*send EOI to master*/
}
