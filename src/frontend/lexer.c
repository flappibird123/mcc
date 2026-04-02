#include "frontend/lexer.h"

#include "frontend/vector_token.h"

#include "lib/stdbool.h"

/* 

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
*/

void lexer_init(struct lexer* l, const char* source) {
    l->source = source;
    vector_token_init(&l->tokens, 64);
    l->current = 0;
    l->start = l->current;
    l->column = 0;
    l->start_column = l->column;
    l->line = 0;
}

struct vector_token lexer_run(struct lexer* l) {
   



    return l->tokens;
}

void lexer_free(struct lexer* l) {
    l->source = NULL;
    vector_token_free(&l->tokens);
    l->current = 0;
    l->start = 0;
    l->column = 0;
    l->start_column = 0;
    l->line = 0;
}
