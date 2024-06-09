#include "state.h" // IWYU pragma: keep
#include "stdarg.h"
#include <stdlib.h>
bool tlisp_error_next(tlisp_state *state, tlisp_error *err) {
    return error_next(&state->errors, err);
}

void tlisp_error_free(tlisp_error *error) {
    free(error->message);
}
int tlisp_error_flush(tlisp_state *state, FILE *stream) {
    error_array *arr = &state->errors;
    for (; arr->read_pos < arr->count; arr->read_pos++) {
        tlisp_error *error = &arr->errors[arr->read_pos];
        if (0 > fprintf(stream, "%.*s\n", error->mlen, error->message)) {
            free(error->message);
            return 1;
        }
        free(error->message);
    }
    return 0;
}

void tlisp_error_report(tlisp_state *state, int errn, const char *message,
                        ...) {
    FILE *errs = error_openstream(&state->errors);
    va_list args;
    va_start(args, message);
    error_vadderror(errs, errn, message, args);
    va_end(args);
    fclose(errs);
}
