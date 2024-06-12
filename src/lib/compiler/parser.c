#include "parser.h"
#include "arrays/chunk.h"
#include "core/errors.h" // IWYU pragma: keep
#include "runtime/opcode.h"
#include "scanner.h"
#include "tlisp/types.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef tlisp_result_t (*parse_callback_t)(tparser*);
parse_callback_t get_callback(ttoken_t id);
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
static void emit_bytes(tparser *parser, int byte, int byte2) {
    emit_byte(parser,byte);
    emit_byte(parser, byte2);
}
static void emit_return(tparser *parser) {
    emit_byte(parser, OP_RETURN);
}
static void emit_constant(tparser *parser, tlisp_value value) {
    int pos = chunk_writeconstant(current_chunk(parser), value, parser->alloc);
    emit_bytes(parser, OP_CONSTANT, pos);
}
static void end_compiler(tparser *parser) {
    emit_return(parser);
}

static tlisp_result_t parse_expr(tparser *parser) {
    tlisp_result_t res = TLISP_RESULT_OK;
    advance(parser);
    ttoken *previous =  &parser->previous;
    parse_callback_t callback = get_callback(previous->type);
    if (callback == NULL) {
        return error(parser, TLISP_ERR_EXPECTED_EXPRESSION, "expected expression");
    }
    if (!(res =callback(parser)))
        return res;
    return res;
}
static tlisp_result_t expression(tparser *parser) {
    tlisp_result_t res = TLISP_RESULT_OK;
    if (!(res = parse_expr(parser)))
        return res;

    return res;
}
static tlisp_result_t binary(tparser *parser) {
    ttoken op = parser->previous;
    tlisp_result_t res = TLISP_RESULT_OK;
    if (!(res = expression(parser)))
        return res;
    if (!(res = expression(parser)))
        return res;
    switch (op.type) {
    case TOKEN_PLUS:
            emit_byte(parser, OP_ADD);
        break;
        case TOKEN_MINUS:
        emit_byte(parser, OP_SUBTRACT);
        break;
        case TOKEN_STAR:
            emit_byte(parser, OP_MULTIPLY);
        break;
        case TOKEN_SLASH:
        emit_byte(parser, OP_DIVIDE);
        break;
        default:
        return error_at(parser->errstream, TLISP_ERR_EXPECTED_BINARY_TOKEN, &op, "expected binary operator", &parser->panic_mode, &parser->had_err);
    }
    return res;
}
tlisp_result_t parser_compile(tparser *parser, chunk_t *chunk) {
    parser->chunk = chunk;
    advance(parser); // prime the pump.
    expression(parser);
    consume(parser, TOKEN_EOF, TLISP_ERR_EXPECTED_EOF, "expected end of file");
    end_compiler(parser);
    if (parser->had_err) 
        return TLISP_RESULT_ERR;
    return TLISP_RESULT_OK;
}

static tlisp_result_t number(tparser *parser) {
                                ttoken *token = &parser->previous;
    tlisp_number_t lit = strtod(token->start, NULL);
    emit_constant(parser, lit);
    return TLISP_RESULT_OK;
}

parse_callback_t parse_fns[] = {
    [TOKEN_EOF] = NULL,
    [TOKEN_PLUS] = binary,
    [TOKEN_MINUS] = binary,
    [TOKEN_STAR] = binary,
    [TOKEN_SLASH] = binary,
    [TOKEN_TICK] = NULL,
    [TOKEN_LPAREN] = NULL,
    [TOKEN_RPAREN] = NULL,
    [TOKEN_EQUAL] = NULL,
    [TOKEN_EQUAL_EQUAL] = NULL,
    [TOKEN_GT] = NULL,
    [TOKEN_GT_EQUAL] = NULL,
    [TOKEN_LT] = NULL,
    [TOKEN_LT_EQUAL] = NULL,
    [TOKEN_BANG] = NULL,
    [TOKEN_BANG_EQUAL] = NULL,
    [TOKEN_STRING] = NULL,
    [TOKEN_NUMBER] = number,
    [TOKEN_NAME] = NULL,
    [TOKEN_QUOTE] = NULL,
    [TOKEN_CONS] = NULL,
    [TOKEN_CAR] = NULL,
    [TOKEN_TRUE] = NULL,
    [TOKEN_FALSE] = NULL,
};
parse_callback_t get_callback(ttoken_t id) {
    return parse_fns[id];
}
