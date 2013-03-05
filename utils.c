
#include <stdio.h>
#include <stdlib.h>

void *safe_alloc(size_t size)
{
    void *block = malloc(size);

    if (block == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    return block;
}

