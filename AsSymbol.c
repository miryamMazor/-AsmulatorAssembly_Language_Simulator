#include "AsSymbol.h"

extern boolean iserror;

struct Extern first; /*dummy node*/
/* initialize first node */
extern_ptr ptr_node_extern = &first;
/* initialize last node */
extern_ptr last_nodeSymbol = &first;


int IsSymbol(label_ptr *head_lable, char *ptr) {
        int end = 0;
        insert_label(ptr, 0, 2);
        ptr = strtok(NULL, " \t");
        end = strlen(ptr);
        if (end != -1) {
                return 0;
        }
        return 1;
}

void insert_extern(char *name, int context) {
        char *copy_name;
        extern_ptr new_extern = (extern_ptr) malloc(sizeof(struct Extern));
        if (new_extern == NULL) {
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
        new_extern->name = copy_name;
        new_extern->context = context;
        last_nodeSymbol->next = new_extern;
        new_extern->next = NULL;
        last_nodeSymbol = new_extern;
}

int search_extern(char *name) {
        extern_ptr ptr = ptr_node_extern;
        ptr = ptr->next;
        while (ptr != NULL) {
                if (strcmp(name, ptr->name) == 0)
                        return 1;
                ptr = ptr->next;
        }
        return 0;
}

void freeAsSymbol() {
        extern_ptr temp, head = ptr_node_extern;
        head = head->next;
        while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp->name);
                free(temp);
        }
        ptr_node_extern->next = NULL; /* isolate first node */
        last_nodeSymbol = &first; /* re-initialize last node */
}
