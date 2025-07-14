#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

#include "global.h"
#include "prime_asembler.h"
#include <string.h>
#include "out.h"
#include "first_pass.h"
#include "second_pass.h"
#include "free.h"
#include "action.h"

#define SIZE 100

#define IC_START 100
#define DC_START 0

#define MAX_LINE 82
#define LINE_NUM_START 1

/* IC - code counter
 * DC - data counter
 * line_num - number for line */
int IC, DC, line_num, l, L;
/*I added L because that's what I called it,
if you used it I'd love for you to replace it*/
extern boolean next_line;
/*if have next line*/

boolean iserror;
flag isentry, isextern;


void data_process(char *);

#endif

