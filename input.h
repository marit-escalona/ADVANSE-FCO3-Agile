
#ifndef _INPUT_H_
#define _INPUT_H_

#include "trl.h"

#define CMD_EXIT 0

#define CMD_SET_TRL_INFO 1
#define CMD_ADD_TRL_ENTRY 2
#define CMD_VIEW_TRL_ENTRIES 3

#define CMD_SAVE_TRL 4

int input_read();

void input_set_trl_info(TimeRecordingLog *trl);
void input_add_trl_entry(TimeRecordingLog *trl);

void input_get_time(Time *time);

#endif // _INPUT_H_

