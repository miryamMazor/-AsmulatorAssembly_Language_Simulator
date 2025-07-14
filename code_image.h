#ifndef PROJECT_CODE_IMAGE_H
#define PROJECT_CODE_IMAGE_H
#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "global.h"

extern boolean iserror;/*This boolean returns an error*/
typedef struct newCode *code_ptr;
struct newCode {
    int address;
    union {
        unsigned int all: 12;
        struct {/*instructions and not data */
            unsigned int ARE: 2;/*00*/
            unsigned int b: 3;
            unsigned int c: 4;
            unsigned int d: 3;
        } S;
        struct {
            unsigned int ARE: 2;
            unsigned int mis: 10;


        } AddressFrom;

        struct {
            unsigned int ARE: 2;
            unsigned int mis1: 5;/*target*/
            unsigned int mis2: 5;/*source*/
        } regirster;
        struct {

            unsigned int ARE: 2;
            unsigned int mis1: 10;
        } lebal;

        struct {
            unsigned int zero: 5;
            unsigned int codASCII: 7;
        } d_String;
        struct {
            unsigned int misBinary: 12;
        } All;
        struct {
            unsigned int out: 12;

        } output;
    } u;
    code_ptr next;
};

void insert_opcod(int are, int rt, int op, int rs, int ic);

/* insert binary for line to have opcode
 * get ARE -0/1/2 Pointer to the position
 * get rt 1, 3 ,5 - type for oparand
*get opcode number
*get rs 1, 3 ,5 - type for oparand
 * */
void insert_registers(int are, int rt, int rs);

/* insert binary for line to have registers
* get ARE -0/1/2 Pointer to the position
* get rt 1, 3 ,5 - type for oparand
        *get opcode number
*get rs adress for oparnd
 * for label insert 0
* */
void insert_number(int are, int num);

void insert_lebal_code(int are, int ic_label);

/* insert binary for line to have registers
* get ARE -0/1/2 Pointer to the position
* get rt 1, 3 ,5 - type for oparand
        *get opcode number
*get rs adress for oparnd
 * for label insert 0
* */
void insert_askii(int askii);

void free_code();

/*free list*/
void selection_sort_by_address();


/*Sort the array by address*/


#endif

