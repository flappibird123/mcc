#ifndef MCC_FRONTEND_AST_H
#define MCC_FRONTEND_AST_H

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

#endif // MCC_FRONTEND_AST_H
       
