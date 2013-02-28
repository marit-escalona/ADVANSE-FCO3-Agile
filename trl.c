#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trl.h"

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

    printf("Program number %d, written by %s\n", trl->programNumber, trl->userName);
    printf("%d TRL entries\n", trl->numEntries);

    for (i = 0; i < trl->numEntries; i++) {
        trlEntry = trl->entries[i];
        printf("%02d:%02d - %02d:%02d\n",
                trlEntry.startTime.hour, trlEntry.startTime.minute,
                trlEntry.endTime.hour, trlEntry.endTime.minute);
    }
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

