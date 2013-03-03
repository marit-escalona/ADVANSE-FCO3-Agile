#include <stdio.h>

#include "input.h"

int input_read()
{
    int input;

    printf("What would you like to do?\n");

    printf("[%d] Set TRL Information\t", CMD_SET_TRL_INFO);
    printf("[%d] Add TRL Entry\t", CMD_ADD_TRL_ENTRY);
    printf("[%d] View TRL", CMD_VIEW_TRL_ENTRIES);

    printf("\n");
    printf("[%d] Save TRL", CMD_SAVE_TRL);

    printf("\n[%d] Exit\n", CMD_EXIT);

    printf("> ");
    scanf("%d", &input);

    // Make sessions more readable
    printf("\n");

    return input;
}

void input_set_trl_info(TimeRecordingLog *trl)
{
    printf("Program number> ");
    scanf("%d", &(trl->programNumber));
    printf("Username> ");
    scanf("%s", trl->userName);
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

void input_get_time(Time *time)
{
    printf("Hour> ");
    scanf("%d", &time->hour);

    printf("Minute> ");
    scanf("%d", &time->minute);
}

