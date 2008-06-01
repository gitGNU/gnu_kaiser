#include <asm/stddef.h>
#include <procio.h>

uint8_t read_byte(uint16_t port){
	uint8_t rv;
	__asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (port));
	return rv;
}

void send_byte(uint16_t port, uint8_t data){
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
