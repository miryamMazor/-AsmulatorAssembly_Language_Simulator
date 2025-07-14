#ifndef PROJECT_AsSymbol_H
#define PROJECT_AsSymbol_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AsSymbol.h"
#include "label_table.h"

typedef struct Extern *extern_ptr;

struct Extern {
    char *name;
    int context;
    extern_ptr next;
};

int IsSymbol(label_ptr *head_lable, char *ptr);

void insert_extern(char *name, int context);

int search_extern(char *name);

void freeAsSymbol();

#endif
