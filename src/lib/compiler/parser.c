#include "parser.h"
#include "arrays/chunk.h"
#include "core/errors.h" // IWYU pragma: keep
#include "runtime/opcode.h"
#include "scanner.h"
#include "tlisp/types.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>

void parser_init(tparser *parser, const char *source, int len, FILE *errstream, allocator *alloc) {
    scanner_init(&parser->scanner, source, len);
    parser->alloc = alloc;
    parser->errstream = errstream;
    parser->chunk = NULL;
    parser->had_err = parser->panic_mode = false;
}

static tlisp_result_t error_at(FILE *stream, tlisp_error_t errn, ttoken *token, const char *message, bool *panic_mode, bool *had_err) {
    if (*panic_mode) return TLISP_RESULT_ERR;
    *panic_mode = true;
    fprintf(stream, "%d[line %d] Error", errn, token->line);

    if (token->type == TOKEN_EOF) {
        fprintf(stream, " at end");
    } else if (token->type == TOKEN_ERROR) {
        // do nothing.
    } else {
        fprintf(stream, " at %.*s", token->len, token->start);
    }
    fprintf(stream, ": %s\n", message);
    *had_err = true;
    return TLISP_RESULT_ERR;
}
static tlisp_result_t error(tparser *parser,tlisp_error_t errn, const char *message) {
    error_at(parser->errstream, errn, &parser->previous, message, &parser->panic_mode, &parser->had_err);
    return TLISP_RESULT_ERR;
}
static tlisp_result_t error_at_current(tparser *parser, tlisp_error_t errn,const char *message) {
    error_at(parser->errstream, errn, &parser->current, message, &parser->panic_mode, &parser->had_err);
    return TLISP_RESULT_ERR;
}
static void advance(tparser *parser) {
    parser->previous = parser->current;
    for (;;) {
        parser->current = scanner_next(&parser->scanner);
        if (parser->current.type != TOKEN_ERROR) {
            break;
        }
        error_at_current(parser, TLISP_ERR_UNTERMITATED_STRING, parser->current.start);
    }
}

static tlisp_result_t consume(tparser *parser, ttoken_t type, tlisp_error_t errn, const char *message) {
    if (parser->current.type == type) {
        advance(parser);
        return TLISP_RESULT_OK;
    }
    return error_at_current(parser, errn, message);
}

static chunk_t *current_chunk(tparser *parser) {
    return parser->chunk;
}
static void emit_byte(tparser *parser, int byte) {
    chunk_writebyte(current_chunk(parser), byte, parser->previous.line, parser->alloc);
}
static void emit_return(tparser *parser) {
    emit_byte(parser, OP_RETURN);
}
static void end_compiler(tparser *parser) {
    emit_return(parser);
}

tlisp_result_t parser_compile(tparser *parser, chunk_t *chunk) {
    parser->chunk = chunk;
    advance(parser); // prime the pump.
    consume(parser, TOKEN_EOF, TLISP_ERR_EXPECTED_EOF, "expected end of file");
    end_compiler(parser);
    if (parser->had_err) 
        return TLISP_RESULT_ERR;
    return TLISP_RESULT_OK;
}
