#include "libmx.h"

void mx_bzero(void *s, size_t n) {
    mx_memset(s, '\0', n);
}
