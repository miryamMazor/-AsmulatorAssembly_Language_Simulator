#ifndef PROJECT_ISDATA_H
#define PROJECT_ISDATA_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <string.h>
#include "global.h"

extern int line_num;

/*The function receives a pointer and an initial position
and skips over all spaces 
(and returns the initial position that is not a space)*/
int jumpSpace(char *command, int from);

/*Receives a pointer and a starting position,
and returns whether there is any additional text 
in the command (until the end of the command) 
returns 1 if there is and 0 if there is not*/
int isTextLeft(char *command, int from);


/*The function receives a string char* ptr ,
which represents two words that are inside the string. 
It goes through each character in the string 
and checks if there is a comma (,) between the characters.
If the comma is between the characters, 
the function returns no value,
assuming there is a comma between the words. Otherwise, 
it returns an error message,
assuming there is no comma between the words.*/
int hasCommaBetweenWords(char *ptr);


/*Gets a pointer and a starting position, and returns 
the end of the next text 
(position up to the next comma, comma, or space)*/
int end_of_text(char *ptr, int index);


#endif

