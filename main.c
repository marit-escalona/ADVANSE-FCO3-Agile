#include <stdio.h>
#include <stdlib.h>

#include "trl.h"
#include "input.h"
#include "program.h"
#include "user.h"

void run_prog_edit_menu()
{
    TimeRecordingLog *trl;
    int cmdCode;

    do {
        cmdCode = input_projedit_read();

        switch (cmdCode) {
        case CMD_SET_TRL_INFO:
            input_set_trl_info(trl);
            trl_print(trl);
            break;
        case CMD_ADD_TRL_ENTRY:
            input_add_trl_entry(trl);
            break;
        case CMD_VIEW_TRL_ENTRIES:
            trl_print(trl);
            break;
        case CMD_SAVE_TRL:
            break;
        case CMD_EXIT:
            break;
        default:
            printf("Unknown command code\n");
            break;
        }
    } while (cmdCode != CMD_EXIT);

    printf("Bye!\n");
}

int main(int argc, char **argv)
{
    int cmdCode = -1;
    int isEditingProject = 0;

    User *user;
    Program *program;

    printf("Creating a user:\n");
    user = input_create_user();

    printf("Hello, %s!\n\n", user->name);

     // Project/TRL input state menu
    while (cmdCode != CMD_EXIT) {
        printf("%s has %d programs.\n", user->name, user->numPrograms);
        cmdCode = input_projmenu_read();

        switch (cmdCode) {
        case CMD_CREATE_PROGRAM:
            input_create_program_for_user(user);
            break;
        case CMD_EDIT_PROGRAM:
            break;
        case CMD_LIST_PROGRAMS:
            user_print_programs(user);
            break;
        case CMD_EXIT:
            break;
        default:
            printf("Unrecognized command code.\n");
            break;
        }
    }

    printf("Bye!\n");
    return 0;
}

