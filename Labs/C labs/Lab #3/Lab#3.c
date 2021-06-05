#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


int input_int(char *text, int upper_bound, int lower_bound);

void clear();

void task();

int main() {
    bool main_bool = true;
    bool program_exit = false;
    int a;

    printf("Laboratory work #3\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");

    while (program_exit == false) {

        main_bool = true;

        while (main_bool == true) {
            printf("Main menu:\n 1. Print even/odd words separately \n 2. Clean console\n 3. Exit from program\n");

            a = input_int("", 3, 1);

            if (a == 1) {
                task();
                main_bool = false;
            } else {
                if (a == 2) {
                    clear();
                } else {
                    if (a == 3) {
                        main_bool = false;
                        program_exit = true;
                    } else {
                        printf("ERROR! You can choose only programs 1 or 2\n");
                    }
                }
            }
        }
    }
    return 0;
}


void task() {
    //def index vars
    int i, j = 0, k = 0;
    //def var responsible for even-ness
    int div = 2;
    //def arrays
    char even[10000];
    char odd[10000];
    char s[10000];
    printf("Enter any string separating words with ONE space (max len is 10000 letters):\n");
    scanf("%[^\n]s", s);
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] != ' ') {
            if (div % 2 == 1) {
                even[j] = s[i];
                j++;
            }
            if (div % 2 == 0) {
                odd[k] = s[i];
                k++;
            }
        }
        if (s[i] == ' ') {
            if (div % 2 == 1) {
                even[j] = ' ';
                j++;
            }
            if (div % 2 == 0) {
                odd[k] = ' ';
                k++;
            }
            div++;
        }
    }

    for (i = 0; i < 89; i++) {
        printf("-");
    }
    i = 0;
    printf("\nEven words\n");
    while (even[i] != 0) {
        if (even[i] == ' ')
            printf("\n");
        else
            printf("%c", even[i]);
        i++;
    }
    printf("\n");

    for (i = 0; i < 89; i++) {
        printf("-");
    }
    i = 0;
    printf("\nOdd words\n");
    while (odd[i] != 0) {
        if (odd[i] == ' ')
            printf("\n");
        else
            printf("%c", odd[i]);
        i++;
    }
    printf("\n");
    for (i = 0; i < 89; i++) {
        printf("-");
    }
    printf("\n");
}


int input_int(char *text, int upper_bound, int lower_bound) {
//    int res = 0;
    int error, chr, res = 0;
    bool choose = true;
    while (choose == true) {
        printf("%s", text);
        error = scanf("%d", &res);
        while ((chr = getchar()) != '\n' && chr != EOF) {}
        if (error != 1) {
            printf("You entered wrong type of variable\n");
        } else {
            if (res > upper_bound || res < lower_bound) {
                printf("The number cannot be higher than the specified number - %d - or lower than %d\n", upper_bound,
                       lower_bound);
            } else {
                choose = false;
            }
        }
    }
    return res;
}


void clear() {
    system("cls||clear");
}