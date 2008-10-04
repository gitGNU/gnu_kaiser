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
void cpuid_get_info(cpuinfo_t *info);

#endif /* !__CPUID_H__ */

