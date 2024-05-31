#ifndef _TLISP_STATE_H__
#define _TLISP_STATE_H__
#include "memory.h"
#include "errors.h"
#include <stddef.h>
struct tlisp_state {
    error_array errors;
    mem_tracker mem_usage;
    allocator allocator;
};
#endif // !_TLISP_STATE_H__
