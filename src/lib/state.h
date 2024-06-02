#ifndef _TLISP_STATE_H__
#define _TLISP_STATE_H__
#include "arrays/chunk.h"
#include "core/errors.h"
#include "core/memory.h"
#include "runtime/vm.h"
#include <stddef.h>
struct tlisp_state {
    error_array errors;
    mem_tracker mem_usage;
    allocator allocator;
    chunk_t chunk;
    vm vm;
};
#endif // !_TLISP_STATE_H__
