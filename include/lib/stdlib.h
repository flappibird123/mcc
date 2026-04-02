#ifndef MCC_LIB_STDLIB_H
#define MCC_LIB_STDLIB_H

#include "lib/stddef.h"

// exit program with exit code 
// status is used as exit code
void exit(int status);

void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#endif // MCC_LIB_STDLIB_H

