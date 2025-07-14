#ifndef PROJECT_ACTION_H
#define PROJECT_ACTION_H

#include "first_pass.h"
#include "AsSymbol.h"
#include "label_table.h"
#include "isData.h"
#include "main.h"
#include "code_image.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

extern int IC;

extern int line_num;

/*#define  MaxSymbol 30*/

/*Input: string and starting position
Returns the type of the operand
Output: -3 if the operand is a register
-2 error
-1 if it's a number
X>0 if it is a label*/
int getAdress(char *ptr, int index);

/*Convert a text number to a number assuming the resulting text is numeric*/
int textToNum(char *ptr);

/*The function receives an operation number 0-13 inclusive and points to a string that contains operands.
The function checks according to the rules if the operand corresponds 
to an operation number and adds it to the list.
The function returns the number of operands + the operation.*/
int countActionList(int actionNum, char *ptr);


/**
 * Counts the number of commas in a given string.
 *
 * This function iterates through the input string and counts the occurrences
 * of the comma character ','.
 *
 * @param ptr A pointer to the input string to be examined.
 * @return Returns the count of commas found in the input string.
 */
int countCommas(char* ptr);


/**
 * Replaces colons with spaces in a given string.
 *
 * This function iterates through the input string and replaces colons (":")
 * with a colon followed by a space, if there is no space already.
 *
 * @param ptr A pointer to the input string to be examined and modified.
 */
void replaceColonsWithSpace(char* ptr);

/**
 * Checks if a given string is a valid string.
 *
 * A valid string is a sequence of printable ASCII characters enclosed within
 * double quotation marks.
 *
 * @param ptr A pointer to the input string to be examined.
 * @return Returns `true` if the input string is a valid string, otherwise `false`.
 */
int isValidString(char* ptr);
#endif

