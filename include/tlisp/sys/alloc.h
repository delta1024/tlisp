#ifndef INCLUDE_sys_tlisp_alloc_h__
#define INCLUDE_sys_tlisp_alloc_h__
#include "tlisp/common.h"
// #include "tlisp/types.h"

typedef void *(*tmalloc_t)(void *ud, size_t size);
typedef void *(*trealloc_t)(void *ud, void *ptr, size_t osize, size_t nsize);
typedef void (*tfree_t)(void *ud, void *ptr, size_t osize);
typedef size_t (*tget_total_t)(void *ud);

/** Interface for defining a custom allocator */
typedef struct {
	tmalloc_t malloc;
	trealloc_t realloc;
	tfree_t free;
	tget_total_t get_total;
} tlisp_allocator_functions ;

// /** Set the allocator for a state 
//  * @param state State to set the allocator on
//  * @param ud    Memory tracker to pass to each callback. be sure to call tlisp_alloc_update_total() after each successful allocation.
//  * @param callbacks Callbacks to call on internal allocation.
//  *
// */
// void tlisp_alloc_set_state(tlisp_state *state, void *ud, tlisp_allocator_functions callbacks);

// /** Inform the Garbage Collector about a change in total memory usage
//  * @param state An active state
//  * @param total_memory_allocated The new total amount of memory allocatet. This number should always be the same size or larger than the last value passed through this call.
//  */
// void tlisp_alloc_update_total(tlisp_state *state, size_t total_mem_allocated);
#endif // !INCLUDE_sys_tlisp_alloc_h__
