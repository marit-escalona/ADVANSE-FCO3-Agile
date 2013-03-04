
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void program_set_prog_number(Program *program, char *progNumber)
{
    strcpy(program->programNumber, progNumber);
}

