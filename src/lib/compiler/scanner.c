#include "token.h"
#include "scanner.h"
#include <stdbool.h>
#include <string.h>

void scanner_init(tscanner *scanner, const char *buffer, int blen) {
    scanner->line = 0;
    scanner->start = scanner->current = scanner->source.chars = buffer;
    scanner->source.length = blen;
}
static bool at_end(tscanner *scanner){
    return (scanner->current - scanner->source.chars) == scanner->source.length;
}
static char advance(tscanner *scanner) {
    if (at_end(scanner))
        return '\0';
    return *scanner->current++;
}
ttoken create_token(tscanner *scanner, ttoken_t type) {
    ttoken token;
    token.type = type;
    token.start = scanner->start;
    token.len = scanner->current - scanner->start;
    token.line = scanner->line;
    return token;
}
ttoken err_token(tscanner *scanner, const char *message) {
    ttoken token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.len = strlen(message);
    token.line = scanner->line;
    return token;
}
ttoken scanner_next(tscanner *scanner) {
    if (at_end(scanner)) {
        return create_token(scanner, TOKEN_EOF);
    }
    scanner->start = scanner->current;
    char c = advance(scanner);
    switch (c) {
        default:
        return err_token(scanner, "unknown token");
    }
}
