
#include "global.h"

extern boolean iserror;

/*  get line and massge for print and word erorr
*print eror and turn on flag iserorr  */
void print_error(int line_numb, char *message, char *name) {

        printf("Error: Line %d: %s <%s>\n", line_numb, message, name);
        iserror = TRUE;
}

/* remove whitespaces from string beginning and ending */

void delete_spaces(char **str) {
        size_t len;

        while (isspace((*str)[0])) {

                (*str)++;
        }
        len = strlen(*str);
        while (len > 0 && isspace((*str)[len - 1])) {
                (*str)[len - 1] = '\0';
                len--;
        }
}

