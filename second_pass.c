#include "second_pass.h"


/*
 * get name for file and run on file and to update data in code
*/

void second_pass(char *line) {
        extern int IC;
        flag isregrister = off;/* flag for is regrister is first oprand*/
        flag iscomma = off;
        char *ptr;
        
        /*if line is NULL*/
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

        /* if first  word is  extern*/
        if (strcmp(ptr, ".extern") == 0)
                return;
        /* if first  word is  entry*/
        if (strcmp(ptr, ".entry") == 0) {
                delete_spaces(&ptr);

                ptr = strtok(NULL, ", \t");

                /*if label is exist in label*/
                if (search_label(ptr) == 0) {

                        print_error(line_num,
                                    "The label is not saved in the system",
                                    ptr);
                        return;
                } else {

                        /* change context entry*/
                        insert_entry(ptr);/**/
                }
                return;
        }
        /*to jump over label*/
        if ((ptr[strlen(ptr) - 1]) == ':') {
                delete_spaces(&ptr);
                ptr = strtok(NULL, " \t");
            


                if ((strcmp(ptr, ".data") == 0) || (strcmp(ptr, ".string") == 0)
                    || (strcmp(ptr, ".extern") == 0))
                        return;
                /* if second  word is  entry*/
                if (strcmp(ptr, ".entry") == 0) {

                        delete_spaces(&line);
                        ptr = strtok(NULL, ", \t");

                        /*if label is exist in label*/

                        if (!search_label(ptr)) {
                                print_error(line_num, "The label is not saved in the system",
                                            ptr);


                        } else {
                                /* change context entry*/
                                insert_entry(ptr);
                        }
                        delete_spaces(&ptr);


                        ptr = strtok(NULL, " \t");
                        if (ptr != NULL)
                                print_error(line_num,
                                            "There are words after the label .entry definition",
                                            ptr);

                }
                /* if second  word is  opcomand*/
                if (if_command_return_i(ptr) != -1) {
                        IC++;


                        delete_spaces(&ptr);
                        ptr = strtok(NULL, ", \t");
                        if (ptr == NULL) {
 		
                                return;
                        }
if(ptr[strlen(ptr) - 1] == ',')
			 ptr[strlen(ptr) - 1] = '\0';
		

                        /* if first operand is register*/
                        if (getAdress(ptr, 0) == -5) {

                                isregrister = on;
                                IC++;
                        }
                                /* if first operand is number*/

                        else if (getAdress(ptr, 0) == -1) {
                                IC++;
                        }
                                /* if first operand is label */
                        else
                                oparand_label(ptr);


                        /* second operand */
                        delete_spaces(&ptr);
                        ptr = strtok(NULL, " \t");
                        if (ptr == NULL)
                                return;
			 if (ptr[strlen(ptr) - 1] == ',') {
                                if (ptr[0] == ',') {

                                        ptr = strtok(NULL, ", \t");
                                     if (ptr == NULL)
                                return;
                                iscomma = on;
}
                        }

                        if (ptr[0] == ',') {
                                if (iscomma == on)
                                        print_error(line_num,
                                                    " there is a problem with the comma ", ptr);
                                ptr = ptr + 1;


                        }


                        /* if second operand is register */
                        if (getAdress(ptr, 0) == -5) {
                                if (!isregrister)
                                        IC++;
                        }
                                /* if second operand is number */
                        else if (getAdress(ptr, 0) == -1)
                                IC++;

                        else
                                oparand_label(ptr);
                }


                iscomma = off;
                isregrister = off;

                return;
        }




        /* if first word is  command*/

        if (if_command_return_i(ptr) != -1) {
                IC++;

                ptr = strtok(NULL, ", \t");

                if (ptr == NULL)
                        return;
               if(ptr[strlen(ptr) - 1] == ',')
			 ptr[strlen(ptr) - 1] = '\0';


                /* if first operand is register */
                if (getAdress(ptr, 0) == -5) {
                        isregrister = on;
                        IC++;
                }
                        /* if first operand is number */
                else if (getAdress(ptr, 0) == -1) {

                        IC++;
                        /* if first operand is label */
                } else
                        oparand_label(ptr);

                /*second operand  */
                delete_spaces(&ptr);
                ptr = strtok(NULL, " \t");

                if (ptr == NULL) {
                        return;
                }
		 if (ptr[strlen(ptr) - 1] == ',') {
                        if (ptr[0] == ',') {
                                ptr = strtok(NULL, ", \t");
                 if (ptr == NULL)
                                return;
                        iscomma = on;
}
                }
                if (ptr[0] == ',') {
                        print_error(line_num,
                                    " there is a problem with the comma ", ptr);
                        ptr = ptr + 1;


                }



                /* if second operand is register */
                if (getAdress(ptr, 0) == -5) {
                        if (!isregrister)
                                IC++;
                }
                        /* if second operand is number */
                else if (getAdress(ptr, 0) == -1)
                        IC++;
                        /* if second operand is label */
                else
                        oparand_label(ptr);

                isregrister = off;
                iscomma = off;

        }

}
/* get oparand and cheak if oparand is label / else return erorr*/
void oparand_label(char *ptr) {
        extern int IC;
        if (search_label(ptr) != 0) {


                found = get_label(ptr);

                        /*if label is */
                if (found.context == 0 || found.context == 1) {
                        insert_lebal_code(2, found.value);
                        IC++;


                        /*insert code in list*/

                }
                if (found.context == 3) {
                        insert_lebal_code(2, found.value);
                        IC++;

                }
                /*if the extern label */
                if (found.context == 2) {

                        /*insert code in list*/
                       /* insert extern label in code*/
                        insert_lebal_code(1, 0);
                        /* insert extern label*/
                        insert_label(ptr, IC, 2);
                        IC++;
                }

        } else
                /*if is oparnd dosnt rigrester or number or label */
                print_error(line_num,
                            "Does not recognize the operand or there is a problem with the comma ", ptr);

}




