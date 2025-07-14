#include "data_image.h"

extern boolean iserror;
struct newData first_data; /*dummy node*/
data_ptr data_image_first = &first_data; /* initialize first node */
data_ptr last_data = &first_data; /* initialize last node */



void insertData(int num) {
extern int DC;
/*The number exceeds*/
  data_ptr dataNew = (data_ptr) malloc(sizeof(struct newData));
if(num<MINNUM||num>BIGNUM)
	 print_error(line_num, "The number exceeds", "num");

      
        if (dataNew == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        dataNew->address = DC;
        dataNew->name = ".data";
        dataNew->u.cod_data.codASCII = num;

        last_data->next = dataNew;
        dataNew->next = NULL;
        last_data = dataNew;
        DC++;
	
}




  
void data_code(char *ptr) {

        ptr = strtok(ptr, ",");
        while (ptr != NULL) {
                insertData(atoi(ptr));
                ptr = strtok(NULL, ",");
        }
}

void insertString(char c) {
        extern int DC;
        data_ptr dataNew = (data_ptr) malloc(sizeof(struct newData));
        if (dataNew == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        dataNew->address = DC;
        dataNew->name = ".string";
        dataNew->u.cod_String.codASCII = c;
        last_data->next = dataNew;
        dataNew->next = NULL;
        last_data = dataNew;
        DC++;
}

int string_code(char *ptr) {

        char *str = ptr;
        int i;
        for (i = 0; i < strlen(ptr) - 0; i++) {

		if (isprint(ptr[i]))
                insertString(str[i]);
        }


        insertString('\0');
        return 0;

}

int isNumber(char *ptr) {

        int start = 0, end = 0;

        if (ptr[start] == '-' || ptr[start] == '+')
                start++;
        while (ptr[start + end] != ',' && ptr[start + end] != '\0' && ptr[start + end] >= '0' &&
               ptr[start + end] <= '9') {
                end++;
        }

        if (end == 0)
                return 0;
        return end;
}

int commas_num(char *str) {
        int i, sum = 0, prev = FALSE;
        for (i = 0; i < strlen(str); i++) {
                if ((str[i]) == ',') {
                        if (prev)
                                return -1;
                        else {
                                prev = TRUE;
                                sum += 1;
                        }
                } else
                        prev = FALSE;
        }
        return sum;
}

int check_commas(char *ptr) {
        if (ptr[0] == ',' || ptr[strlen(ptr) - 1] == ',') {

                print_error(line_num, "Incorrect comma in data line", ptr);
                return 0;
        }
        if (commas_num(ptr) == -1) {
                print_error(line_num, "consecutive commas", ptr);
                return 0;
        }
        return 1;
}

void freeData() {
        data_ptr temp, head = data_image_first;
        head = head->next;
        while (head != NULL) {
                temp = head;
                head = head->next;
                free(temp);
        }
        data_image_first->next = NULL; /* isolate first node */
        data_image_first = &first_data; /* re-initialize last node */



}



