#ifndef _TLISP_VM_H__
#define _TLISP_VM_H__
#include "tlisp/types.h"
#include "arrays/chunk.h"
#include <stdio.h>

typedef struct {
    chunk *chunk;
    uint8_t *ip;
    FILE *errout;
} vm ;

tlisp_result_t vm_interpret(vm *vm);

#endif // !_TLISP_VM_H__
