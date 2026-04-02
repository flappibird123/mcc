#include "lib/stdio.h"

#include "lib/stddef.h"
#include "lib/unistd.h"

void putstr(int fd, const char* s) {
    size_t len = 0;
    while (s[len]) {
        ++len;
    }
    write(1, s, len);
}
