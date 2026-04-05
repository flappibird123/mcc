#ifndef MCC_FRONTEND_VECTOR_TOKEN_H
#define MCC_FRONTEND_VECTOR_TOKEN_H

#include "lib/stddef.h"

#include "token.h"

struct vector_token {
    struct token* data;
    size_t size;
    size_t capacity;
};

void vector_token_init(struct vector_token* tv, size_t initial_capacity);
void vector_token_push_back(struct vector_token* tv, struct token elem);
struct token vector_token_at(struct vector_token* tv, size_t index);
struct token* avector_token_at(struct vector_token* tv, size_t index);
void vector_token_free(struct vector_token* tv);

#endif // MCC_FRONTEND_VECTOR_TOKEN_H

