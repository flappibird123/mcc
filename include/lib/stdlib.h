#ifndef MCC_LIB_STDLIB_H
#define MCC_LIB_STDLIB_H

#include "lib/stddef.h"

// exit program with exit code 
// status is used as exit code
void exit(int status);

// *FAKE* heap allocation
// works by using a fixed array
// point is to make memory persist across functions 
// array does not grow dynamically
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

// conversion functions
long strtol(const char* nptr, char** endptr, int base);

#endif // MCC_LIB_STDLIB_H

