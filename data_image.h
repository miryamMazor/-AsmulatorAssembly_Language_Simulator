#ifndef PROJECT_DATA_IMAGE_H
#define PROJECT_DATA_IMAGE_H
#pragma once
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define BIGNUM 2047

#define MINNUM -2048
typedef struct newData *data_ptr;

struct newData {
    int address;
    char *name;
    union {

        unsigned int all: 12;

        struct {
            unsigned int codASCII: 12;
        } cod_String;

        struct {
            unsigned int codASCII: 12;
        } cod_data;
        struct {
            unsigned int out: 12;


        } output;

    } u;
    data_ptr next;

};

void insertData(int num);

void data_code(char *ptr);

void insertString(char c);

int string_code(char *ptr);

int isNumber(char *ptr);

int commas_num(char *str);

int check_commas(char *ptr);

void remove_spaces_beg_end(char **str);

void freeData();

#endif
