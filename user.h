
#ifndef _USER_H_
#define _USER_H_

#include "program.h"

struct User {
    int rowID;
    char name[255];
    Program *programs[10]; // TODO: Use linked list for final program
    int numPrograms; // Only necessary while we're not using a linked list
};

typedef struct User User;

User *user_new();
void user_set_name(User *user, char *name);
void user_add_program(User *user, Program *program);

void user_print_programs(User *user);

#endif // _USER_H_

