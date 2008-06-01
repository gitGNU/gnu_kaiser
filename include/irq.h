#ifndef __IRQ_H__
#define __IRQ_H__

#include <asm/stddef.h>
#include <isr.h>

extern void irq0();  /* looking familiar? */
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_clear_handler(uint32_t);
void irq_remap();
void irq_install();
void irq_create_handler(uint32_t, void (*handler)(stack_rep_t *));
void irq_handler(stack_rep_t *);

#endif
