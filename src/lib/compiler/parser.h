#ifndef _TLISP_PARSER_H__
#define _TLISP_PARSER_H__

#include "core/memory.h"
#include "scanner.h"
#include "tlisp/types.h"
#include "token.h"
#include "arrays/chunk.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct  {
    allocator *alloc;
    tscanner scanner;
    ttoken current;
    ttoken previous;
    chunk_t *chunk;
    FILE *errstream;
    bool had_err;
    bool panic_mode;
} tparser;

void parser_init(tparser *parser, const char *source, int len,
                 FILE *errstream, allocator *alloc);
tlisp_result_t compile(tparser *parser, chunk_t *chunk);
#endif // !_TLISP_PARSER_H__
