#include "test_common.h"
#include <stdio.h>
#include <stdarg.h>
int _test_fail(const char *callee, const char *message, ...){
    fprintf(stderr,"not ok: %s - ", callee);
    va_list args;
    va_start(args, message);
    vfprintf(stderr, message, args);
    fprintf(stderr, "\n");
    return 1;
}
int _test_pass(const char *callee) {
    printf("ok: %s/n",callee);
    return 0;
}
