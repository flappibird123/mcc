#include "lib/unistd.h"
#include "lib/stdlib.h"

int main(int argc, const char* argv[]) {

    write(1, "Hello\n", 6);

    exit(25);

    return 0;
}
