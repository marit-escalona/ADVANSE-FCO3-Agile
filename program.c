
#include <stdio.h>
#include <stdlib.h>

#include "program.h"

Program *program_new()
{
    Program *program;

    program = malloc(sizeof(Program));
    if (program == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    return program;
}

