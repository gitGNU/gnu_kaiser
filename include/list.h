/* 
 * More or less a ripoff of the linux linked list implementation:
 * 
 * Washing instructions:
 *
 * 1. Ensure you call list_init(list_header) before adding data 
 * 2. You embed list_t into the top of whatever structure you're linking
 * 3. You should keep a seperate list_t to act as the list header
 * 4. Do not tumble dry
 *
 */

struct list_head
{
	struct list_head *next, *prev;
};

typedef struct list_head list_t;

static inline void list_init(list_t *head)
{
	head->next = head;
	head->prev = head;
}

/* add element to the end of a list */
static inline void list_append(list_t *head, list_t *elem)
{
	list_t *prev = head->prev;
	
	/* prev -> elem -> head */
	prev->next = elem; elem->next = head;
	
	/* prev <- elem <- head */
	elem->prev = prev; head->prev = elem; 
}

/* 
 * Removes elem from whatever list it's currently in.
 *
 * BONUS: Doesn't break when the list is empty, which is nice.
 */

static inline void list_remove(list_t *elem)
{
	list_t *next = elem->next, *prev = elem->prev;

	/* prev <-> prev */
	prev->next = next; next->prev = prev;
}

/* moves an element from it's current list to the one specified */
static inline void list_move(list_t *head, list_t *elem)
{
	list_remove(elem);
	list_append(head, elem);
}

static inline int list_is_empty(list_t *head)
{
	return (head->next == head->prev) ? 1 : 0;
}

/* 
 * Convenience macros
 *
 * If the embedded list_t is the first member
 * of a struct, you can just cast iter to
 * list_t *
 */

#define list_iterate(iter, head) \
	for(iter = (head)->next; iter != (head); iter = iter->next)

#define list_iterate_reverse(iter, head) \
	for(iter = (head)->prev; iter != (head); iter = iter->prev)


