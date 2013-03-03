
#ifndef _PROJECT_H_
#define _PROJECT_H_

#include "trl.h"

struct Program {
    int programNumber;
    TimeRecordingLog trl;
};

typedef struct Program Program;

Program *program_new();

#endif // _PROJECT_H_

