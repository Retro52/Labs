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

//Recommended max input for integer (or any other) values
#define MAX_INPUT 2147483647

int input_int(char *text, int upper_bound, int lower_bound);

//function to clean console
void clear();

void edit_str(char str[]);

#endif //HROMOVA_7_MYFUNC_H
