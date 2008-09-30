#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

/* simple ring buffer implementation */

struct ringbuf 
{
	size_t size;  /* size of the buffer */
	size_t bytes; /* numer of bytes currently in the buffer */
	size_t start, end; /* buffer offsets */
	void *buffer; /* buffer */
};

typedef struct ringbuf ringbuf_t;

size_t ringbuf_write(ringbuf_t *rb, const void *d, size_t len);
size_t ringbuf_read(ringbuf_t *rb, void *d, size_t len);
void ringbuf_delete(ringbuf_t *rb);
ringbuf_t *ringbuf_create(size_t bufsize);

#endif
