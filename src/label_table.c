#include "label_table.h"
#include "commands_tabels.h"
#include "first_pass.h"
#include "main.h"

extern boolean iserror;

/*list for label*/
struct label first; /*dummy node*/
/*  first node */
label_ptr ptr_nodeLable = &first;
/*  last node */
label_ptr last_nodeLable = &first;

/*
 * get name - name for label
 * get value Ic/Dc
 * get context ,0-4 type for context
 */
void insert_label(char *name, int value, int context) {
        extern flag isextern;
        char *copy_name;
        label_ptr new_label = (label_ptr) malloc(sizeof(struct label));
        if (new_label == NULL) {
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
        if (context == 2)
                isextern = on;
/*save label in new label*/
        strcpy(copy_name, name);
        new_label->name = copy_name;
        new_label->value = value;
        new_label->context = context;
/*joining new label in list*/
        last_nodeLable->next = new_label;
        new_label->next = NULL;
        last_nodeLable = new_label;
}

/*get name for label and rturn 1id lacel exsit else return 0*/
int search_label(char *name) {
        label_ptr ptr = ptr_nodeLable;
        ptr = ptr->next;
        while (ptr != NULL) {
                if (strcmp(name, ptr->name) == 0)
                        return 1;
                ptr = ptr->next;
        }

        return 0;
}
/*get name for label and rturn 1id lacel exsit else return 0*/
int search_label_i(char *name) {
        int i = 0;
        label_ptr ptr = ptr_nodeLable;
        ptr = ptr->next;
        while (ptr != NULL) {
                if (strcmp(name, ptr->name) == 0)
                        return i;
                ptr = ptr->next;
                i++;
        }

        return 0;
}

/*
 * get name and check if name for label coreect
*/
int if_label_correct(char *ptr, boolean ext) {
        extern int line_num;
        int i;
        /* is there only letters and numbers */
        for (i = 0; i < strlen(ptr) - 1; i++) {
                /*if check if thl number or letter*/
                if (!isalnum(ptr[i])) {
                        print_error(line_num, "invalid label name. only chars and numbers allowed", ptr);
                        return 0;
                }
        }
        /* is short than 31 chars */
        if (strlen(ptr) > 31) {
                print_error(line_num, "label name cannot be longer than 32 	chars", ptr);
                return 0;
        }

        /* is first char a letter */
        if (!isalpha(ptr[0])) {
                print_error(line_num, "invalid label name. first char has to be a letter", ptr);
                return 0;
        }

        /*if name for label dasn't name is ave in system*/
        if (if_command_return_i(ptr) != -1 || search_label_i(ptr) != 0 ||
            (strcmp(ptr, "entry") == 0) || (strcmp(ptr, "extern") == 0)) {
                print_error(line_num, "label name cannot be command or instruction name", ptr);
                return 0;
        }
        /*if label is exist*/
        if (search_label(ptr)) {
                print_error(line_num, "label name is  exist", ptr);
                return 0;
        }
        return 1;
}

/*
 * get name for label and change for entry
 */
int insert_entry(char *name) {

        label_ptr p = ptr_nodeLable;
        while (p != NULL) {
                if (p->name != NULL)
                        if (strcmp(name, p->name) == 0) {
                                p->context = 3;

                                return 1;
                        }
                p = p->next;
        }
        return 0;
}




struct label get_label(char *name) {
        struct label getLabel;
        struct label empty_label = {NULL, 0, 0};/*cheak*/
        label_ptr ptr = ptr_nodeLable->next;
        while (ptr != NULL) {
                if (strcmp(name, ptr->name) == 0) {
                        getLabel.name = ptr->name;
                        getLabel.value = ptr->value;

                        getLabel.context = ptr->context;

                        return getLabel;
                }
                ptr = ptr->next;
        }


        return empty_label;
}

void free_label() {
        label_ptr temp, head = ptr_nodeLable;
        head = head->next;
        while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp->name);
                free(temp);
        }
        ptr_nodeLable->next = NULL; /* isolate first node */
        last_nodeLable = &first; /* re-initialize last node */
}


