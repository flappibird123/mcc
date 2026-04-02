#ifndef MCC_LIB_STRING_H
#define MCC_LIB_STRING_H

#include "lib/stddef.h"

// Memory functions

// copies n bytes from src to dest
// UB if regions overlap
void* memcpy(void* dest, const void* src, size_t n);

// memcpy but safe for overlapping memory
void* memmove(void* dest, const void* src, size_t n);

// sets first n bytes of s to byte value c 
void* memset(void* s, int c, size_t n);

// String functions

// no bounds checking string copy including \0
char* strcpy(char* dest, const char* src);

// lexicographic string comparison
int strcmp(const char* s1, const char* s2);

// counts characters before \0
size_t strlen(const char* s);



#endif // MCC_LIB_STRING_H
       
