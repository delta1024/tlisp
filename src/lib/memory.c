#include "memory.h"
#include "tlisp/common.h"
#include "tlisp/sys/alloc.h"
#include <stdlib.h>
void *tmalloc(allocator *allocator, size_t size) {
	void *ptr = allocator->f.malloc(allocator->ud, size);
	allocator->total_alloced = allocator->f.get_total(allocator->ud);
	return ptr;
}

void *trealloc(allocator *allocator, void *ptr, size_t nsize, size_t osize) {
	ptr =  allocator->f.realloc(allocator->ud, ptr, nsize, osize);
	allocator->total_alloced = allocator->f.get_total(allocator->ud);
	return ptr;
}

void tfree(allocator *allocator, void *ptr, size_t osize) {
	allocator->f.free(allocator->ud, ptr, osize);
}

void *itmalloc(void *ud, size_t size) {
	mem_tracker *tracker = (mem_tracker*)ud;
	void *ptr = malloc(size);
	if (ptr == NULL) {
		return NULL;
	}
	tracker->allocated += size;
	return ptr;
}
void *itrealloc(void *ud, void *ptr, size_t osize, size_t nsize) {
	mem_tracker *tracker = (mem_tracker*)ud;
	ptr = realloc(ptr, nsize);
	if (ptr == NULL) {
		return NULL;
	}
	if (osize > nsize) {
		tracker->freed += osize - nsize;
	} else {
		tracker->allocated += nsize - osize;
	}
	return ptr;
}
void itfree(void *ud, void *ptr, size_t osize) {
	mem_tracker *tracker = (mem_tracker*)ud;
	free(ptr);
	tracker->freed += osize;
}

size_t itget_total(void *ud) {
	mem_tracker *tracker = (mem_tracker*)ud;
	return tracker->allocated;
}
tlisp_allocator_functions const default_callbacks = {
	.malloc = itmalloc,
	.realloc = itrealloc,
	.free = itfree,
	.get_total = itget_total,
};
