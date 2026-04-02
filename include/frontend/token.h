#ifndef MCC_FRONTEND_TOKEN_H
#define MCC_FRONTEND_TOKEN_H

#include "lib/stddef.h"

enum tokentype {
    
    TK_INTEGER_LITERAL,
    
    TK_PLUS,
    TK_MINUS,
    TK_STAR,
    TK_SLASH,

    TK_OPENPAREN,
    TK_CLOSEPAREN,

    TK_EOF
};

struct token {
    enum tokentype type;
    char* lexeme;
    size_t length;
    size_t line;
    size_t column;
};

#endif // MCC_FRONTEND_TOKEN_H

