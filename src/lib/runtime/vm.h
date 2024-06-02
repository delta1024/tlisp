#ifndef _TLISP_VM_H__
#define _TLISP_VM_H__
#include "arrays/chunk.h"
#include "core/stack.h"
#include "tlisp/types.h"
#include <stdio.h>

typedef struct {
    chunk_t *chunk;
    uint8_t *ip;
    value_stack *stack;
    FILE *errout;
} vm;

tlisp_result_t vm_interpret(vm *vm);

#endif // !_TLISP_VM_H__
