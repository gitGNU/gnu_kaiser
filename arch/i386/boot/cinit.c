#include <multiboot.h>

#define CHECK_FLAG(flags,bit) ((flags) & (1<<(bit)))

void cinit(unsigned long magic, unsigned long addr);

void cinit(unsigned long magic, unsigned long addr){
	multiboot_info_t *mbi;
	mbi = (multiboot_info_t *)addr;
	/*
	 * do out initialisation here maybe?
	 */
}
