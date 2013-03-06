
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *safe_alloc(size_t size)
{
    void *block = malloc(size);

    if (block == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }

    return block;
}

// Removes a trailing newline character from a string, if one is found.
void string_chomp(char *string)
{
    int length = strlen(string);
    if (string[length - 1] == '\n') {
        string[length - 1] = '\0';
    }
}

