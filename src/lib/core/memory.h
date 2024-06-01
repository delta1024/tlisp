#ifndef _TLISP_MEMORY_H__
#define _TLISP_MEMORY_H__
#include "tlisp/common.h"
#include "tlisp/sys/alloc.h"
typedef struct {
    size_t total_alloced;
    void *ud;
    tlisp_allocator_functions f;
} allocator;

typedef struct {
    size_t allocated;
    size_t freed;
} mem_tracker;
extern tlisp_allocator_functions const default_callbacks;

void *tmalloc(allocator *allocator, size_t size);
void *trealloc(allocator *allocator, void *ptr, size_t osize, size_t nsize);
void tfree(allocator *allocator, void *ptr, size_t osize);
#endif // !_TLISP_MEMORY_H__
