#include <stdio.h>
#include <stdlib.h>

#include <mysql.h>

#include "trl.h"
#include "input.h"
#include "program.h"
#include "user.h"

#include "dbconn.h"

Program *select_program_to_edit(User *user)
{
    int progID = -1;
    printf("Enter the ID of the program you want to edit:\n");

    while (progID < 0 || progID > user->numPrograms) {
        user_print_programs(user);

        printf("ID> ");
        scanf("%d", &progID);
    }

    printf("\n");
    return user->programs[progID];
}

void run_prog_edit_menu(User *user, Program *program)
{
    TimeRecordingLog *trl = program->trl;
    int cmdCode;

    do {
        printf("Editing program %s\n", program->programNumber);
        cmdCode = input_projedit_read();

        switch (cmdCode) {
        case CMD_ADD_TRL_ENTRY:
            input_add_trl_entry(trl);
            break;
        case CMD_VIEW_TRL_ENTRIES:
            trl_print(trl);
            break;
        case CMD_EXIT:
            break;
        default:
            printf("Unknown command code\n");
            break;
        }
    } while (cmdCode != CMD_EXIT);
}

int main(int argc, char **argv)
{
    int cmdCode = -1;
    int isEditingProject = 0;

    User *user;
    Program *program;

    MYSQL *conn;
    conn = db_connect();
    if (conn == NULL) {
        printf("Failed to connect to MySQL!\n");
        exit(1);
    } else {
        printf("Connected to MySQL.\n");
    }

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
            if (user->numPrograms == 0) {
                printf("You don't have any programs.\n\n");
            } else {
                program = select_program_to_edit(user);
                run_prog_edit_menu(user, program);
                printf("Returning to projects menu\n\n");
            }
            break;
        case CMD_LIST_PROGRAMS:
            user_print_programs(user);
            break;
        case CMD_SAVE:
            break;
        case CMD_EXIT:
            break;
        default:
            printf("Unrecognized command code.\n");
            break;
        }
    }

    mysql_close(conn);
    printf("Bye!\n");
    return 0;
}

