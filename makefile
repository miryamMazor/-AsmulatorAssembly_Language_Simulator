prime: global.o main.o prime_asembler.o commands_tabels.o second_pass.o out.o label_table.o isData.o first_pass.o data_image.o code_image.o AsSymbol.o action.o free.o
	gcc -g -Wall -ansi -pedantic global.o main.o prime_asembler.o commands_tabels.o second_pass.o out.o label_table.o isData.o first_pass.o data_image.o code_image.o AsSymbol.o action.o -o project free.o

global.o:global.c global.h
	gcc -c -Wall -ansi -pedantic global.c -o global.o

main.o:main.c main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o

prime_asembler.o:prime_asembler.c prime_asembler.h
	gcc -c -Wall -ansi -pedantic prime_asembler.c -o  prime_asembler.o

action.o:action.c action.h
	gcc -c -Wall -ansi -pedantic action.c -o action.o

AsSymbol.o:AsSymbol.c AsSymbol.h
	gcc -c -Wall -ansi -pedantic AsSymbol.c -o AsSymbol.o

code_image.o:code_image.c code_image.h
	gcc -c -Wall -ansi -pedantic code_image.c -o code_image.o

data_image.o:data_image.c data_image.h
	gcc -c -Wall -ansi -pedantic data_image.c -o data_image.o

first_pass.o:first_pass.c first_pass.h
	gcc -c -Wall -ansi -pedantic first_pass.c -o first_pass.o

commands_tables.o:commands_tabels.c commands_tabels.h
	gcc -c -Wall -ansi -pedantic commands_tables.c -o commands_tables.o

isData.o:isData.c isData.h
	gcc -c -Wall -ansi -pedantic isData.c -o isData.o

label_table.o:label_table.c label_table.h
	gcc -c -Wall -ansi -pedantic label_table.c -o label_table.o

out.o:out.c out.h
	gcc -c -Wall -ansi -pedantic out.c -o out.o

second_pass.o:second_pass.c second_pass.h
	gcc -c -Wall -ansi -pedantic second_pass.c -o second_pass.o
free.o:free.c free.h
	gcc -c -Wall -ansi -pedantic free.c -o free.o

