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

