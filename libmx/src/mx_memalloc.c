#include "libmx.h"

void *mx_memalloc(size_t size) {
    void *ptr;

    if ((ptr = malloc(size)))
        mx_bzero(ptr, size);
    return (ptr);
}
