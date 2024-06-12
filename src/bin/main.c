#include "tlisp/state.h"
#include <stdio.h>
#include <string.h>
#include <tlisp.h>

int main(void) {
    tlisp_state *state = tlisp_state_open();
    char buffer[1024];
    for (;;) {
        printf("> ");
        if(!fgets(buffer, 1024, stdin)) {
            printf("\n");
            break;
        }

        if (!tlisp_state_loadbuffer(state, buffer, strlen(buffer)))
            goto handle_err;

        if (!tlisp_state_call(state, 0,0,0))
            goto handle_err;

        continue;
    handle_err:
        tlisp_error_flush(state, stderr);
    }
    tlisp_state_close(state);
}
