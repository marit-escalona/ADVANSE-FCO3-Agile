
#ifndef _TRL_H_
#define _TRL_H_

#define PHASE_PLANNING 1
#define PHASE_DESIGN 2
#define PHASE_CODING 3
#define PHASE_COMPILE 4
#define PHASE_DEBUG 5
#define PHASE_TEST 6
#define PHASE_POSTMORTEM 7

const char *get_phase_name_string(int phaseID);

struct Time {
    int hour;
    int minute;
};

struct TRLEntry {
    int phaseID;
    struct Time startTime;
    struct Time endTime;
};

struct TimeRecordingLog {
    int programNumber;
    char userName[255];
    struct TRLEntry entries[100];   // Should be a linked list in final program
    int numEntries; // Only necessary while we're using an array
};

// Typedefs for convenience
typedef struct Time Time;
typedef struct TRLEntry TRLEntry;
typedef struct TimeRecordingLog TimeRecordingLog;

TimeRecordingLog *trl_new();
void trl_set_user_name(TimeRecordingLog *trl, char *userName);
void trl_add_entry(TimeRecordingLog *trl, TRLEntry *trlEntry);
void trl_print(TimeRecordingLog *trl);


TRLEntry *trl_entry_new();
void trl_entry_set_start(TRLEntry *trlEntry, int hour, int minute);
void trl_entry_set_end(TRLEntry *trlEntry, int hour, int minute);

#endif // _TRL_H_

