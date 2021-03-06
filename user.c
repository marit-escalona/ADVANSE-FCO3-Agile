
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

User *user_new()
{
    User *user;

    user = malloc(sizeof(User));
    if (user == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    user_init(user);

    return user;
}

void user_init(User *user)
{
    memset(user->programs, 0, sizeof(Program *) * 10);
    user->rowID = -1;
    user->numPrograms = 0;
}

void user_set_name(User *user, char *name)
{
    strcpy(user->name, name);
}

void user_add_program(User *user, Program *program)
{
    user->programs[user->numPrograms++] = program;
}

void user_print_programs(User *user)
{
    int i;

    printf("%s has %d programs:\n", user->name, user->numPrograms);
    printf("Index\tPROG #\n");
    for (i = 0; i < user->numPrograms; i++) {
        printf("%d\t%s\n", i, user->programs[i]->programNumber);
    }

    printf("\n");
}

