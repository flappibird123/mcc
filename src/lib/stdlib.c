#include "lib/stdlib.h"

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
