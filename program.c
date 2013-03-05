
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"
#include "trl.h"

Program *program_new()
{
    Program *program;

    program = malloc(sizeof(Program));
    if (program == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    // Needs to be a pointer, so we can let its code handle the initialization
    program->trl = trl_new();
    return program;
}

void program_set_prog_number(Program *program, char *progNumber)
{
    strcpy(program->programNumber, progNumber);
}

void program_free(Program *program)
{
    free(program->trl);
    free(program);
}

