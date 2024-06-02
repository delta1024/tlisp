#include "tlisp/state.h"
#include "arrays/chunk.h"
#include "config.h"
#include "core/errors.h"
#include "core/memory.h"
#include "runtime/opcode.h" // IWYU pragma: keep
#include "runtime/vm.h"
#include "state.h"          // IWYU pragma: keep
#include "tlisp/errors.h"
#include "tlisp/types.h"
#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG_PRINT_CODE
#include "debug/debug.h"
#endif /* ifdef DEBUG_PRINT_CODE                                               \
#include "debug/debug.h" */
tlisp_state *tlisp_state_open() {
    tlisp_state *state = malloc(sizeof(tlisp_state));
    if (state == NULL)
        return NULL;
    state->mem_usage               = (mem_tracker){0, 0};
    state->allocator.total_alloced = 0;
    state->allocator.ud            = &state->mem_usage;
    state->allocator.f             = default_callbacks;
    state->errors                  = (error_array){NULL};
    chunk_init(&state->chunk);
    state->vm.chunk  = NULL;
    state->vm.ip     = NULL;
    state->vm.errout = error_openstream(&state->errors);
    return state;
}
void tlisp_state_close(tlisp_state *state) {
    tlisp_error err;
    while (tlisp_error_next(state, &err)) {
        tlisp_error_free(&err);
    }
    free(state->errors.errors);
    chunk_free(&state->chunk, &state->allocator);
    fclose(state->vm.errout);
    free(state);
}
tlisp_result_t tlisp_state_loadbuffer(tlisp_state *state, const char *buffer,
                                      int blen) {
    int pos = chunk_writeconstant(&state->chunk, 33, &state->allocator);
    chunk_writebyte(&state->chunk, OP_CONSTANT, 0, &state->allocator);
    chunk_writebyte(&state->chunk, pos, 0, &state->allocator);
    chunk_writebyte(&state->chunk, OP_RETURN, 1, &state->allocator);
#ifdef DEBUG_PRINT_CODE
    debug_dissasemble_chunk(&state->chunk, "test chunk");
    printf("\n");
#endif /* ifdef DEBUG_PRINT_CODE */
    return TLISP_RESULT_OK;
}

tlisp_result_t tlisp_state_call(tlisp_state *state, int dist, int params,
                                int nret_vals) {
    vm *vm    = &state->vm;
    vm->chunk = &state->chunk;
    vm->ip    = vm->chunk->code;

    tlisp_result_t check = TLISP_RESULT_OK;
    if (!(check = vm_interpret(vm)))
        return check;
    return check;
}
