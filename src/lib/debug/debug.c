#include "debug.h" // IWYU pragma: keep
#include "arrays/chunk.h"
#include "core/value.h"
#include "runtime/opcode.h"
#include "runtime/opcode_strs.h"
#include <stdio.h>
void debug_dissasemble_chunk(const chunk_t *chunk, const char *name) {
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->count;) {
        offset = debug_dissasemble_instruction(chunk, offset);
    }
}
int simple_instruction(const char *name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}
int constant_instruction(const char *name, const chunk_t *chunk, int offset ) {
    int index = chunk->code[offset + 1];
    printf("%-16s %d '", name, index);
    value_print(chunk->constants.entries[index]);
    printf("'\n");
    return offset + 2;
}
int debug_dissasemble_instruction(const chunk_t *chunk, int offset) {
    printf("%04d ", offset);
    if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
        printf("   | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }
    int byte = chunk->code[offset];
    switch (byte) {
    case OP_CONSTANT: 
        return constant_instruction(op_strs[byte], chunk, offset);
    case OP_RETURN:
        return simple_instruction(op_strs[byte], offset);
    default:
        fprintf(stderr, "error: unknown opcode: %d\n", byte);
        return offset + 1;
    }
}
