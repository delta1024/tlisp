#ifndef _TLISP_OPCODE_H__
#define _TLISP_OPCODE_H__
// IWYU pragma: begin_exports
typedef enum {
    OP_RETURN,
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
} opcode;
// IWYU pragma: end_exports
#endif // !_TLISP_OPCODE_H__
