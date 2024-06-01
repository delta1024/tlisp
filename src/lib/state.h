#ifndef _TLISP_STATE_H__
#define _TLISP_STATE_H__
#include "core/memory.h"
#include "core/errors.h"
#include "runtime/vm.h"
#include "arrays/chunk.h"
#include <stddef.h>
struct tlisp_state {
    error_array errors;
    mem_tracker mem_usage;
    allocator allocator;
    chunk chunk;
    vm vm;
};
#endif // !_TLISP_STATE_H__
