#include <kmalloc.h>
#include <asm/stddef.h>
#include <lib/kprintf.h>

extern uint32_t end; /* defined in the linker script */
uint32_t start_address = &end;

uint32_t kmalloc_internal(uint32_t size, int align, uint32_t *physical){
        if(align && (start_address & 0xFFFFF000)){
                start_address &= 0xFFFFF000;
                start_address += 0x1000;
        }
        if(physical){
                *physical = start_address;
        }
        uint32_t tmp = start_address;
        start_address += size;
        return tmp;
}

uint32_t kmalloc(uint32_t size){
	return kmalloc_internal(size, 0, NULL);
}

uint32_t kmalloc_a(uint32_t size){
	return kmalloc_internal(size, 1, NULL);
}

uint32_t kmalloc_p(uint32_t size, uint32_t *physical){
	return kmalloc_internal(size, 0, physical);
}

uint32_t kmalloc_ap(uint32_t size, uint32_t *physical){
	return kmalloc_internal(size, 1, physical);
}
