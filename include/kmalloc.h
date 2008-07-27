#ifndef __KMALLOC_H__
#define __KMALLOC_H__

#include <asm/stddef.h>

extern uint32_t start_address;

void *kmalloc_internal(uint32_t size, int align, uint32_t *physical);

void *kmalloc(uint32_t size); /* returns a pointer to the address */
void *kmalloc_a(uint32_t size); /* returns page aligned pointer */
void *kmalloc_p(uint32_t size, uint32_t *physical); /*returns both*/
void *kmalloc_ap(uint32_t size, uint32_t *physical);

#endif
