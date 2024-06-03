#ifndef _TLISP_ERRORS_H__
#define _TLISP_ERRORS_H__
#include "tlisp/types.h"
#include <stdbool.h>
#include <stdio.h>
typedef struct error_array {
    tlisp_error *errors;
    int count;
    int capacity;
} error_array;

typedef struct {
    error_array *errors;
    int index;
} error_stream;
error_stream error_openstream(error_array *array);
void error_freearray(error_array *array, int start);
void error_adderror(error_stream *stream, tlisp_error_t errn, const char *format, ...);
void error_vadderror(error_stream *stream, tlisp_error_t errn, const char *format,
                     va_list args);
bool error_next(error_stream *array, tlisp_error *err);
#endif // !_TLISP_ERRORS_H__
