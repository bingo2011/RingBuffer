/* Ring buffer implementation */
#include "ringbuffer.h"
#include <assert.h>
#include <string.h>

int ringbuffer_empty(RINGBUFFER_T *rb)
{
	/* It's empty when the read and write pointers are the same. */
	if (0 == rb->fill) {
		return 1;
	}else {
		return 0;
	}
}

int ringbuffer_full(RINGBUFFER_T *rb)
{
	/* It's full when the write ponter is 1 element before the read pointer*/
	if (rb->size == rb->fill) {
		return 1;
	}else {
		return 0;
	}
}

int ringbuffer_read(RINGBUFFER_T *rb, unsigned char* buf, unsigned int len)
{
	assert(len>0);
	if (rb->fill >= len) {
		// in one direction, there is enough data for retrieving
		if (rb->write > rb->read) {
			memcpy(buf, rb->read, len);
			rb->read += len;
		}else if (rb->write < rb->read) {
			int len1 = rb->buffer + rb->size - 1 - rb->read + 1;
			if (len1 >= len) {
				memcpy(buf, rb->read, len);
				rb->read += len;
			} else {
				int len2 = len - len1;
				memcpy(buf, rb->read, len1);
				memcpy(buf + len1, rb->buffer, len2);
				rb->read = rb->buffer + len2; // Wrap around
			}
		}
		rb-> fill -= len;
		return len;
	} else	{
		return 0;
	}
}

int ringbuffer_write(RINGBUFFER_T *rb, unsigned char* buf, unsigned int len)
{
	assert(len > 0);
	if (rb->size - rb->fill < len) {
		return 0;
	}
	else {
		if (rb->write >= rb->read) {
			int len1 = rb->buffer + rb->size - rb->write;
			if (len1 >= len) {
				memcpy(rb->write, buf, len);
				rb->write += len;
			} else {
				int len2 = len - len1;
				memcpy(rb->write, buf, len1);
				memcpy(rb->buffer, buf+len1, len2);
				rb->write = rb->buffer + len2; // Wrap around
			}
		} else {
			memcpy(rb->write, buf, len);
			rb->write += len;
		}
		rb->fill += len;
		return len;
	}
}
