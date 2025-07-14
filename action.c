#include "action.h"

int getAdress(char* ptr, int index) {
	int i = 0;
	if (ptr[index] == '@' && ptr[index + 1] == 'r' && ptr[index + 2] >= '0' && ptr[index + 2] <= '7')
		return -5;/*proper registers 5*/

	if (isNumber(ptr) != 0)
		return -1;/*If the operand is a positive or negative number*/

	if ((ptr[index] >= 'A' && ptr[index] <= 'Z') || (ptr[index] >= 'a' && ptr[index] <= 'z')) {
		i++;/*A valid label begins with an alphabetic letter*/

		while (ptr[index + i] != '\0' && ptr[index + i] != ',' && !isspace(ptr[index + i]) && i < 32 && ((ptr[index + i] >= 'A' && ptr[index + i] <= 'Z') || (ptr[index + i] >= 'a' && ptr[index + i] <= 'z') || (ptr[index + i] >= '0' && ptr[index + i] >= '9'))) {
			i++;/*followed by some series of letters Alphabets (uppercase or lowercase) and/or numbers*/
		}
		if (i > 31) {/*The maximum length of a label is 31 characters*/
			print_error(line_num, "The maximum length of a label is 31 characters", ptr);
			return-2;
		}
		if (i > 0)/*label*/
			return i;
	}
	print_error(line_num, "Invalid operand", ptr);
	return -2;
}

int countActionList(int actionNum, char* ptr) {
	
	int addres1 = 0, addres2 = 0, NumLine = 1,num_comman=0;
	int are = 0, operand1 = 0, operand2 = 0;
	int flag_operand1_number = 0, Flag_register_operand1 = 0, flag_operand2_number = 0, Flag_register_operand2 = 0;
	int Test_operand2_number = 0, Test_operand2_register = 0;
	num_comman=countCommas(ptr);
	if(num_comman>1){
		print_error(line_num, "punctuation above expected", ptr);
		return -2;
	}
	if (!isTextLeft(ptr, 0)) {/*A function that checks that there is a continuation of the string,
		operations 0-13 must be at least with an operand*/
		print_error(line_num, "Syntax error, blank line is not possible after action name", ptr);
		return -2;
	}
	delete_spaces(&ptr);
	ptr = strtok(ptr, ", \t");
	if(ptr[strlen(ptr)-1]==','){/*When the comma is adjacent to the 1st operand*/
		ptr[strlen(ptr)-1]=' ';
	}
	addres1 = getAdress(ptr, 0);
	switch (addres1)
	{
	case -1:/*number*/
		if ((actionNum >= 0 && actionNum <= 3) || actionNum == 12) {
			addres1 = 1;
			NumLine += 1;
			operand1 = textToNum(ptr);
			textToNum(ptr);/**/
			if (operand1 == -1)
				return 0;
			flag_operand1_number = 1;/*true*/
			ptr += end_of_text(ptr, 0);
		}
		else {
			print_error(line_num, "Syntax error, immediate address(0), cannot be in the first address in this operation", ptr);
			return -1;
		}
		break;
	case -5:
		addres1 = 5;
		NumLine += 1;
		operand1= atoi(&ptr[2]);
		Flag_register_operand1 = 1;
		ptr += end_of_text(ptr, 0);
		break;
	case -2:
		print_error(line_num, "Error", ptr);
		return -1;
		break;
	}

	if (addres1 > 0) {
		if(flag_operand1_number !=1&& Flag_register_operand1 != 1){
		/*if (actionNum != 6) {*/
			addres1 = 3;
			NumLine += 1;
			ptr += end_of_text(ptr, 0);
		
		}
		/*else {
			print_error(line_num, "syntax error, Addressing a direct register, cannot be at the first address in this operation", ptr);
			return -1;
		}
}*/
	}
	delete_spaces(&ptr);
	if (actionNum <= 3 || actionNum == 6)
	{
		
			ptr += 1;
		delete_spaces(&ptr);
	if(ptr[0] == ','){/*when the comma is adjacent to the 2nd operand*/
		ptr += 1;
	delete_spaces(&ptr);
	}
	addres2 = getAdress(ptr, 0);
		switch (addres2)
		{
		case -1:
			if (actionNum == 1) {
				flag_operand2_number = 1;
				Test_operand2_number =1;
				addres2 = 1;
				operand2 = textToNum(ptr);
				NumLine += 1;
				ptr += end_of_text(ptr, 0);
			}
			else {
				print_error(line_num, "Syntax error, immediate address, cannot be in the first address in this operation", ptr);
				return -1;
			}
			break;
		case -5:
			addres2 = 5;
			NumLine += 1;
			operand2= atoi(&ptr[2]);
			Flag_register_operand2 = 1;
			Test_operand2_register =5;
			ptr += end_of_text(ptr, 0);
			break;
		case -2:
			print_error(line_num, "Error", ptr);
			return -1;
			break;
		}
		if (addres2 > 0) {
			/*Checking if the second operand is a label and not a register or a number*/
			if(Test_operand2_number !=1&& Test_operand2_register !=5)
			{
			addres2 = 3;
			NumLine += 1;
			ptr += end_of_text(ptr, 0);
			}	
		}
	}
	else {
		if (isTextLeft(ptr, 0))
			print_error(line_num, "No continuation of this provision is expected", ptr);

	}

	if(addres2==0&&(addres1==3||addres1==1||addres1==5))
{
		    addres2=addres1;
			addres1=0;
}
	if((NumLine==3 && num_comman!=1)||(NumLine==2 &&(num_comman!=0))){
		/*Check that only if there are 2 operands there must be only one comma*/
		print_error(line_num, "punctuation not as expected", ptr);
		return -2;
		}
	insert_opcod(are, addres1, actionNum, addres2, IC);
	IC += 1;
	
	if(addres1==3)
		IC++;
	

	if (Flag_register_operand2 && Flag_register_operand1) {
		insert_registers(are, operand2, operand1);

		IC += 1;
	}
	if(flag_operand1_number){
		insert_number(are, operand1);
		IC += 1;
	}
	if (Flag_register_operand1 && !Flag_register_operand2) {
		if(addres1!=0)
		insert_registers(are,0, operand1);
		else
		insert_registers(are,operand1,0);
		IC += 1;
		
	}
	if (flag_operand2_number) {
		insert_number(are, operand2);
		IC += 1;
	}
	if (!Flag_register_operand1 && Flag_register_operand2) {
		
		insert_registers(are, operand2, 0);
		IC += 1;
	}
	if(addres2==3)
		IC++;	
	
	return NumLine;
}


int textToNum(char* ptr) {
        int result = 0, start = 0;
        if (ptr[start] != '-' && ptr[start] != '+' && (ptr[start] < '0' || ptr[start] > '9')) {
                return -1;
        }
        if (ptr[start] == '-' || ptr[start] == '+') {
                start++;
        }
        while (ptr[start] >= '0' && ptr[start] <= '9') {
                result = result * 10 + (ptr[start] - '0');
                start++;
        }
        if (ptr[0] == '-') {
                result = -result;
        }
        return result;
}

int countCommas(char* ptr){/*The function returns the number of commas in the string*/
int count=0;
char* current=ptr;
while(*current!='\0'){
	if(*current==','){
		count++;
	}
	current++;
	}
return count;
}

void replaceColonsWithSpace(char* ptr) {
int i;
    for ( i = 0; ptr[i] != '\0'; i++) {
        if (ptr[i] == ':' && ptr[i + 1] != ' ') {
            ptr[i] = ':';
            ptr[i + 1] = ' ';
        }
    }
}

int isValidString(char* ptr) {
int i;
     if (ptr[0] == '"' && ptr[strlen(ptr) - 1] == '"') {
        for ( i = 1; i < strlen(ptr) - 1; i++) {
            if (ptr[i] < 32 || ptr[i] > 126) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
