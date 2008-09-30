/* simple ring buffer implementation */
#include <kmalloc.h>
#include <ringbuffer.h>
#include <asm/stddef.h>

size_t ringbuf_write(ringbuf_t *rb, const void *d, size_t len)
{
	const uint8_t *data = d;
	uint8_t *buffer = rb->buffer;
	size_t i, end = rb->end;
	
	if( rb->bytes == rb->size) /* prevent writing into a full buffer*/
		return 0;

	for(i = 0; i < len && (end != rb->start || rb->bytes == 0); i++, end++) {
		if( end == rb->size - 1) {
			end = 0;
		}

		buffer[end] = data[i];
	}

	rb->bytes += i;
	rb->end = end;

	return i;
}

size_t ringbuf_read(ringbuf_t *rb, void *d, size_t len)
{
   	const uint8_t *buffer = rb->buffer;
	uint8_t *data = d;
	size_t i, start = rb->start;

	if( rb->bytes == 0) // can't read an empty buffer
		return 0;

	for(i = 0; i < len && (start != rb->end || rb->bytes == (rb->size - 1)); i++, start++) {
		if( start == rb->size - 1) {
			start = 0;
		}

		data[i] = buffer[start];
	}

	rb->bytes -= i;
	rb->start = start;
	
	return i;
}

void ringbuf_delete(ringbuf_t *rb)
{
	kfree(rb->buffer);
	kfree(rb);
}

ringbuf_t *ringbuf_create(size_t bufsize)
{
	ringbuf_t *rb;

	rb = (ringbuf_t *) kmalloc(sizeof(ringbuf_t));
	if(rb == NULL)
		return NULL;

	rb->buffer = kmalloc(bufsize);
	if(rb->buffer == NULL) {
		kfree(rb);
		return NULL;
	}

	rb->start = 0;
	rb->bytes = 0;
	rb->size = bufsize;
	rb->end = 0;
	
	return rb;
}

