#include "lib/unistd.h"

extern ssize_t _write(int fd, const void* buf, size_t count);

ssize_t write(int fd, const void* buf, size_t count) {
    return _write(fd, buf, count);
}
