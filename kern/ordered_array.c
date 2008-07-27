#include <ordered_array.h>
#include <asm/stddef.h>
#include <lib/string.h>
#include <kmalloc.h>

char standard_lessthan_predicate(void *a, void *b){
	return (a<b)?1:0;
}

ordered_array_t create_ordered_array(uint32_t max_size, lessthan_predicate_t less_than){
	ordered_array_t retval;
	retval.array = (void *)kmalloc(max_size*sizeof(void *));
	memset(retval.array, 0, max_size*sizeof(void *));
	retval.size = 0;
	retval.max_size = max_size;
	retval.less_than = less_than;
	return retval;
}

ordered_array_t place_ordered_array(void *address, uint32_t max_size, lessthan_predicate_t less_than){
	ordered_array_t retval;
	retval.array = (void **)address;
	memset(retval.array, 0, max_size*sizeof(void *));
	retval.size = 0;
	retval.max_size = max_size;
	retval.less_than = less_than;
	return retval;
}

void destroy_ordered_array(ordered_array_t *array){
	//kfree(array->array);
}

void insert_ordered_array(void *item, ordered_array_t *array){
	uint32_t i = 0;
	while(i < array->size && array->less_than(array->array[i], item))
		i++;
	if(i==array->size)
		array->array[array->size++] = item;
	else {
		void *tmp = array->array[i];
		array->array[i] = item;
		while(i<array->size){
			i++;
			void *tmp2 = array->array[i];
			array->array[i] = tmp;
			tmp = tmp2;
		}
		array->size++;
	}
}

void *lookup_ordered_array(uint32_t i, ordered_array_t *array){
	return array->array[i];
}

void remove_ordered_array(uint32_t i, ordered_array_t *array){
	while(i<array->size){
		array->array[i] = array->array[i+1];
		i++;
	}
	array->size--;
}
