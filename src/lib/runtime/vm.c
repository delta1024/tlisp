#include "vm.h"
#include "config.h"
#include "core/errors.h"
#include "opcode.h"
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
tlisp_result_t vm_interpret(vm *vm) {
#define read_byte() (*vm->ip++)
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        debug_dissasemble_instruction(vm->chunk, vm->ip - vm->chunk->code);
#endif /* ifdef DEBUG_TRACE_EXECUTION */
        int byte = read_byte();
        switch (byte) {
        case OP_RETURN:
            return TLISP_RESULT_OK;
        default:
            runtime_error(vm, TLISP_ERR_WRNG_OPCODE, "unknown opcode %d", byte);
            return TLISP_RESULT_ERR;
        }
    }
#undef read_byte
}
