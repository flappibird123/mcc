#include "lib/stdio.h"
#include "lib/stddef.h"
#include "lib/stdlib.h"
#include "lib/string.h"
#include "frontend/lexer.h"
#include "frontend/vector_token.h"
#include "frontend/token.h"

/* 
 struct token {
    enum tokentype type;
    const char* lexeme;
    size_t length;
    size_t line;
    size_t column;

    union {
        int64_t int_val;
    };
};

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



*/

static const char* tk_to_str(enum tokentype type) {
    switch (type) {
        case TK_INTEGER_LITERAL:
            return "INTEGER_LITERAL";
        case TK_PLUS:
            return "PLUS";
        case TK_MINUS:
            return "MINUS";
        case TK_STAR:
            return "STAR";
        case TK_SLASH:
            return "SLASH";
        case TK_OPENPAREN:
            return "OPENPAREN";
        case TK_CLOSEPAREN:
            return "CLOSEPAREN";
        case TK_EOF:
            return "EOF";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, const char* argv[]) {

    char* source = malloc(64);
    strcpy(source, "(1 + 2) * 3");

    struct lexer lex;
    lexer_init(&lex, source);
    struct vector_token tokens = lexer_run(&lex);
    lexer_free(&lex);

    for (size_t i = 0; i < tokens.size; ++i) {
        struct token tok = vector_token_at(&tokens, i);
        const char* type = tk_to_str(tok.type);
        putstr(1, "Type: ");
        putstr(1, type);
        putstr(1, "\n");
        char lex[512]; 
        memcpy(lex, tok.lexeme, tok.length);
        putstr(1, "Lexeme: ");
        putstr(1, lex);
        putstr(1, "\n");
    }
    vector_token_free(&tokens);
    free(source);

    return 0;
}
