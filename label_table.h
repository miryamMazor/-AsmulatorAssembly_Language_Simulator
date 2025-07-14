#ifndef PROJECT_LABEL_TABLE_MY_H
#define PROJECT_LABEL_TABLE_MY_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"

typedef struct label *label_ptr;

struct label {
    char *name;
    int value;/*ic dc*/
    int context;/*data extern entry string*/

    label_ptr next;
};


void insert_label(char *, int, int);

/*
 *
 * get name - name for label
 * get value Ic/Dc
 * get context ,0-4 type for context
 */
int search_label(char *);

/*get name for label and rturn 0 id lacel exsit else return 0*/
int search_label_i(char *);

/*
 *get name for label and check if name label correct
 */
int if_label_correct(char *, boolean);

/*
 * get name and check if name for label coreect
 */
int insert_entry(char *);

/*
 * get name for label and change for entry
 */


 

struct label get_label(char *);

void free_label();

#endif
