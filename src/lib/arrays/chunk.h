#ifndef _TLISP_CHUNK_H__
#define _TLISP_CHUNK_H__
#include "tlisp/types.h"
#include "tlisp/common.h" // IWYU pragma: keep
#include "arrays/value.h"

typedef struct {
    uint8_t *code;
    uint8_t *lines;
    int count;
    int capacity;
    value_array constants;
} chunk;

void chunk_init(chunk *chunk);
void chunk_writebyte(chunk *chunk, uint8_t byte, uint8_t line, allocator *allocator);
int chunk_writeconstant(chunk *chunk, tlisp_value value, allocator *allocator);
void chunk_free(chunk *chunk, allocator *allocator);
#endif // !_TLISP_CHUNK_H_i_
