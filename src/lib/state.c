#include "tlisp/state.h"
#include "arrays/chunk.h"
#include "compiler/parser.h"
#include "compiler/scanner.h"
#include "compiler/token.h"
#include "config.h"
#include "core/errors.h"
#include "core/memory.h"
#include "core/stack.h"
#include "runtime/opcode.h" // IWYU pragma: keep
#include "runtime/vm.h"
#include "state.h"          // IWYU pragma: keep
#include "tlisp/errors.h"
#include "tlisp/types.h"
#include <stdio.h>
#include <stdlib.h>
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
    state->stack     = &state->vm.stack;
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
    parser_init(&state->parser, buffer, blen, error_openstream(&state->errors), &state->allocator);
    if (!parser_compile(&state->parser, &state->chunk))
        return TLISP_RESULT_ERR;
    return TLISP_RESULT_OK;
}

tlisp_result_t tlisp_state_call(tlisp_state *state, int dist, int params,
                                int nret_vals) {
    stack_reset(&state->vm.stack);
    state->vm.chunk = &state->chunk;
    state->vm.ip = state->chunk.code;
    if (!vm_interpret(&state->vm))
        return TLISP_RESULT_ERR;
    return TLISP_RESULT_OK;
}
