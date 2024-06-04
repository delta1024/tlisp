#ifndef _TLISP_ERRORS_H__
#define _TLISP_ERRORS_H__
#include "tlisp/types.h"
#include <stdbool.h>
#include <stdio.h>
typedef struct error_array {
    tlisp_error *errors;
    int count;
    int capacity;
    int read_pos;
} error_array;
FILE *error_openstream(error_array *array);
void error_freearray(error_array *array);
void error_adderror(FILE *stream, tlisp_error_t errn, const char *format, ...);
void error_vadderror(FILE *stream, tlisp_error_t errn, const char *format,
                     va_list args);
bool error_next(error_array *array, tlisp_error *err);
#endif // !_TLISP_ERRORS_H__
