/*
 * cpuid.h - Internal CPUID API header
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

#ifndef __CPUID_H__
#define __CPUID_H__

typedef struct {
	uint8_t stepping;
	uint8_t model;
	uint8_t family;
	uint8_t type;
	uint8_t ext_model;
	uint8_t ext_family;
} cpuinfo_t;

/*
 * Single char * argument should be a char array with 13 elements (including
 * a terminating '\0' char).
 *
 * Returns the given argument, which is set to a '\0' terminated 12 char CPUID
 * vendor string.
 */
char *cpuid_get_vendor_string(char *);

/*
 * Retrieve CPU information and store in the given cpuinfo_t structure.
 */
cpuinfo_t *cpuid_get_info(cpuinfo_t *);

#endif /* !__CPUID_H__ */

