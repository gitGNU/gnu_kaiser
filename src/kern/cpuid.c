/*
 * cpuid.c - Internal CPUID API
 *
 * Copyright (C) 2008 Oliver Heard <ogheard@googlemail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

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

cpuinfo_t *cpuid_get_info(cpuinfo_t *info) {
	int eax, ebx, ecx, edx;
	cpuid(1, &eax, &ebx, &ecx, &edx);
	info->stepping = (0x0000000F & eax);
	info->model = (0x000000F0 & eax) >> 4;
	info->family = (0x00000F00 & eax) >> 8;
	info->type = (0x0000F000 & eax) >> 12;
	info->ext_model = (0x000F0000 & eax) >> 16;
	info->ext_family = (0x00F00000 & eax) >> 20;
	return info;
}

