#ifndef PROJECT_SECOND_PASS_H
#define PROJECT_SECOND_PASS_H

#include <stdio.h>
#include "global.h"
#include "main.h"
#include "action.h"
#include "code_image.h"
#include "label_table.h"

struct label found;
extern label_ptr ptr_nodeLable;


void second_pass(char *);

void oparand_label(char *);

#endif

