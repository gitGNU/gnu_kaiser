#ifndef __ORDERED_ARRAY_H__
#define __ORDERED_ARRAY_H__

#include <asm/stddef.h>

typedef char (*lessthan_predicate_t)(void *, void *);
typedef struct {
	void **array;
	uint32_t size;
	uint32_t max_size;
	lessthan_predicate_t less_than;
} ordered_array_t;

char standard_lessthan_predicate(void *, void *);

ordered_array_t create_ordered_array(uint32_t, lessthan_predicate_t);
ordered_array_t place_ordered_array(void *, uint32_t, lessthan_predicate_t);
void destroy_ordered_array(ordered_array_t *);
void insert_ordered_array(void *, ordered_array_t *);
void *lookup_ordered_array(uint32_t, ordered_array_t *);
void remove_ordered_array(uint32_t, ordered_array_t *);

#endif
