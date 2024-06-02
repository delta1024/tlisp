#ifndef _TLISP_DEBUG_H__
#define _TLISP_DEBUG_H__
#include "arrays/chunk.h"

void debug_dissasemble_chunk(const chunk *chunk, const char *name);
int debug_dissasemble_instruction(const chunk *chunk, int offset);

#endif // !_TLISP_DEBUG_H__
