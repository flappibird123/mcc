#ifndef MCC_FRONTEND_PARSER_H
#define MCC_FRONTEND_PARSER_H

#include "ast.h"
#include "vector_token.h"
#include "lexer.h"

#include "lib/stddef.h"

struct parser {
    struct lexer* l;

    struct expr* ast;
    struct vector_token tokens;
    
    size_t current;
};

void parser_init(struct parser* p, struct lexer* l);
struct expr* parser_run(struct parser* p);
void parser_free(struct parser* p);

#endif // MCC_FRONTEND_PARSER_H

