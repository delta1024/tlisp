#ifndef _TLISP_TOKEN_H__
#define _TLISP_TOKEN_H__

typedef enum {
    TOKEN_ERROR,
    TOKEN_EOF,
} ttoken_t;

typedef struct {
    ttoken_t type;
    const char *start;
    int len;
    int line;
} ttoken ;

#endif // !_TLISP_TOKEN_H__
