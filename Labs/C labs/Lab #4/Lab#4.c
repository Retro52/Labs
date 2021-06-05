#include <stdio.h>
#include <stdlib.h>
#include "myfunc.h"
#include <stdbool.h>

//
//To understand everything also look at the file myfunc.h
//

//defining void task functions
void task_1(void);

void task_2(void);

//recursive multiplying function
int recursiveMultiplying(int x, int y, int res);

int main(void) {
    //specific seed test because of predictability of time(NULL) seed and repetitive results
    struct timeval time;
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    bool exit_program = false;
    int menu;
    //Main menu part
    while (exit_program == false) {
        //do-once func test for future projects
        //Of course, the same can be done by simply placing this piece of code outside the loop.
        static bool initialized;
        if (!initialized) {
            initialized = true;
            printf("Laboratory work #4\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");
        }
        menu = input_int("Main menu\n  "
                         "1. Array-pointer task. Replace all negative elements with zero\n  "
                         "2. Recursive multiplication using only add-operation \n  "
                         "3. Clean console\n  "
                         "4. Exit from program\n",
                         4, 1);
        if (menu == 1)
            task_1();
        if (menu == 2)
            task_2();
        if (menu == 3)
            clear();
        if (menu == 4)
            exit_program = true;
    }
    return 0;
}

void task_1(void) {
    int arr_num = input_int("Enter number of arrays you would like to change (max. 100): ", MAX_PRERALLOC_MATRIX_SIZE,
                            1);
    double mat[MAX_PRERALLOC_MATRIX_SIZE][MAX_PRERALLOC_MATRIX_SIZE];
    int size;
    double *arr;
    for (int i = 0; i < arr_num; ++i) {
        arr = create_array(false, i + 1);
        if (arr) {
            size = (int) arr[0];
            mat[i][0] = size;
            for (int j = 1; j <= size; ++j) {
                mat[i][j] = arr[j];
            }
            free(arr);
        } else
            printf("Memory error!\n");
    }
    for (int i = 0; i < arr_num; ++i) {
        printf("------------------------------------------------------------------\n");
        printf("Array #%d before edition:\n\n", i + 1);
        size = (int) mat[i][0];
        for (int j = 1; j <= size; ++j) {
            printf("Arr[%d] = %.2lf\n", j - 1, mat[i][j]);
        }
        quicksort(mat[i], 1, size);
        printf("Array #%d after edition:\n\n", i + 1);
        for (int j = 1; j <= size; ++j) {
            if (mat[i][j] < 0)
                mat[i][j] = 0;
            printf("Arr[%d] = %.2lf\n", j - 1, mat[i][j]);
        }
        printf("------------------------------------------------------------------\n");
    }
}

void task_2(void) {
    printf("This task works only for integers\nMax value input = 32768\n\n");
    int x = input_int("Enter first number: ", MAX_MULT_INT, -MAX_MULT_INT);
    int y = input_int("Enter second number: ", MAX_MULT_INT, -MAX_MULT_INT);
    int res = recursiveMultiplying(x, y, 0);
    printf("Answer: %d * %d = %d\n", x, y, res);
}

int recursiveMultiplying(int x, int y, int res) {
    //Well, this looks like i needed do-once function sooner than i thought)
    static bool initialized;
    if (!initialized) {
        initialized = true;
        if (x == 0 || y == 0)
            return 0;
        if (x < 0 && y > 0)
            return recursiveMultiplying(x, y, 0);
        if (x < 0 && y < 0)
            return recursiveMultiplying(-x, -y, 0);
        if (x > 0 && y > 0)
            return recursiveMultiplying(x, y, 0);
        if (x > 0 && y < 0)
            return recursiveMultiplying(y, x, 0);
    }
    res += x;
    if (y != 1)
        return recursiveMultiplying(x, y - 1, res);
    else {
        initialized = false;
        return res;
    }
}