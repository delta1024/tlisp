#include "tlisp/errors.h"
#include "errors.h"
#include <alloca.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static ssize_t write(void *cookie, const char *buf, size_t size);
static cookie_io_functions_t callbacks = {
    .write = write,
    .read  = NULL,
    .seek  = NULL,
    .close = NULL,
};

FILE *error_openstream(error_array *array) {
    FILE *file = fopencookie(array, "w", callbacks);
    if (file == NULL)
        return NULL;
    setvbuf(file, NULL, _IOLBF, BUFSIZ);
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
    int size = vsnprintf(NULL, 0, format, arg_count) + 1;
    va_end(arg_count);

    char *buffer = alloca(size);
    size         = vsnprintf(buffer, size, format, args);
    buffer[size] = 0;
    fprintf(stream, "%d%s\n", errn, buffer);
}
void error_freearray(error_array *array) {
    for (; array->read_pos < array->count; array->read_pos++) {
        tlisp_error_free(&array->errors[array->read_pos]);
    }
    free(array->errors);
    array->errors   = NULL;
    array->read_pos = array->count = array->capacity = 0;
}

bool error_next(error_array *array, tlisp_error *err) {
    if (array->read_pos == array->count)
        return false;

    *err = array->errors[array->read_pos++];
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

ssize_t write(void *cookie, const char *buf, size_t size) {
    tlisp_error error;
    if (sscanf(buf, "%d%m[^\n]", &error.code, &error.message) == 0)
        return 0; // 0 if nothing written
    error.mlen         = strlen(error.message);
    error_array *array = (error_array *)cookie;
    if (array->count + 1 > array->capacity) {
        array->capacity = array->capacity < 8 ? 8 : array->capacity * 2;
        array->errors =
            reallocarray(array->errors, array->capacity, sizeof(tlisp_error));
    }
    array->errors[array->count++] = error;
    return size;
}
