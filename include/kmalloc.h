#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include <asm/stddef.h>

extern uint32_t start_address;

uint32_t kmalloc_internal(uint32_t size, int align, uint32_t *physical);

uint32_t kmalloc(uint32_t size); /* returns a pointer to the address */
uint32_t kmalloc_a(uint32_t size); /* returns page aligned pointer */
uint32_t kmalloc_p(uint32_t size, uint32_t *physical); /*returns both*/
uint32_t kmalloc_ap(uint32_t size, uint32_t *physical);

#endif
