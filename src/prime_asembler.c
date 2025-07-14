#include "prime_asembler.h"
#include "main.h"

struct mcro first;
/*  first node */
mcro_ptr ptr_node = &first;
/*  last node */
mcro_ptr last_node = &first;
/*  findd_node */
mcro_ptr find_node = &first;


/*   get name file and retrum  end File extension .am
    delete mcro and nmae mcro and endmcro . and open mcros
	return new file name
   */
void prime_asembler(char *file) {


        char temp_copy[MAX_LINE];
        char *ptr;
        char temp[MAX_LINE];
        char *filename;/*name of the file sourch*/
        char *filename_new; /*name of the file traget*/
        char *check;

        FILE *fd;
        FILE *fd_new;

        iserror = FALSE;


        filename = (char *) malloc((strlen(file) + 5));
        if (filename == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }

        filename_new = (char *) malloc((strlen(file) + 5));
        if (filename_new == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        /* flag for mcro*/
        flag_mcro = off;


        /* check file name */
        strcpy(filename, file);
        check = strrchr(filename, '.');

        if (check != NULL) {
                printf("Error: wrong file name . <%s>", filename);
                return;
        }

        /* connect filename and .as */
        strcat(filename, ".as");

        /* open file */

        fd = fopen(filename, "r");
        if (!fd) {
                printf("Error: can't open file");
                return;
        }

        /* connect filename and  and .am */
        strcpy(filename_new, file);
        strcat(filename_new, ".am");

        /* open new file */

        fd_new = fopen(filename_new, "w");
        if (!fd_new) {
                printf("Error: can't open file");
                return;
        }
        /*  run file and print new file*/
        line_num = LINE_NUM_START;
        while (fgets(temp, MAX_LINE - 1, fd)) {
                line_num++;
                /*check if he line exceeds 80 characters*/
                if (!strchr(temp, '\n')) {
                        print_error(line_num,
                                    "he line exceeds 80 characters", temp);
                        continue;
                }

                /* is line empty or only whitespaces */
                if (strspn(temp, " \r\n\t") == strlen(temp))
                        continue;

                /*create a space after the label*/
replaceColonsWithSpace(temp);
                if (strchr(temp, ':') == strchr(temp, '.') + 1) {

                        strncat(temp_copy, temp, (int) strchr(temp, ':'));
                        strcat(temp_copy, ":");
                        strcat(temp_copy, temp);
                        strcpy(temp, temp_copy);
                } else
                        strcpy(temp_copy, temp);
                ptr = strtok(temp, " \t\n");
                /* Turn off and on mcro flag and insert mcro name */
                if (strcmp(ptr, "endmcro") == 0) {
                        check = strtok(NULL, " \t");
                        if (check != NULL)
                                print_error(line_num,
                                            "dosn't empty line after endmcro", ptr);
                        flag_mcro = off;
                        continue;
                }
                /*check name mcro*/
                if (if_found_mcro(ptr)) {
                        /*print line in new file*/
                        fprintf(fd_new, "%s", find_node->str);
                        check = strtok(NULL, " \t");
                        if (check != NULL)
                                print_error(line_num, "dosn't empty line after mcro", ptr);
                        continue;
                }
                /*check if string  "mcro"*/
                if (strcmp(ptr, "mcro") == 0) {

                        ptr = strtok(NULL, " \t\n");
			
                        /*check if string  mcro coorect*/
                        if (if_correct_mcro(ptr) == 0)
                                print_error(line_num,
                                            "Error mcro the name of the mcro in the system", ptr);
                        check = strtok(NULL, " \t\n");
                        if (check != NULL)
                                print_error(line_num, "dosn't empty line after mcro", ptr);

                        /* insert mcro name to table */
                        insert_mcro(ptr);
                        /*turn on flag*/
                        flag_mcro = on;
                        continue;


                }

                /*to check flag mcro and insert line in mcro*/
                if (flag_mcro && strcmp(temp, "mcro") != 0) {
                        insert_line(temp_copy);
                        continue;
                }
                /*Checks whether it is not macro */
                if (!flag_mcro && strcmp(ptr, "mcro") != 0 && strcmp(temp, "endmcro") != 0) {
                        temp[strlen(ptr) - 1] = '\n';
                        /*print line in new file*/
                        fprintf(fd_new, "%s", temp_copy);

                }
        }
        /* close file and file_new*/
        fclose(fd_new);
        fclose(fd);
        /* if line in file eror delete file*/
        if (iserror) {

                if (remove(filename_new) == 0)
                        printf("\nfile delete\n");

                else
                        printf("\nError file delete\n");

        }

        free_mcro();
        free(filename);
        free(filename_new);
        return;
}

/*
get name mcro for make node mcro 
and save mcro in last_node 
*/
void insert_mcro(char *name) {
        char *copy_name;
        /* Assigns memory to string and copy name  */
        mcro_ptr new_mcro = (mcro_ptr) malloc(sizeof(struct mcro));
        if (new_mcro == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        copy_name = (char *) malloc((strlen(name) + 1));
        if (copy_name == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        strcpy(copy_name, name);
        /* insert mcro name in node*/
        new_mcro->name = copy_name;
        new_mcro->str = "";

        /* save new_nod =last_node */
        last_node->next = new_mcro;
        new_mcro->next = NULL;
        last_node = new_mcro;


}

/*
get string for mcro 
and to connect lines
*/

void insert_line(char *line) {
        char *string;
        /* Assigns memory to strings  */
        char *copy_line = (char *) malloc((strlen(line) + 1));
        if (copy_line == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        string = (char *) malloc((strlen(last_node->str) + strlen(line) + 1));
        if (string == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }

        strcpy(copy_line, line);
        /* insert line in node*/
        strcpy(string, last_node->str);
        strcat(string, copy_line);
        last_node->str = string;

}

/* search node mcro */
int if_found_mcro(char *name) {
        mcro_ptr ptr = ptr_node;
        ptr = ptr->next;
        /* run nods ans search name */
        while (ptr != NULL) {
                /* if name equals name in node*/
                if (strcmp(name, ptr->name) == 0) {
                        find_node = ptr;
                        return 1;
                }
                ptr = ptr->next;
        }

        return 0;
}

/* get name for mcro and check if name mcro correct
*and if name corrrect return 1  else return 0*/
int if_correct_mcro(char *name) {
        char *copy_name = (char *) malloc((strlen(name)));
        if (copy_name == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        strcpy(copy_name, name);
        if ((strcmp(copy_name, ".data") == 0)
            || (strcmp(copy_name, ".string") == 0)
            || (strcmp(copy_name, ".extern") == 0)
            || (strcmp(copy_name, ".entry") == 0)
            || (if_found_mcro(copy_name) == 1)
            || (if_command_return_i(copy_name) != -1)
            || (strcmp(copy_name, "@r0") == 0)
            || (strcmp(copy_name, "@r1") == 0)
            || (strcmp(copy_name, "@r2") == 0)
            || (strcmp(copy_name, "@r3") == 0)
            || (strcmp(copy_name, "@r4") == 0)
            || (strcmp(copy_name, "@r5") == 0)
            || (strcmp(copy_name, "@r6") == 0)
            || (strcmp(copy_name, "@r7") == 0)
            || copy_name[strlen(copy_name) - 1] == ':') {
                free(copy_name);
                return 0;
        }
        free(copy_name);

        return 1;

}

/* run node and free node*/
void free_mcro() {
        mcro_ptr temp, head = ptr_node;
        head = head->next;
        while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp->name);
                free(temp);
        }
        ptr_node->next = NULL;
        ptr_node = &first;
        last_node = &first;
        find_node = &first;
}

