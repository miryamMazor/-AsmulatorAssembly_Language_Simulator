#include "isData.h"
#include <stdio.h>
#include <math.h>

extern boolean iserror;


int jumpSpace(char *command, int from) {
/*Input:command-pointer to arry,from-and starting poin.
Output: point after starting text.*/
        char c;
        while ((c = command[(from)]) != '\0' && isspace(c))/**/
                from++;
        return from;
}/*jumpSpace*/

int isTextLeft(char *command, int from) {
/*Input: pointer to arry, and starting poin. 
Output:If there is room left for the text?
returns 1 if all worked well,1 otherwise*/
        from = jumpSpace(command, from);
        return (command[from] != '\0') ? 1 : 0;
}/*isTextLeft*/


int end_of_text(char *ptr, int index) {
        char c;
        while ((c = ptr[(index)]) != '\0' && !isspace(c) && (c != ',')) {
                index++;
        }
        return index;
}

int hasCommaBetweenWords(char *ptr) {
        int len = strlen(ptr);
        int i, commaIndex = -1;

        for (i = 0; i < len; i++) {
                if (ptr[i] == ',') {
                        commaIndex = i;
                        break;
                }
        }

        if (commaIndex == -1) {
                return 0; /*No comma found between the words*/
        } else {
                return 1; /*A comma is found between the words*/
        }
}


