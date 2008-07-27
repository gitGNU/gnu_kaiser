#include <kmalloc.h>
#include <asm/stddef.h>
#include <lib/kprintf.h>
#include <kheap.h>
#include <page.h>
#include <lib/kprintf.h>

extern uint32_t end; /* defined in the linker script */
extern heap_t *kheap;
uint32_t start_address = &end;

void *kmalloc_internal(uint32_t size, int align, uint32_t *physical){
	if(kheap != 0){
		void *address = alloc(size, (uint8_t)align, kheap);
		if(physical){
			page_t *page = get_page((uint32_t)address, 0, kernel_directory);
			*physical = page->frame*0x1000 + ((uint32_t)address&0xFFF);
		}
		return (void *)address;
	} else {
	        if(align && (start_address & 0xFFFFF000)){
	                start_address &= 0xFFFFF000;
	                start_address += 0x1000;
	        }
	        if(physical){
	                *physical = start_address;
	        }
	        uint32_t tmp = start_address;
	        start_address += size;
	        return (void *)tmp;
	}
}

void *kmalloc(uint32_t size){
	return kmalloc_internal(size, 0, NULL);
}

void *kmalloc_a(uint32_t size){
	return kmalloc_internal(size, 1, NULL);
}

void *kmalloc_p(uint32_t size, uint32_t *physical){
	return kmalloc_internal(size, 0, physical);
}

void *kmalloc_ap(uint32_t size, uint32_t *physical){
	return kmalloc_internal(size, 1, physical);
}

void kfree(void *p){
	free(p, kheap);
}
