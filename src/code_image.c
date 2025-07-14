#include "code_image.h"


extern int IC, DC;

/* List for the data counter*/
struct newCode start_IC;
code_ptr code_IC = &start_IC;/* first node*/
code_ptr last_IC = &start_IC;/* last node*/


/* insert binary for line to have opcode
 * get ARE -0/1/2 Pointer to the position
 * get rt 1, 3 ,5 - type for oparand
*get opcode number
*get rs 1, 3 ,5 - type for oparand
 * */
void insert_opcod(int are, int rt, int op, int rs, int ic) {
        code_ptr newNode = (code_ptr) malloc(sizeof(struct newCode));
        if (newNode == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        newNode->address = IC;/*insert for address line*/
        newNode->u.S.ARE = are;
        newNode->u.S.b = rs;
        newNode->u.S.c = op;
        newNode->u.S.d = rt;


        /*list concatenation*/
        last_IC->next = newNode;
        newNode->next = NULL;
        last_IC = newNode;
}

/* insert binary for line to have registers
* get ARE -0/1/2 Pointer to the position
* get rt 1, 3 ,5 - type for oparand
        *get opcode number
*get rs adress for oparnd
 * for label insert 0
* */
void insert_registers(int are, int rt, int rs) {
        code_ptr newNode = (code_ptr) malloc(sizeof(struct newCode));
        if (newNode == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        newNode->u.regirster.ARE = are;
        newNode->u.regirster.mis1 = rt;
        newNode->u.regirster.mis2 = rs;
        newNode->address = IC;/*insert for address line*/

        /*list concatenation*/
        last_IC->next = newNode;
        newNode->next = NULL;
        last_IC = newNode;
}

/* insert binary for line to have label
* get ARE -0/1/2 Pointer to the position
*get ic _label= adress  label
 * for label insert 0
* */
void insert_lebal_code(int are, int ic_label) {

        code_ptr newNode = (code_ptr) malloc(sizeof(struct newCode));
        if (newNode == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        newNode->u.lebal.ARE = are;
        newNode->u.lebal.mis1 = ic_label;
        newNode->address = IC;/*insert for address line*/

        /*list concatenation*/
        last_IC->next = newNode;
        newNode->next = NULL;
        last_IC = newNode;
}

void insert_number(int are, int num) {

        code_ptr newNode = (code_ptr) malloc(sizeof(struct newCode));
        if (newNode == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        newNode->address = IC;
        newNode->u.AddressFrom.mis = num;
        newNode->u.AddressFrom.ARE = are;

        /*list concatenation*/
        last_IC->next = newNode;
        newNode->next = NULL;
        last_IC = newNode;
}


void insert_node_between(code_ptr first, code_ptr new_node, code_ptr second) {
        new_node->next = second;
        first->next = new_node;
}


/*
 * Sorts a linked list of nodes based on their addresses in ascending order.

 */


void selection_sort_by_address() {
        code_ptr ptr = code_IC->next;

        while (ptr != NULL) {
                code_ptr min_node = ptr;
                code_ptr temp = ptr->next;


                while (temp != NULL) {
                        if (temp->address < min_node->address) {
                                min_node = temp;
                        }
                        temp = temp->next;
                }

                /* Swap the data and addresses of the current node and the minimum node*/
                if (min_node != ptr) {
                        int temp_address = ptr->address;
                        int temp_ARE = ptr->u.S.ARE;
                        int temp_b = ptr->u.S.b;
                        int temp_c = ptr->u.S.c;
                        int temp_d = ptr->u.S.d;

                        ptr->address = min_node->address;
                        ptr->u.S.ARE = min_node->u.S.ARE;
                        ptr->u.S.b = min_node->u.S.b;
                        ptr->u.S.c = min_node->u.S.c;
                        ptr->u.S.d = min_node->u.S.d;

                        min_node->address = temp_address;
                        min_node->u.S.ARE = temp_ARE;
                        min_node->u.S.b = temp_b;
                        min_node->u.S.c = temp_c;
                        min_node->u.S.d = temp_d;
                }

                ptr = ptr->next; /*Move to the next node in the list*/
        }
}

void free_code() {
        code_ptr temp, head = code_IC;
        head = head->next;
        while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
        }

        code_IC->next = NULL; /* isolate first node */
        last_IC = &start_IC; /* re-initialize last node */

}


     
