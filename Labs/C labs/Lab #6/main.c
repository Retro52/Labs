#include "myfunc.h"


int task_1() {
    double *arr = create_array(false);

    if (!arr) {
        printf("Memory leak error!\n");
        return -1;
    }
    int m = (int) arr[0];
    printf("Entered array:\n\n");
    for (int i = 1; i < m + 1; ++i) {
        printf("arr[%d] = %.2lf\n", i - 1, arr[i]);
    }
    int k = input_int("\nEnter matrix row len: ", m, 1);

    int truncated = (int) m / k;
    float not_truncated = (float) m / (float) k;

    int rows;
    if ((float) truncated == not_truncated) {
        rows = (int) truncated;
    } else {
        rows = (int) truncated + 1;
    }

    double **matrix = (double **) malloc((rows) * sizeof(double *));
    for (int j = 0; j < rows; j++)
        matrix[j] = (double *) malloc((k) * sizeof(double));
    if(!matrix){
      printf("Memory leak error!\n");
      return -2;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < k; ++j) {
            if (i * j + j + 1 <= m + 1) {
                matrix[i][j] = arr[i * k + j + 1];
            } else {
                matrix[i][j] = 0.0;
            }
        }
    }
    printf("\nGenerated matrix\n\n");
    if (k < 5){
        for (int i = 0; i < rows; ++i) {
            printf("|");
            for (int j = 0; j < k; ++j) {
                printf("%15.2lf\t", matrix[i][j]);
            }
            printf("|\n");
        }
    } else{
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < k; ++j) {
                printf("Matrix[%d][%d] = %.2lf\n", i, j, matrix[i][j]);
            }

        }
    }

    printf("\n");

    free(arr);
    for (int j = 0; j < rows; j++)
        free(matrix[j]);

    return 0;
}

int main(void) {
    bool exit_program = false;
    int menu;

    while (exit_program == false) {

        static bool initialized;
        if (!initialized) {
            initialized = true;
            printf("Laboratory work #6\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");
        }
        menu = input_int("Main menu\n"
                         "  1. Generate matrix from given array\n"
                         "  2. Clean console\n"
                         "  3. Exit from program\n",
                         4, 1);
        if (menu == 1) {
            int res = task_1();
            if (res == -1) {
                return -1;
            }
            if (res == -2) {
                return -2;
            }

        }
        if (menu == 2)
            clear();
        if (menu == 3)
            exit_program = true;
    }

    return 0;
}