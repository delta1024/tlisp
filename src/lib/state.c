#include "tlisp/state.h"
#include "chunk.h"
#include "errors.h"
#include "memory.h"
#include "state.h" // IWYU pragma: keep
#include "tlisp/errors.h"
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
    state->vm.chunk = NULL;
    state->vm.ip = NULL;
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
