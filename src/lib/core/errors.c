#include "tlisp/errors.h"
#include "errors.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write(error_stream *cookie, const char *buf, int size);

 error_stream error_openstream(error_array *array) {
    error_stream stream = {array, 0};
    return stream;
}

void error_adderror(error_stream *stream, tlisp_error_t errn, const char *format, ...) {
    va_list args;
    va_start(args, format);
    error_vadderror(stream, errn, format, args);
    va_end(args);
}
void error_vadderror(error_stream *stream, tlisp_error_t errn, const char *format,
                     va_list args) {
    va_list arg_count;
    va_copy(arg_count, args);
    int size = vsnprintf(NULL, 0, format, arg_count) + 1;
    va_end(arg_count);

    char *buffer = malloc(size);
    size         = vsnprintf(buffer, size, format, args);
    buffer[size] = 0;
    write(stream, buffer, errn);
    free(buffer);
}
void error_freearray(error_array *array, int _start) {
    int start = _start;

    for (; start < array->count; start++) {
        tlisp_error_free(&array->errors[start]);
    }
    free(array->errors);
    array->errors   = NULL;
    array->count = array->capacity = 0;
}

bool error_next(error_stream *array, tlisp_error *err) {
    if (array->index == array->errors->count)
        return false;

    *err = array->errors->errors[array->index++];
    return true;
}
/* ------------------------
 * |       Interface      |
 * ------------------------
 */

/* ------------------------
 * |      Callbacks       |
 * ------------------------
 */

void write(error_stream *array, const char *buf, int errn) {
    tlisp_error error;
    error.message = malloc(strlen(buf) + 1);
    int written = snprintf(error.message, strlen(buf) + 1, "%s", buf);
    error.message[written] = '\0';
    error.mlen         = strlen(error.message);
    error.code = errn;
    if (array->errors->count + 1 > array->errors->capacity) {
        array->errors->capacity = array->errors->capacity < 8 ? 8 : array->errors->capacity * 2;
        array->errors->errors =
            realloc(array->errors->errors, array->errors->capacity * sizeof(tlisp_error));
    }
    array->errors->errors[array->errors->count++] = error;
}
