#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trl.h"

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

