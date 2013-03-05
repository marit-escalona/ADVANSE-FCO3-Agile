
#ifndef _PROJECT_H_
#define _PROJECT_H_

#include "trl.h"

struct Program {
    char programNumber[10];
    TimeRecordingLog *trl;
};

typedef struct Program Program;

Program *program_new();
void program_set_prog_number(Program *program, char *progNumber);

void program_free(Program *program);

#endif // _PROJECT_H_

