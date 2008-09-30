#ifndef __PANIC_H__
#define __PANIC_H__

#include <lib/unwind.h>
#include <lib/kprintf.h>

#define PANIC(message) \
	kprintf("\n\nPANIC ocurred: at %s:%u, message: %s\n\n", __FILE__, __LINE__,message);\
	unwind();\
	kprintf("\n");\
	__asm__("int3")

#endif
