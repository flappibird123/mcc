#include "lib/string.h"


void* memcpy(void* dest, const void* src, size_t n) {
    char* _dest = (char*)dest;
    const char* _src = (const char*)src;
    for (size_t i = 0; i < n; ++i) {
        _dest[i] = _src[i];
    }
    return dest;
}

void* memmove(void* dest, const void* src, size_t n) {
    char tmp[n];
    const char* _src = (const char*)src;
    for (size_t i = 0; i < n; ++i) {
        tmp[i] = _src[i];
    }
    memcpy(dest, tmp, n);
    return dest;
}

void* memset(void* s, int c, size_t n) {
    char* _s = (char*)s;
    for (size_t i = 0; i < n; ++i) {
        _s[i] = c;
    }
    return s;
}

char* strcpy(char* dest, const char* src) {
    size_t src_len = strlen(src);
    memcpy(dest, src, src_len);
    dest[src_len] = '\0';
    return dest;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

size_t strlen(const char* s) {
    const char* p = s;
    while (*p) {
        ++p;
    }
    return p - s;
}

