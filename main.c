#include <stdio.h>
#include "trl.h"

int main(int argc, char **argv)
{
    TimeRecordingLog *trl;
    TRLEntry *trlEntry;

    trl = trl_new();
    trl->programNumber = 1;
    trl_set_user_name(trl, "Patrick Calulo");

    trlEntry = trl_entry_new();
    trl_entry_set_start(trlEntry, 8, 0);
    trl_entry_set_end(trlEntry, 10, 0);

    trl_add_entry(trl, trlEntry);

    trl_print(trl);

    return 0;
}

