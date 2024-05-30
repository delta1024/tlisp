#include "tlisp/state.h"
#include "state.h" // IWYU pragma: keep
#include "memory.h"
#include <stdlib.h>

tlisp_state *tlisp_state_open()  {
	tlisp_state *state = malloc(sizeof(tlisp_state));
	if (state == NULL) 
		return NULL;
	state->mem_usage.allocated = 0;
	state->mem_usage.freed = 0;
	state->allocator.total_alloced = 0;
	state->allocator.ud = &state->mem_usage;
	state->allocator.f = default_callbacks;
	return state;
}
void tlisp_state_close(tlisp_state *state) {
	free(state);
}
