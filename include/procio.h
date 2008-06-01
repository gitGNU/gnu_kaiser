#ifndef __PROCIO_H__
#define __PROCIO_H__
#include <asm/stddef.h>

#define MASTER_PIC 0x20
#define SLAVE_PIC  0xA0
#define EOI_PIC    0x20

uint8_t read_byte(uint16_t);
void send_byte(uint16_t, uint8_t);

#endif
