#include <stdio.h>
#include <stdlib.h>

#include "trl.h"
#include "input.h"

int main(int argc, char **argv)
{
    int cmdCode;

    TimeRecordingLog *trl;
    TRLEntry *trlEntry;

    trl = trl_new();

    do {
        cmdCode = input_read();

        switch (cmdCode) {
        case CMD_SET_TRL_INFO:
            input_set_trl_info(trl);
            trl_print(trl);
            break;
        case CMD_ADD_TRL_ENTRY:
            break;
        case CMD_VIEW_TRL_ENTRIES:
            break;
        case CMD_SAVE_TRL:
            break;
        case CMD_EXIT:
            break;
        default:
            printf("Unknown command code\n");
            break;
        }
    } while (cmdCode != CMD_EXIT);

    printf("Bye!\n");
    free(trl);
    return 0;
}

