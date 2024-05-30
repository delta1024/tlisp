#ifndef _TLISP_MEMORY_H__
#define _TLISP_MEMORY_H__
#include "tlisp/common.h"
#include "tlisp/sys/alloc.h"
typedef struct {
	void *ud;
	tlisp_allocator_functions f;
	size_t total_alloced;
} allocator_t;

typedef struct {
	size_t allocated;
	size_t freed;
} mem_tracker_t;
extern tlisp_allocator_functions const default_callbacks;

void *tmalloc(allocator_t *allocator, size_t size);
void *trealloc(allocator_t *allocator, void *ptr, size_t nsize, size_t osize);
void tfree(allocator_t *allocator, void *ptr, size_t osize);
#endif // !_TLISP_MEMORY_H__
