#include "first_pass.h"
#include "main.h"
#include <stdio.h>
#include <string.h>


void first_pass(char *line) {

        extern int IC, DC;
        extern flag isentry, isextern;
        char *ptr;
        char *label_name = NULL;
        flag islabel = off;
        int Result = 0, Result2, NumAct = -1;
        char *inst_name;
        char *new_line = (char *) malloc(strlen(line) + 1); /* Memory allowance according to string length*/
        if (new_line == NULL) {
                print_error(line_num, "Memory allocation failed", label_name);
                return;
        }
        strcpy(new_line, line); /* Copy the contents of line into new_line*/
        /* is line empty or only whitespaces */
        if (strspn(line, " \r\n\t") == strlen(line))
                return;

        /* cut and analyze first token */
        ptr = line;
        /* If it's an instruction line*/
        if (ptr[0] == ';')
                return;
        delete_spaces(&ptr);
        /*first word*/
        ptr = strtok(line, " \t");
        /* is comment phrase */
        if (ptr[0] == ';')
                return;
        else if (strcmp(ptr, ".entry") == 0) {

                isentry = 1;
                return;
        } else if (strcmp(ptr, ".extern") == 0) {
                isextern = 1;
                delete_spaces(&ptr);
                ptr = strtok(NULL, " \t");
                if (ptr == NULL) {
                        print_error(line_num, "An empty line instead of a label", label_name);
                        return;
                }
		if_label_correct(ptr,FALSE);
                insert_label(ptr, 0, 2);
                return;
        }
        /*If the first field is an lebal*/
        if ((ptr[strlen(ptr) - 1]) == ':') {
                /* remove ':' */
                ptr[strlen(ptr) - 1] = '\0';
                /* check if label is proper */
                     islabel = on;
        }
        /* if first token is label, continue and cut next token */
        if (islabel) {
                label_name = ptr;
                delete_spaces(&ptr);
                ptr = strtok(NULL, " \t");
                delete_spaces(&ptr);
                if (ptr == NULL) {
                        print_error(line_num, "empty line after label", label_name);
                        return;
                }

                /* instruction save data .data .string*/
                if (ptr[0] == '.') {

                        inst_name = ptr;


                        /*to המילה הבאה .entry */
                        if (strcmp(ptr, ".data") == 0) {
                                /*insert dats#*/
				if_label_correct( label_name,FALSE);
                                insert_label(label_name, DC + IC, 1);
                                ptr = strtok(NULL, "\0");
                                if (ptr == NULL) {
                                        print_error(line_num, "blank line after .data", label_name);
                                        return;
                                }

                                delete_spaces(&ptr);
                                data_code(ptr);
				/***/return;
                        }

                       if (strcmp(ptr, ".string") == 0) {
                                  /*insert dats#*/
                                if_label_correct( label_name,FALSE);
                                insert_label(label_name, DC + IC, 1);
			
                              ptr = strtok(NULL, "\"");

                                if (ptr == NULL) {
                                        print_error(line_num, "blank line after .string", label_name);
                                        return;
                                }
				if(isValidString(ptr)){
					print_error(line_num, "blank line after .string", label_name); 
				}
                                Result2 = string_code(ptr);

                        }
                        if (Result2 == -1) {
                                print_error(line_num, "string contains non-printable chararcter", inst_name);
                                return;

                        }

                } else
			if_label_correct( label_name,FALSE);
                        insert_label(label_name, IC + DC, 0);


                /*Note that I added this:*/

        }

        NumAct = if_command_return_i(ptr);
        if (if_command_return_i(ptr) == -1)
                return;

        delete_spaces(&ptr);
        ptr = strtok(NULL, " \t");
        if (ptr != NULL)
                delete_spaces(&ptr);

        if (ptr == NULL) {
                if (NumAct >= 14) {
                        insert_opcod(00, 0, NumAct, 0, IC);
                        IC++;
                        ptr = strtok(NULL, " \t");
                        if (ptr != NULL)
                                print_error(line_num,
                                            "Syntax error, unexpected text after operation name, operation not without operands",
                                            ptr);
                } else
                        print_error(line_num,
                                    "Syntax error, unexpected text after operation name, operation not without operands",
                                    ptr);
                return;
        }
        if (NumAct <= 3 || NumAct == 6) {
                /*Operations with 2 operands*/
                if (!hasCommaBetweenWords(strstr(new_line, ptr))) {
                        print_error(line_num, "Syntax error, no comma", ptr);
                        return;
                }
        } else if (NumAct > 3 && NumAct <= 13 && NumAct != 6) {/*No source operand*/
                if (hasCommaBetweenWords(strstr(new_line, ptr))) {
                        print_error(line_num, "Syntax error, no comma", ptr);
                        return;
                }
        }
        Result = countActionList(NumAct, strstr(new_line, ptr));

        if (Result < 1) {
                print_error(line_num, "unrecognized input. not valid label/instruction/command", ptr);
                return;
        }
        free(new_line);
	if((IC+DC)>1024)
		  print_error(line_num, "erorr memory", ptr);

	
}


