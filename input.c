#include <stdio.h>
#include <mysql.h>

#include "input.h"

int input_projmenu_read()
{
    int input;


    printf("What would you like to do?\n");

    printf("[%d] Create Program\t", CMD_CREATE_PROGRAM);
    printf("[%d] Edit Program\t", CMD_EDIT_PROGRAM);
    printf("[%d] View Program List", CMD_LIST_PROGRAMS);

    printf("\n[%d] Save to Database\t[%d] Exit\n", CMD_SAVE, CMD_EXIT);

    printf("> ");
    scanf("%d", &input);
    printf("\n");

    return input;
}

int input_projedit_read()
{
    int input;

    printf("What would you like to do?\n");

    printf("[%d] Add TRL Entry\t", CMD_ADD_TRL_ENTRY);
    printf("[%d] View TRL", CMD_VIEW_TRL_ENTRIES);

    printf("\n[%d] Return to Projects Menu\n", CMD_EXIT);

    printf("> ");
    scanf("%d", &input);

    // Make sessions more readable
    printf("\n");

    return input;
}

User *input_create_user()
{
    User *user = user_new();
    printf("Name> ");

    fgets(user->name, USER_NAME_LENGTH, stdin);
    string_chomp(user->name);

    return user;
}

Program *input_create_program_for_user(User *user)
{
    Program *program = program_new();
    printf("Creating program for %s:\n", user->name);

    printf("Program number> ");
    scanf("%s", program->programNumber);

    user_add_program(user, program);
    return program;
}

void input_add_trl_entry(TimeRecordingLog *trl)
{
    TRLEntry *trlEntry = trl_entry_new();
    int phaseID = -1;

    while (phaseID < PHASE_PLANNING || phaseID > PHASE_POSTMORTEM) {
        printf("Phases:\n");
        printf("[%d] %s\t[%d] %s\t[%d] %s\n",
                PHASE_PLANNING, get_phase_name_string(PHASE_PLANNING),
                PHASE_DESIGN, get_phase_name_string(PHASE_DESIGN),
                PHASE_CODING, get_phase_name_string(PHASE_CODING));

        printf("[%d] %s\t[%d] %s\t[%d] %s\n",
                PHASE_COMPILE, get_phase_name_string(PHASE_COMPILE),
                PHASE_DEBUG, get_phase_name_string(PHASE_DEBUG),
                PHASE_TEST, get_phase_name_string(PHASE_TEST));

        printf("[%d] %s\n",
                PHASE_POSTMORTEM, get_phase_name_string(PHASE_POSTMORTEM));

        printf("Phase> ");
        scanf("%d", &phaseID);
    }

    trlEntry->phaseID = phaseID;

    printf("\nEnter start time:\n");
    input_get_time(&trlEntry->startTime);

    printf("\nEnter end time:\n");
    input_get_time(&trlEntry->endTime);

    trl_add_entry(trl, trlEntry);
    printf("\nAdded!\n");
}

void input_get_time(MYSQL_TIME *time)
{
    printf("Hour> ");
    scanf("%d", &time->hour);

    printf("Minute> ");
    scanf("%d", &time->minute);
}

