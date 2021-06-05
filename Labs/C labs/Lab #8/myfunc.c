//
// Created by Anton on 27.04.2021.
//

#include "myfunc.h"

int input_int(char *text, int upper_bound, int lower_bound) {
    int error, chr, truncated;
    double res;
    bool choose = true;
    while (choose == true) {
        printf("%s", text);
        error = scanf("%lf", &res);
        truncated = (int) res;
        while ((chr = getchar()) != '\n' && chr != EOF) {}
        if (error != 1 || truncated != res) {
            printf("You entered wrong type of variable. Try again: \n");
        } else {
            if (res > upper_bound || res < lower_bound) {
                printf("The number cannot be higher than the specified number - %d - or lower than %d. "
                       "Try again:\n", upper_bound, lower_bound);
            } else {
                choose = false;
            }
        }
    }
    return (int) res;
}

void clear(void) {
    system("cls||clear");
}

void edit_str(char str[]) {
    int length = (int) strlen(str);
    if (str[0] == ' ') {
        for (int j = 0; j < length; ++j) {
            str[j] = str[j + 1];
        }
        length--;
    }
    if (str[length - 1] == '\n') {
        str[length - 1] = '\0';
    }
}