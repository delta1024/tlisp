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
        tlisp_state_loadbuffer(state, buffer, strlen(buffer));
        tlisp_state_call(state, 0,0,0);
    }
    tlisp_state_close(state);
}
