#ifndef PROJECT_GLOBAL_H
#define PROJECT_GLOBAL_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    FALSE = 0, TRUE = 1
} boolean;
typedef enum {
    off = 0, on = 1
} flag;


typedef enum {
    code = 0, data = 1, external = 2, ENTRY = 3
} attribute;

/*  get line and masage for print and word erorr
*print eror and turn on flag iserorr  */
void print_error(int, char *, char *);

/* remove whitespaces from string beginning and ending */
void delete_spaces(char **);

#endif

