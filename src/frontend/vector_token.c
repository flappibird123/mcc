#include "frontend/vector_token.h"

#include "lib/string.h"
#include "lib/stdlib.h"
#include "lib/stdio.h"
#include "lib/stddef.h"

void vector_token_init(struct vector_token* tv, size_t initial_capacity) {
    tv->size = 0;
    tv->capacity = initial_capacity < 1 ? 1 : initial_capacity;
    tv->data = malloc(initial_capacity * sizeof(struct token));
    if (!tv->data) {
        putstr(2, "memory allocation failure\n");
        exit(1);
    }
}

void vector_token_push_back(struct vector_token* tv, struct token elem) {
    if (tv->size >= tv->capacity) {
        size_t new_capacity = tv->capacity * 2; 
        struct token* tmp = realloc(tv->data, new_capacity * sizeof(struct token));
        if (!tmp) {
            putstr(2, "memory allocation failure\n");
            exit(1);
        }
        tv->capacity = new_capacity;
        tv->data = tmp;
    }
    tv->data[tv->size] = elem;
    tv->size++;
}

struct token vector_token_at(struct vector_token* tv, size_t index) {
    if (index >= tv->size) {
        putstr(2, "access out of bounds of vector_token\n");
        exit(1);
    }
    return tv->data[index];
}

void vector_token_free(struct vector_token* tv) {
    free(tv->data);
    tv->data = NULL;
    tv->size = 0;
    tv->capacity = 0;
}

struct token* avector_token_at(struct vector_token* tv, size_t index) {
    if (index >= tv->size) {
        putstr(2, "access out of bounds of vector_token\n");
        return NULL;
    }
    return tv->data + index;
}

