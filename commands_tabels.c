#include "commands_tabels.h"

/*list for opcode ,name and number for name*/
struct commands command_table[] = {
        {"mov",  0,},
        {"cmp",  1},
        {"add",  2},
        {"sub",  3},
        {"not",  4},
        {"clr",  5},
        {"lea",  6},
        {"inc",  7},
        {"dec",  8},
        {"jmp",  9},
        {"bne",  10},
        {"red",  11},
        {"prn",  12},
        {"jsr",  13},
        {"rts",  14},
        {"stop", 15},
};

/*get name for opcode and return namber for opcode*/
int if_command_return_i(char *name) {

        {
                int i;
                for (i = 0; i < TABLE_LINE; i++) {
                        if (strcmp(name, command_table[i].command_name) == 0)
                                return i;
                }
                return -1;
        }

}

