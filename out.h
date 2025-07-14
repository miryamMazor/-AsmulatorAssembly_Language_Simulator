#ifndef PROJECT_OUT_H
#define PROJECT_OUT_H

#include "label_table.h"
#include "data_image.h"
#include "code_image.h"
#include "AsSymbol.h"
#include "global.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>






extern label_ptr ptr_nodeLable;
extern extern_ptr ptr_node_extern;
extern code_ptr code_IC;


/*extern data_ptr data_image_first;*/

/*void file_label(char *);*/


void file_data(char *);
/*
the funnc gert name for file and return new file.ob 
and write assembler bsis 64
*/
void file_extern(char *);
/*the functiom get name file and  following function generates an output file containing information about external labels. */
void file_ent(char *file);
/*the functiom get name file and  following function generates an output file containing information about entry labels. */
void binary_to_base64(const char *binary, char *save);
/*
this funct get binary string and string for ave basis 64 and swap string binary for string save_64 basis 64
*/

#endif

