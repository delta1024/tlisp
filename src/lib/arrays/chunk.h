#ifndef _TLISP_CHUNK_H__
#define _TLISP_CHUNK_H__
#include "arrays/value.h"
#include "tlisp/common.h" // IWYU pragma: keep
#include "tlisp/types.h"

typedef struct {
    uint8_t *code;
    uint8_t *lines;
    int count;
    int capacity;
    value_array constants;
} chunk_t;

void chunk_init(chunk_t *chunk);
void chunk_writebyte(chunk_t *chunk, uint8_t byte, uint8_t line,
                     allocator *allocator);
int chunk_writeconstant(chunk_t *chunk, tlisp_value value, allocator *allocator);
void chunk_free(chunk_t *chunk, allocator *allocator);
#endif // !_TLISP_CHUNK_H_i_
