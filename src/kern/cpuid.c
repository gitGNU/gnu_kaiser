#include <asm/stddef.h>
#include <lib/string.h>
#include "cpuid.h"

inline void cpuid(int code, int *eax, int *ebx, int *ecx, int *edx) {
	__asm__ __volatile__("cpuid"
											 :"=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
											 :"a" (code));
}

char *cpuid_get_vendor_string(char *out) {
	int eax, ebx, ecx, edx;
	cpuid(0, &eax, &ebx, &ecx, &edx);
	memcpy(out, &ebx, 4);
	memcpy(out + 4, &edx, 4);
	memcpy(out + 8, &ecx, 4);
	out[12] = '\0';
	return out;
}

/*
void cpuid_get_info(cpuinfo_t *info) {
}
*/
