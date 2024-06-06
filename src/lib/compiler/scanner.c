#include "scanner.h"
#include "token.h"
#include <stdbool.h>
#include <string.h>

void scanner_init(tscanner *scanner, const char *buffer, int blen) {
    scanner->line  = 0;
    scanner->start = scanner->current = scanner->source.chars = buffer;
    scanner->source.length                                    = blen;
}
static bool at_end(const tscanner *scanner) {
    return (scanner->current - scanner->source.chars) == scanner->source.length;
}
static char advance(tscanner *scanner) {
    if (at_end(scanner))
        return '\0';
    return *scanner->current++;
}
static bool check(const tscanner *scanner, char c) {
    if (at_end(scanner))
        return false;
    return *scanner->current == c;
}
static bool match(tscanner *scanner, char c) {
    if (check(scanner, c)) {
        advance(scanner);
        return true;
    }
    return false;
}
static ttoken create_token(const tscanner *scanner, ttoken_t type) {
    ttoken token;
    token.type  = type;
    token.start = scanner->start;
    token.len   = scanner->current - scanner->start;
    token.line  = scanner->line;
    return token;
}
static ttoken err_token(const tscanner *scanner, const char *message) {
    ttoken token;
    token.type  = TOKEN_ERROR;
    token.start = message;
    token.len   = strlen(message);
    token.line  = scanner->line;
    return token;
}
static bool is_number(char c) {
    return '0' <= c && c <= '9';
}
static char peek(const tscanner *scanner) {
    if (at_end(scanner)) {
        return '\0';
    }
    return *scanner->current;
}
static char peek_next(const tscanner *scanner) {
    if (at_end(scanner)) {
        return '\0';
    }

    return *(scanner->current + 1);
}
static ttoken number(tscanner *scanner) {
    while (!at_end(scanner) && is_number(peek(scanner))) {
        advance(scanner);
    }
    if (peek(scanner) == '.') {
        advance(scanner);
        while (!at_end(scanner) && is_number(peek(scanner))) {
            advance(scanner);
        }
    }
    return create_token(scanner, TOKEN_NUMBER);
}
static bool is_alpha(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}
static bool is_alpha_numer(char c) {
    return is_alpha(c) || is_number(c);
}
static ttoken_t check_ident(const tscanner *scanner, int start,
                            const char *rest, int len, ttoken_t ident) {
    if (scanner->current - start - scanner->start == len &&
        memcmp(scanner->start + start, rest, len) == 0) {
        return ident;
    }
    return TOKEN_NAME;
}
static ttoken_t identifier_type(tscanner *scanner) {
    switch (*scanner->start) {
    case 'q':
        return check_ident(scanner, 1, "uote", 4, TOKEN_QUOTE);
    case 'c':
        if (scanner->current - scanner->start > 1) {
            switch (scanner->start[1]) {
            case 'o':
                return check_ident(scanner, 2, "ns", 2, TOKEN_CONS);
            case 'a':
                return check_ident(scanner, 2, "r", 1, TOKEN_CAR);
            default:
                return TOKEN_NAME;
            }
        } else
            return TOKEN_NAME;

    case 't':
        return check_ident(scanner, 1, "rue", 3, TOKEN_TRUE);
    case 'f':
        return check_ident(scanner, 1, "alse", 4, TOKEN_FALSE);
    default:
        return TOKEN_NAME;
    }
}
static ttoken identifier(tscanner *scanner) {
    while (!at_end(scanner) && is_alpha_numer(peek(scanner))) {
        advance(scanner);
    }
    ttoken_t type = identifier_type(scanner);
    return create_token(scanner, type);
}
static void skip_whitespace(tscanner *scanner) {
    for (;;) {
        if (at_end(scanner))
            return;
        char c = peek(scanner);
        switch (c) {
        case '\n':
            scanner->line++;
        case '\t':
        case ' ':
        case '\r':
            advance(scanner);
            break;
        case ';': {
            while (!at_end(scanner) && peek_next(scanner) != '\n') {
                advance(scanner);
            }
            break;
        }
        default:
            return;
        }
    }
}
ttoken scanner_next(tscanner *scanner) {
    skip_whitespace(scanner);
    scanner->start = scanner->current;
    if (at_end(scanner)) {
        return create_token(scanner, TOKEN_EOF);
    }
    char c = advance(scanner);
    if (is_number(c)) {
        return number(scanner);
    }
    if (is_alpha(c))
        return identifier(scanner);

    switch (c) {
    case '+':
        return create_token(scanner, TOKEN_PLUS);
    case '-':
        return create_token(scanner, TOKEN_MINUS);
    case '*':
        return create_token(scanner, TOKEN_STAR);
    case '/':
        return create_token(scanner, TOKEN_SLASH);
    case '\'':
        return create_token(scanner, TOKEN_TICK);
    case '(':
        return create_token(scanner, TOKEN_LPAREN);
    case ')':
        return create_token(scanner, TOKEN_RPAREN);
    case '=':
        return create_token(scanner, match(scanner, '=') ? TOKEN_EQUAL_EQUAL
                                                         : TOKEN_EQUAL);
    case '>':
        return create_token(scanner,
                            match(scanner, '=') ? TOKEN_GT_EQUAL : TOKEN_GT);
    case '<':
        return create_token(scanner,
                            match(scanner, '=') ? TOKEN_LT_EQUAL : TOKEN_LT);
    case '!':
        return create_token(scanner, match(scanner, '=') ? TOKEN_BANG_EQUAL
                                                         : TOKEN_BANG);
    case '"': {
        while (!at_end(scanner) && peek(scanner) != '"') {
            advance(scanner);
        }
        if (at_end(scanner)) {
            return err_token(scanner, "Unterminated string");
        }
        advance(scanner);
        return create_token(scanner, TOKEN_STRING);
    }

    default:
        return err_token(scanner, "unknown token");
    }
}
