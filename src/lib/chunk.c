#include "chunk.h"
#include "memory.h"
#include "value.h"
#include <stddef.h>

void chunk_init(chunk *chunk) {
    chunk->code = chunk->lines = NULL;
    chunk->count = chunk->capacity = 0;
    value_array_init(&chunk->constants);
}

void chunk_free(chunk *chunk, allocator *allocator) {
    tfree(allocator, chunk->code, sizeof(uint8_t) * chunk->capacity);
    tfree(allocator, chunk->lines, sizeof(uint8_t) * chunk->capacity);
    value_array_free(&chunk->constants, allocator);
    chunk_init(chunk);
}
void chunk_writebyte(chunk *chunk, uint8_t byte, uint8_t line, allocator *allocator) {
    if (chunk->count + 1 > chunk->capacity) {
        int ocap = chunk->capacity;
        chunk->capacity = ocap < 8 ? 8 : ocap * 2;
        chunk->code = trealloc(allocator, chunk->code, sizeof(uint8_t) * ocap,
                               sizeof(uint8_t) * chunk->capacity);
        chunk->lines = trealloc(allocator, chunk->lines, sizeof(uint8_t) * ocap, 
                                sizeof(uint8_t) * chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count++] = line;
}

int chunk_writeconstant(chunk *chunk, tlisp_value value, allocator *allocator) {
    value_array_write(&chunk->constants, value, allocator);
    return chunk->constants.count - 1;
}
