#ifndef _TLISP_ERRORS_H__
#define _TLISP_ERRORS_H__
#include "tlisp/types.h"
#include <stdio.h>
typedef enum {
    TLISP_RESULT_OK,
    TLISP_RESULT_ERR,
} result_t;
typedef struct error_array {
    int count;
    int capacity;
    int read_pos;
    tlisp_error *errors;
} error_array;
FILE *error_openstream(error_array *array);
void error_adderror(FILE *stream, tlisp_error_t errn, const char *format, ...);
void error_vadderror(FILE *stream, tlisp_error_t errn, const char *format, va_list args);
#endif // !_TLISP_ERRORS_H__
