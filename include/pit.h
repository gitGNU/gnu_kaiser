#ifndef __PIT_H__
#define __PIT_H__
#include <isr.h>
#include <asm/stddef.h>

#define WANTED_FREQUENCY 100  /* 100Hz */
#define PIT_FREQUENCY 1193180 /* I didn't invent them... */
#define PIT_COMMAND_REGISTER 0x43
#define PIT_CHANNEL1 0x40
#define PIT_CHANNEL2 0x41
#define PIT_CHANNEL3 0x42

void timer_install();
void timer_handler(stack_rep_t *);

#endif
