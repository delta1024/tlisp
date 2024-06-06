#ifndef _TLISP_SCANNER_H__
#define _TLISP_SCANNER_H__

#include "token.h"
typedef struct {
    struct {
        const char *chars;
        int length;
    } source;
    const char *start;
    const char *current;
    int line;
} tscanner;
void scanner_init(tscanner *scanner, const char *buffer, int blen);
ttoken scanner_next(tscanner *scanner);
#endif // !_TLISP_SCANNER_H__
