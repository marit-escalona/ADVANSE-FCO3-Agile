
#ifndef _INPUT_H_
#define _INPUT_H_

#include "trl.h"
#include "user.h"

#define CMD_EXIT 0

// Program menu commands
#define CMD_CREATE_PROGRAM 1
#define CMD_EDIT_PROGRAM 2
#define CMD_LIST_PROGRAMS 3

// Program editing commands

#define CMD_ADD_TRL_ENTRY 1
#define CMD_VIEW_TRL_ENTRIES 2

#define CMD_SAVE_TRL 3

int input_projmenu_read();
int input_projedit_read();

User *input_create_user();
void input_create_program_for_user(User *user);

void input_add_trl_entry(TimeRecordingLog *trl);

void input_get_time(Time *time);

#endif // _INPUT_H_

