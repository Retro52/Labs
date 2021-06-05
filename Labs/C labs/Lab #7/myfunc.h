//
// Created by Anton on 27.04.2021.
//

#ifndef HROMOVA_7_MYFUNC_H
#define HROMOVA_7_MYFUNC_H

//     Includes

//    lib for ini parsing
#include "stdbool.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <math.h>
#include "time.h"

//    function for action logging
//
//     Defining macros
//

//Array will be able to fill up to 2 gigs of RAM, can be changed
#define MAX_ALLOC_ARR_SIZE 268435456

//Matrix will be able to fill up to 8 gigs of RAM (32768x32768 elements), can be changed
#define MAX_ALLOC_MATRIX_SIZE 32768

//Max recommended recursion depth
#define MAX_REC 32768

//Max static array size (can be changed, not recommended)
#define MAX_PRERALLOC_ARR_SIZE 10000

//Matrix size -x 100*100 = 10000 (max array len)
#define MAX_PRERALLOC_MATRIX_SIZE 100

//Recommended max input for integer (or any other) values
#define MAX_INPUT 2147483647
//Or just use -MAX_INPUT
#define MIN_INPUT -2147483647
//Range for counting sort
#define RANGE 255

//defining function to check float/int variables given by user which takes text (question/request to user)
double input(char *text, double upper_bound, double lower_bound);

int input_int(char *text, int upper_bound, int lower_bound);

double pow2(int degree);

//quick sort function
void quicksort(double *arr, int first, int last);

//allocated dynamic array, func return pointer to array
double *create_array(int count);

//filling preallocated static array
void fill_array(double *arr, int count);

//allocated dynamic matrix, function returns pointer to it, works pretty well, except saving rows and cols number, waiting to be improved
double **create_matrix(int rows, int cols);

//filling preallocated static matrix !!!!! this function doesnt work now !!!!!
void fill_matrix(double arr[MAX_PRERALLOC_MATRIX_SIZE][MAX_PRERALLOC_MATRIX_SIZE]);

//function to clean console
void clear();

//random generators; bool boost - special bool var to increase chance of appearing 0  between another options
double randomize();

int randomize_bool();

static char *rand_string(char *str, size_t size);

char *rand_string_alloc(size_t size);

void edit_str(char str[]);

#endif //HROMOVA_7_MYFUNC_H
