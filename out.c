#include "out.h"

extern int IC, DC;

/*oid file_label(char *file) {
        char *filename;
        label_ptr p;
        FILE *fd;

        filename = (char *) malloc((strlen(file) + 5));
        if (filename == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        strcpy(filename, file);
        strcat(filename, "_label.ob");
        fd = fopen(filename, "w");



        p = ptr_nodeLable;
        p = p->next;
        while (p != NULL) {


                fprintf(fd, "name=%s \t value=%d,\tcontext=%d\n", p->name, p->value, p->context);
                fprintf(fd, "\n");

                p = p->next;
        }
        fclose(fd);
}
*/
/*
the funnc gert name for file and return new file.ob 
and write assembler bsis 64
*/

void file_data(char *file) {
        extern data_ptr data_image_first;
	/*pointer for string*/
        int pointer;
	/*string for save binary string*/
        char str_binary[12];
        int bit_save, i;
        char character;
        code_ptr p_IC;
        data_ptr p_DC;
        char *filename;
        char save_64[2];
        /*data_ptr p;*/
        FILE *fd;


        filename = (char *) malloc((strlen(file) + 5));
        if (filename == NULL) {
                printf("Memory not allocated.\n");
                exit(0);
        }
        strcpy(filename, file);
        strcat(filename, ".ob");
        fd = fopen(filename, "w");/* Open the file for writing */

        if (fd == NULL) {
                printf("ERROR");
                exit(0);
        }
        selection_sort_by_address();/* Sort the data by address */
        p_IC = code_IC;

        p_IC = p_IC->next;
        fprintf(fd, "%d %d\n", IC - 100, DC);/* Write IC and DC to the file */

/*get byte for string binary and make string*/
        while (p_IC != NULL) {
                pointer = 0;
                for (i = 11; i >= 0; i--) {
                        bit_save = (p_IC->u.output.out >> i) & 1;
                        character = bit_save + '0';

                        str_binary[pointer] = character;

                        pointer++;
                }


                binary_to_base64(str_binary, save_64);

                fprintf(fd, "%s\n", save_64);


                p_IC = p_IC->next;
        }
/* write for data */
        p_DC = data_image_first;

        p_DC = p_DC->next;
/*get byte for string binary and make string*/
        while (p_DC != NULL) {
                pointer = 0;
		
		
                for (i = 11; i >= 0; i--) {
                        bit_save = (p_DC->u.output.out >> i) & 1;
                        character = bit_save + '0';

                        str_binary[pointer] = character;

                        pointer++;
                }



                binary_to_base64(str_binary, save_64);/* Convert binary to base64 */
                fprintf(fd, "%s\n", save_64);/* Write the base64 representation to the file */




                p_DC = p_DC->next;
        }

        fclose(fd);
        free(filename);
}
/*the functiom get name file and  following function generates an output file containing information about external labels. */
void file_extern(char *file) {
        char *filename;
        label_ptr p;
        FILE *fd;

        filename = (char *) malloc((strlen(file) + 5));
        if (filename == NULL) {
                printf("Memory not allocated.\n");
                exit(0);
        }
        strcpy(filename, file);
        strcat(filename, ".ext");
        fd = fopen(filename, "w");
        if (fd == NULL) {
                printf("ERROR");
                exit(0);
        }

        p = ptr_nodeLable;
        p = p->next;
        while (p != NULL) {
                if (p->context == 2 && p->value != 0) {
                        fprintf(fd, "%s\t%d\n", p->name, p->value);
                }
                p = p->next;
        }
        fclose(fd);
        free(filename);
}
/*the functiom get name file and  following function generates an output file containing information about entry labels. */

void file_ent(char *file) {
        char *filename;
        label_ptr p;
        FILE *fd;
        filename = (char *) malloc((strlen(file) + 5));
        if (filename == NULL) {
                printf("Memory not allocated.\n");
                exit(0);
        }
        strcpy(filename, file);
        strcat(filename, ".ent");
        fd = fopen(filename, "w");

        p = ptr_nodeLable;
        p = p->next;
        while (p != NULL) {

                if (p->context == 3)
                        fprintf(fd, "%s \t %d/n", p->name, p->value);
                p = p->next;
        }
        fclose(fd);/* Close the file  ent*/
        free(filename);  /* Free the allocated memory for the filename */
}
/*
this funct get binary string and string for ave basis 64 and swap string binary for string save_64 basis 64
*/

void binary_to_base64(const char *binary, char *save_64) {
/*sace sing for base 64*/
        const char base_64c_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


        const int bits_per_group = 6;/*sum binary char for make char char in base 64*/ 

        int binary_len = strlen(binary);/*len binary =12*/
        /*int base_64_len = (binary_len * 8 + bits_per_group - 1) / bits_per_group;*/

        int i, j, k;
        for (i = 0, j = 0; i < binary_len; i += bits_per_group) {
                int bits = 0;
                for (k = 0; k < bits_per_group; k++) {
                        bits <<= 1;
                        if (i + k < binary_len) {
                                bits |= (binary[i + k] - '0');
                        }
                }
                save_64[j++] = base_64c_chars[bits];
        }

/* save string for base 64*/
        save_64[j] = '\0';
}





