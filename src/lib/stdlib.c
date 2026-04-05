#include "lib/stdlib.h"

#include "lib/ctype.h"
#include "lib/limits.h"
#include "lib/stddef.h"
#include "lib/errno.h"
/*

#include "lib/stddef.h"

void exit(int status);

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

long strtol(const char* nptr, char** endptr, int base);

*/

extern void _exit(int status);

void exit(int status) {
    _exit(status);
}

#define HEAP_SIZE 1024 * 1024 * 512

static unsigned char heap[HEAP_SIZE];
static int heap_initialized = 0;
static struct block* free_list = NULL;

struct block {
    size_t size;
    int free;
    struct block* next;
};

static void heap_init() {
    free_list = (struct block*)heap;
    free_list->size = HEAP_SIZE - sizeof(struct block);
    free_list->free = 1;
    free_list->next = NULL;
    heap_initialized = 1;
}

void* malloc(size_t size) {
    if (!heap_initialized) {
        heap_init();
    }

    if (size == 0) {
        return NULL;
    }

    // align to 8 bytes
    size = (size+ 7) & ~7;

    struct block* curr = free_list;
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size >= size + sizeof(struct block) + 8) {
                struct block* new_block = (struct block*)((unsigned char*)(curr +1) + size);
                new_block->size = curr->size - size - sizeof(struct block);
                new_block->free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }

            curr->free = 0;
            return (void*)(curr + 1);
        }
        curr = curr->next;
    }
    return NULL;
}

void* realloc(void* ptr, size_t size) {
    if (!ptr) {
        return malloc(size);
    }
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    struct block* curr_block = ((struct block*)ptr) - 1;
    
    if (curr_block->size >= size) {
        return ptr;
    }

    void* new_ptr = malloc(size);
    if (!new_ptr) {
        return NULL;
    }

    size_t copy_size = curr_block->size < size ? curr_block->size : size;
    unsigned char* src = (unsigned char*)ptr;
    unsigned char* dst = (unsigned char*)new_ptr;
    for (size_t i = 0; i < copy_size; ++i) {
        dst[i] = src[i];
    }

    free(ptr);
    return new_ptr;
}

void free(void* ptr) {
    if (!ptr) {
        return;
    }

    struct block* block = ((struct block*)ptr) - 1;
    block->free = 1;

    // coalesce adjacent free blocks
    struct block* curr = free_list;
    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += sizeof(struct block) + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

long strtol(const char* nptr, char** endptr, int base) {
    const char* s = nptr;
    unsigned long acc = 0;
    int neg = 0;
    int any = 0;

    errno = 0;

    while (isspace((unsigned char)*s)) {
        s++;
    }

    if (*s == '-') {
        neg = 1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    if (base == 0) {
        if (*s == '0') {
            if (s[1] == 'x' || s[1] == 'X') {
                base = 16;
                s += 2;
            } else {
                base = 8;
                s++;
            }
        } else {
            base = 10;
        }
    } else if (base == 16) {
        if (*s == '0' && (s[1] == 'x' || s[1] == 'X')) {
            s += 2;
        }
    }

    const char* start = s;

    while (*s) {
        int digit;

        if ('0' <= *s && *s <= '9') {
            digit = *s - '0';
        } else if ('a' <= *s && *s <= 'z') {
            digit = *s - 'a' + 10;
        } else if ('A' <= *s && *s <= 'Z') {
            digit = *s - 'A' + 10;
        } else {
            break;
        }

        if (digit >= base) {
            break;
        }

        // check for overflow in unsigned arithmetic
        if (acc > (ULONG_MAX - digit) / (unsigned long)base) {
            any = 1;
            errno = ERANGE;
            // assign safe max values without signed overflow
            acc = neg ? (unsigned long)LONG_MAX + 1UL : LONG_MAX;

            while (*s) {
                int skip_digit;

                if ('0' <= *s && *s <= '9') {
                    skip_digit = *s - '0';
                } else if ('a' <= *s && *s <= 'z') {
                    skip_digit = *s - 'a' + 10;
                } else if ('A' <= *s && *s <= 'Z') {
                    skip_digit = *s - 'A' + 10;
                } else {
                    break;
                }

                if (skip_digit >= base) {
                    break;
                }

                s++;
            }

            break;
        }

        acc = acc * (unsigned long)base + (unsigned long)digit;
        s++;
        any = 1;
    }

    if (!any) {
        if (endptr != NULL) {
            *endptr = (char*)nptr;
        }
        return 0;
    }

    if (endptr != NULL) {
        *endptr = (char*)s;
    }

    if (neg) {
        if (acc > (unsigned long)LONG_MAX + 1UL) {
            return LONG_MIN;
        }
        return -(long)acc;
    }

    if (acc > LONG_MAX) {
        return LONG_MAX;
    }

    return (long)acc;
}
