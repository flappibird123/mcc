#include "frontend/lexer.h"

#include "lib/stdbool.h"
#include "lib/string.h"
#include "lib/ctype.h"
#include "lib/stddef.h"

#include "frontend/vector_token.h"


/* 

struct lexer {
    const char* source;
    struct vector_token tokens;
    size_t source_len;
    
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

    union {
        int64_t int_val;
    };
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
    l->source_len = strlen(source);
}

static bool is_at_end(struct lexer* l) {
    return l->current >= l->source_len;
}

static char peek(struct lexer* l) {
    if (is_at_end(l)) {
        return '\0';
    }
    return l->source[l->current];
}

static char peekn(struct lexer* l, size_t n) {
    if (l->current + n >= l->source_len) {
        return '\0';
    }
    return l->source[l->current + n];
}

static char advance(struct lexer* l) {
    if (is_at_end(l)) {
        return '\0';
    } 
    char c = peek(l);
    if (c == '\n') {
        l->line++;
        l->column = 0;
    } else {
        l->column++;
    }
    l->current++;
    return c;
}

static bool skip_whitespace(struct lexer* l) {
    bool skipped = false;
    while (isspace((unsigned char)peek(l)) && !is_at_end(l)) {
        skipped = true;
        advance(l); 
    }
    return skipped;
}

static bool skip_comment(struct lexer* l) {
    bool skipped = false;
    if (peek(l) == '/' && peekn(l, 1) == '/') {
        skipped = true;
        advance(l);
        advance(l);
        while (peek(l) != '\n' && !is_at_end(l)) {
            advance(l);
        }
    } else if (peek(l) == '/' && peekn(l, 1) == '*') {
        skipped = true;
        advance(l);
        advance(l);
        while (!(peek(l) == '*' && peekn(l, 1) == '/')) {
            if (is_at_end(l) || peek(l) == '\0') {
                // error: unterminated skip_comment
                // TODO: Handle error
            }
            advance(l);
        }
        advance(l);
        advance(l);
    }

    return skipped;
}

static void add_token(struct lexer* l, enum tokentype type) {
    vector_token_push_back(&l->tokens, (struct token) { type, l->source + l->start, l->current - l->start, l->line, l->start_column });
}

static void scan_integer_literal(struct lexer* l) {
    while (isdigit((unsigned char)peek(l))) {
        advance(l);
    }

    add_token(l, TK_INTEGER_LITERAL);
}

struct vector_token lexer_run(struct lexer* l) {
   
    while (!is_at_end(l)) {
        while (true) {
            if (skip_comment(l)) {
                continue;
            } else if (skip_whitespace(l)) {
                continue;
            } else {
                break;
            }
        } 

        l->start = l->current;
        l->start_column = l->column;

        char c = peek(l);

        switch (c) {
            case '+':
                advance(l);
                add_token(l, TK_PLUS);
                break;
            case '-':
                advance(l);
                add_token(l, TK_MINUS);
                break;
            case '*':
                advance(l);
                add_token(l, TK_STAR);
                break;
            case '/':
                advance(l);
                add_token(l, TK_SLASH);
                break;
            case '(':
                advance(l);
                add_token(l, TK_OPENPAREN);
                break;
            case ')':
                advance(l);
                add_token(l, TK_CLOSEPAREN);
                break;
            default:
                if (isdigit((unsigned char)c)) {
                    scan_integer_literal(l);
                } else {
                    // error: unknown character
                    // TODO: handle error
                }      
        }
    }


    return l->tokens;
}

void lexer_free(struct lexer* l) {
    vector_token_free(&l->tokens);
    l->current = 0;
    l->start = 0;
    l->column = 0;
    l->start_column = 0;
    l->line = 0;
}
