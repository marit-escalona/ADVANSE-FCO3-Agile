#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trl.h"

const char *get_phase_name_string(int phaseID)
{
    switch (phaseID) {
        case PHASE_PLANNING:
            return "Planning";
        case PHASE_DESIGN:
            return "Design";
        case PHASE_CODING:
            return "Coding";
        case PHASE_COMPILE:
            return "Compile";
        case PHASE_DEBUG:
            return "Debug";
        case PHASE_TEST:
            return "Test";
        case PHASE_POSTMORTEM:
            return "Postmortem";
        default:
            return "Unknown";
    }
}

// TimeRecordingLog functions

TimeRecordingLog *trl_new()
{
    TimeRecordingLog *trl;

    trl = malloc(sizeof(TimeRecordingLog));
    if (trl == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    return trl;
}

void trl_set_user_name(TimeRecordingLog *trl, char *userName)
{
    strcpy(trl->userName, userName);
}

void trl_add_entry(TimeRecordingLog *trl, TRLEntry *trlEntry)
{
    trl->entries[trl->numEntries++] = *trlEntry;
}

void trl_print(TimeRecordingLog *trl)
{
    int i;
    TRLEntry trlEntry;

    printf("\n========================================\n");
    printf("%d TRL entries\n", trl->numEntries);

    printf("TIME\t\tPHASE\n");
    for (i = 0; i < trl->numEntries; i++) {
        trlEntry = trl->entries[i];
        printf("%02d:%02d - %02d:%02d\t%s\n",
                trlEntry.startTime.hour, trlEntry.startTime.minute,
                trlEntry.endTime.hour, trlEntry.endTime.minute,
                get_phase_name_string(trlEntry.phaseID));
    }

    printf("========================================\n\n");
}

// TRLEntry functions

TRLEntry *trl_entry_new()
{
    TRLEntry *trlEntry;

    trlEntry = malloc(sizeof(TRLEntry));
    if (trlEntry == NULL) {
        printf("Out of memory!\n");
        exit(1);
    }

    return trlEntry;
}

void trl_entry_set_start(TRLEntry *trlEntry, int hour, int minute)
{
    trlEntry->startTime.hour = hour;
    trlEntry->startTime.minute = minute;
}

void trl_entry_set_end(TRLEntry *trlEntry, int hour, int minute)
{
    trlEntry->endTime.hour = hour;
    trlEntry->endTime.minute = minute;
}

