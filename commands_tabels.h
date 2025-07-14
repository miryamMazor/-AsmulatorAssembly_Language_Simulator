#ifndef PROJECT_COMMANDS_TABELS_H
#define PROJECT_COMMANDS_TABELS_H

#include <string.h>


#define TABLE_LINE 16


struct commands {
    char *command_name;
    int opcode;
};


/*get name for opcode and return namber for opcode*/
int if_command_return_i(char *name);

#endif
