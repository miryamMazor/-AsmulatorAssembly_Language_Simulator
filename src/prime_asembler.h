#ifndef PROJECT_PRIME_ASEMBLER_H
#define PROJECT_PRIME_ASEMBLER_H

#include <stdio.h>
#include "global.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "commands_tabels.h"
#include "action.h"


extern boolean iserror;
int line_num;

flag flag_mcro;
typedef struct mcro *mcro_ptr;
struct mcro {
    char *name;
    char *str;
    mcro_ptr next;
};

/*Gets the name of a file and lays out the macro in it*/
void prime_asembler(char *);

/*insert  node mcro in label for mcro*/
void insert_mcro(char *);

/*insert  text in mcro node*/
void insert_line(char *);

/*found mcro in label*/
int if_found_mcro(char *);

/*check if name for mcro is correct*/
int if_correct_mcro(char *);

/*free label mcro*/
void free_mcro();

#endif


