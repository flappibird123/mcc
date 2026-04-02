#ifndef MCC_FRONTEND_LEXER_H
#define MCC_FRONTEND_LEXER_H

#include "lib/stddef.h"

#include "token.h"
#include "vector_token.h"

struct lexer {
    const char* source;
    struct vector_token tokens;

    size_t current;
    size_t start;
    size_t column;
    size_t start_column;
    size_t line;

};

void lexer_init(struct lexer* l, const char* source);
struct vector_token lexer_run(struct lexer* l);
void lexer_free(struct lexer* l);



#endif // MCC_FRONTEND_LEXER_H

