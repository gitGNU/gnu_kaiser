#include <multiboot.h>
#include <vga.h>

#define CHECK_FLAG(flags,bit) ((flags) & (1<<(bit)))

void init(unsigned long magic, unsigned long addr) {
	multiboot_info_t *mbi;
	mbi = (multiboot_info_t *)addr;

	/* Initialise the VGA system and clear the screen */
	vga_init();
	vga_clear_screen();
}

