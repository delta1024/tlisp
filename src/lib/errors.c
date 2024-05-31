#include "tlisp/errors.h"
#include "errors.h"
#include "state.h" // IWYU pragma: keep
#include <alloca.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static ssize_t write(void *cookie, const char *buf, size_t size);
static cookie_io_functions_t callbacks = {
    .write = write,
    .read = NULL,
    .seek = NULL,
    .close = NULL,
};
FILE *error_openstream(error_array *array) {
    FILE *file = fopencookie(array, "w", callbacks);
    if (file == NULL)
        return NULL;
    return file;
}

void error_adderror(FILE *stream, tlisp_error_t errn, const char *format, ...) {
    va_list args;
    va_start(args, format);
    error_vadderror(stream, errn, format, args);
    va_end(args);
}
void error_vadderror(FILE *stream, tlisp_error_t errn, const char *format,
                     va_list args) {
    va_list arg_count;
    va_copy(arg_count, args);
    int size = vsnprintf(NULL, 0, format, arg_count);
    va_end(arg_count);

    char *buffer = alloca(size + 1);
    size         = vsnprintf(buffer, size + 1, format, args);
    buffer[size] = 0;
    fprintf(stream, "%d %s\n", errn, buffer);
}
bool tlisp_error_next(tlisp_state *state, tlisp_error *err) {
    if (state->errors.read_pos == state->errors.count)
        return false;

    *err = state->errors.errors[state->errors.read_pos++];
    return true;
}

void tlisp_error_free(tlisp_error *error) {
    free(error->message);
}
int tlisp_error_flush(tlisp_state *state, FILE *stream) {
    error_array *arr = &state->errors;
    for (; arr->read_pos < arr->count; arr->read_pos++) {
        tlisp_error *error = &arr->errors[arr->read_pos];
        if (0 > fprintf(stream, "%.*s", error->mlen, error->message)) {
            free(error->message);
            return 1;
        }
        free(error->message);
    }
    return 0;
}

/* ------------------------
 * |      Callbacks       |
 * ------------------------
*/

ssize_t write(void *cookie, const char *buf, size_t size) {
    tlisp_error error;
    if (sscanf(buf, "%d %m[^EOF]", &error.code, &error.message) == 0) return 0;
    error.mlen = strlen(error.message);
    error_array *array = (error_array*)cookie;
    if (array->count + 1 > array->capacity) {
        array->capacity = array->capacity < 8 ? 8 : array->capacity * 2;
        array->errors = reallocarray(array->errors, array->capacity, sizeof(tlisp_error));
    }
    array->errors[array->count++] = error;
    return size;
}
