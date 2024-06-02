#include "tlisp/state.h"
#include <stdio.h>
#include <tlisp.h>

int  main(void) {
	tlisp_state *state = tlisp_state_open();
	tlisp_error error;

	if(!tlisp_state_loadbuffer(state, NULL, 0))
		goto had_err;

	if(!tlisp_state_call(state, 0,0,0))
		goto had_err;
	goto cleanup;
had_err:
	tlisp_error_next(state, &error);
	fprintf(stderr, "%.*s\n",error.mlen, error.message);
	tlisp_error_free(&error);
cleanup:
	tlisp_state_close(state);
}
