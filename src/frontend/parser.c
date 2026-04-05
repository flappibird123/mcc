#include "frontend/parser.h"

#include "lib/stdlib.h"
#include "lib/stddef.h"

/*

#include "ast.h"
#include "vector_token.h"
#include "lexer.h"

#include "lib/stddef.h"

struct parser {
    struct lexer* l;

    struct astnode* ast;
    struct vector_token tokens;
    
    size_t current;
};

void parser_init(struct parser* p, struct lexer* l);
struct astnode parser_run(struct parser* p);
void parser_free(struct parser* p);

#include "lib/stdint.h"
#include "lib/stdbool.h"

#include "token.h"

struct int_literal {
    int64_t value;
};

struct expr;

struct binop {
    enum tokentype op;
    struct expr* left;
    struct expr* right;
};

enum exprkind {
    EX_INT_LIT,
    EX_BINOP
};

struct expr {
    enum exprkind kind;
    union {
        struct int_literal integer_literal;
        struct binop binary_op;
    };
};
*/

static struct token* peek(struct parser* p) {
    return avector_token_at(&p->tokens, p->current);
}

static bool is_at_end(struct parser* p) {
    return peek(p)->type == TK_EOF;
}

static struct token* advance(struct parser* p) {
    if (is_at_end(p)) {
        return peek(p);
    }
    struct token* tok = peek(p);
    p->current++;
    return tok;
}

static bool check(struct parser* p, enum tokentype type) {
    if (is_at_end(p)) {
        return false;
    }
    return peek(p)->type == type;
}

static bool match(struct parser* p, enum tokentype type) {
    if (check(p, type)) {
        advance(p);
        return true;
    }
    return false;
}

static struct token* previous(struct parser* p) {
    return avector_token_at(&p->tokens, p->current - 1);
}

static struct expr* new_int(int64_t value) {
    struct expr* e = malloc(sizeof(struct expr));
    e->kind = EX_INT_LIT;
    e->integer_literal.value = value;
    return e;
}

static struct expr* new_binop(enum tokentype op, struct expr* left, struct expr* right) {
    struct expr* e = malloc(sizeof(struct expr));
    e->kind = EX_BINOP;
    e->binary_op.op = op;
    e->binary_op.left = left;
    e->binary_op.right = right;
    return e;
}

void parser_init(struct parser* p, struct lexer* l) {
    p->l = l;
    p->current = 0;
    p->ast = NULL;
}

static struct expr* expression(struct parser* p);

static struct expr* primary(struct parser* p) {
    if (match(p, TK_INTEGER_LITERAL)) {
        return new_int(previous(p)->int_val);
    }

    if (match(p, TK_OPENPAREN)) {
        struct expr* e = expression(p);
        if (!match(p, TK_CLOSEPAREN)) {
            // error: expected ')'
        }
        return e;
    }

    return NULL;
}

static struct expr* factor(struct parser* p) {
    struct expr* left = primary(p);

    while (match(p, TK_STAR) || match(p, TK_SLASH)) {
        enum tokentype op = previous(p)->type;
        struct expr* right = primary(p);
        left = new_binop(op, left, right);
    }
    return left;
}

static struct expr* term(struct parser* p) {
    struct expr* left = factor(p);
    while (match(p, TK_PLUS) || match(p, TK_MINUS)) {
        enum tokentype op = previous(p)->type;
        struct expr* right = factor(p);
        left = new_binop(op, left, right);
    }

    return left;
}

static struct expr* expression(struct parser* p) {
    return term(p);
}

struct expr* parser_run(struct parser* p) {
    return expression(p);
}

void parser_free(struct parser* p) {
    p->l = NULL;
    p->current = 0;
}


