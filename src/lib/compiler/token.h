#ifndef _TLISP_TOKEN_H__
#define _TLISP_TOKEN_H__

typedef enum {
    TOKEN_ERROR = -1,
    TOKEN_EOF   = 0,
    TOKEN_PLUS  = 1,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_TICK,
    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,
    TOKEN_GT,
    TOKEN_GT_EQUAL,
    TOKEN_LT,
    TOKEN_LT_EQUAL,
    TOKEN_BANG,
    TOKEN_BANG_EQUAL,

    TOKEN_STRING,
    TOKEN_NUMBER,

    TOKEN_NAME,
    TOKEN_QUOTE,
    TOKEN_CONS,
    TOKEN_CAR,
    TOKEN_TRUE,
    TOKEN_FALSE,
} ttoken_t;

typedef struct {
    ttoken_t type;
    const char *start;
    int len;
    int line;
} ttoken;

#endif // !_TLISP_TOKEN_H__
