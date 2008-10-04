typedef struct {
} cpuinfo_t;

/*
 * Single char * argument should be a char array with 13 elements (including
 * a terminating '\0' char).
 *
 * Returns the given argument, which is set to a '\0' terminated 12 char CPUID
 * vendor string.
 */
char *cpuid_get_vendor_string(char *);

