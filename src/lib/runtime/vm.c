#include "vm.h"
#include "config.h"
#include "core/errors.h"
#include "core/value.h"
#include "opcode.h"
#include "stack.h"
#include "tlisp/types.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG_TRACE_EXECUTION
#include "debug/debug.h"
#endif /* ifdef DEBUG_TRACE_EXECUTION */

tlisp_result_t runtime_error(vm *vm, tlisp_error_t errn, const char *message,
                             ...) {
    va_list args;
    va_list count;
    va_start(args, message);
    va_copy(count, args);

    int len = vsnprintf(NULL, 0, message, count) + 1;
    va_end(count);

    char *format = alloca(len);
    int end      = vsnprintf(format, len, message, args);
    format[end]  = '\0';

    va_end(args);

    int offset = vm->ip - vm->chunk->code;
    int line   = vm->chunk->lines[offset];
    error_adderror(vm->errout, errn, "Error: %s - [line: %d] in script\n",
                   format, line);
    return TLISP_RESULT_ERR;
}
tlisp_result_t vm_push(vm *vm, tlisp_value value) {
    tlisp_error_t res;
    if ((res = stack_push(vm->stack, value)) != TLISP_ERR_OK) {
        return runtime_error(vm, res, "too many values in one chunk.");
    }
    return TLISP_RESULT_OK;
}

tlisp_result_t vm_interpret(vm *vm) {
#define read_byte() (*vm->ip++)
#define read_constant() (vm->chunk->constants.entries[read_byte()])
#define binary_op(op)                                                          \
    do {                                                                       \
        tlisp_value b;                                                         \
        tlisp_value a;                                                         \
        stack_pop(vm->stack, &b);                                              \
        stack_pop(vm->stack, &a);                                              \
        if (vm_push(vm, (a op b)) != TLISP_RESULT_OK)                          \
            return TLISP_RESULT_ERR;                                           \
    } while (false);
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("\t");
        for (tlisp_value *slot = vm->stack->buffer; slot < vm->stack->stack_top; slot++) {
            printf("[ ");
            value_print(*slot);
            printf(" ]");
        }
        printf("\n");
        debug_dissasemble_instruction(vm->chunk, vm->ip - vm->chunk->code);
#endif /* ifdef DEBUG_TRACE_EXECUTION */

        int byte = read_byte();
        switch (byte) {
        case OP_ADD:
            binary_op(+);
            break;
        case OP_SUBTRACT:
            binary_op(-);
            break;
        case OP_MULTIPLY:
            binary_op(*);
            break;
        case OP_DIVIDE:
            binary_op(/);
            break;
        case OP_CONSTANT: {
            tlisp_value value = read_constant();
            if (vm_push(vm, value) != TLISP_RESULT_OK)
                return TLISP_RESULT_ERR;
            break;
        }
        case OP_RETURN: {
                tlisp_value value;
                if (stack_pop(vm->stack, &value)) {
                    value_print(value);
                    printf("\n");
                }
            return TLISP_RESULT_OK;
            }
        default:
            return runtime_error(vm, TLISP_ERR_WRNG_OPCODE, "unknown opcode %d", byte);
        }
    }
#undef read_byte
#undef read_constant
#undef binary_op
}
