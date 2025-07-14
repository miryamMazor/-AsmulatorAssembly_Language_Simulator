#include "main.h"


int main(int argc, char *argv[]) {
        int i;
        for (i = 1; i < argc; i++) {
                data_process(argv[i]);
        }
        return 0;
}

/*get name for file and make process asambler*/
void data_process(char *file) {


        /*help to get line*/
        char temp[MAX_LINE];
        FILE *fd;
        /*vartible for name file ncro*/
        char *filename = (char *) malloc((strlen(file) + 5));
        if (filename == NULL) {
                printf("Memory not allocated.\n");
                iserror = TRUE;
                exit(0);
        }
        /* Interprets the macro*/
        prime_asembler(file);
 

        /*make name file for prime_asembler */
        strcpy(filename, file);
        strcat(filename, ".am");
        fd = fopen(filename, "r");
        if (!fd) {
                printf("Error: can't open file");
                return;
        }
        /*first pass*/

        IC = IC_START;/*reset Ic*/
        DC = DC_START;/* reset DC*/

        line_num = LINE_NUM_START; /*reset line num*/

        while (fgets(temp, MAX_LINE, fd)) {
               
                temp[strlen(temp) - 1] = '\0';
                first_pass(temp);
                line_num++;


        }
        fclose(fd);


        /*if iserror equals on jump to next file*/
       /* if (iserror == 1)
                return;*/
        {

                fd = fopen(filename, "r");
                if (!fd) {
                        printf("Error: can't open file");
                        return;
                }

                /*second pass*/


                IC = IC_START;

                line_num = LINE_NUM_START;
                while (fgets(temp, MAX_LINE, fd)) {

                        temp[strlen(temp) - 1] = '\0';
                        second_pass(temp);
                        line_num++;

                }
                fclose(fd);
        }

        /*if iserror equals on jump to next file*/
        if (iserror == 1)
                return;

        /*if isentry turned on print file for label entry*/

        if (isentry == 1)
                file_ent(file);
        /*if isextern turned on print file for label extern*/
        if (isextern == 1)
                file_extern(file);
        /*print commands in base 64*/
        file_data(file);
       /* file_label(file);*/

        /*free tabel*/
        freeALL();

}



