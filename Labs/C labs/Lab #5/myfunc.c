//
// Created by @Retro52 on 25.03.2021.
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

double input(char *text, double upper_bound, double lower_bound) {
    double res = 0;
    int error, chr;
    bool choose = true;
    while (choose == true) {
        printf("%s", text);
        error = scanf("%lf", &res);
        while ((chr = getchar()) != '\n' && chr != EOF) {}
        if (error != 1) {
            printf("Wrong input, try again: \n");
        } else {
            if (res > upper_bound || res < lower_bound) {
                printf("The number cannot be higher than the specified number - %.2f - or lower than %.2f."
                       " Try again: \n", upper_bound, lower_bound);
            } else {
                choose = false;
            }
        }
    }
    return res;
}

double *create_array(int count) {
    int rand, i;
    if (!count)
        printf("Enter array size here: ");
    count = input_int("", MAX_ALLOC_ARR_SIZE, 1);
    double *number = malloc((count + 1) * sizeof(double));
    if (!number)
        return NULL;
    printf("Entered size (floats are automatically converted to integer): %d\n", count);
    number[0] = count;
    rand = input_int("Type:\n 0 - Enter array elements\n 1 - Randomize array elements: ", 1, 0);
    if (rand == 0) {
        printf("Enter %d elements: \n", count);
        for (i = 1; i <= count; i++) {
            printf("Enter array[%d] element: ", i - 1);
            number[i] = input("", MAX_INPUT, MIN_INPUT);
        }
    } else {
        for (i = 1; i <= count; i++) {
            number[i] = randomize();
        }
    }
    return number;
}

void fill_array(double *arr, int count) {
    int rand, i;
    if (!count) {
        count = input_int("Enter array size here: ", MAX_PRERALLOC_ARR_SIZE, 1);
        printf("Entered size (floats are automatically converted to integer): %d\n", count);
        arr[0] = count;
    }
    rand = input_int("Type:\n 0 - Enter array elements\n 1 - Randomize array elements: ", 1, 0);
    if (rand == 0) {
        printf("Enter %d elements: \n", count);
        for (i = 1; i <= count; i++) {
            printf("Enter array[%d] element: ", i - 1);
            arr[i] = input("", MAX_INPUT, MIN_INPUT);
        }
    } else {
        for (i = 1; i <= count; i++) {
            arr[i] = randomize();
        }
    }
}

double **create_matrix(int rows, int cols) {
    int rand;
    if (!rows)
        rows = input_int("Enter rows number here: ", MAX_ALLOC_MATRIX_SIZE, 1);
    if (!cols)
        cols = input_int("Enter cols number here: ", MAX_ALLOC_MATRIX_SIZE, 1);
    //Set memory for matrix
    double **number = (double **) malloc((rows + 1) * sizeof(double *));
    for (int k = 0; k < rows + 1; k++)
        number[k] = (double *) malloc((cols + 1) * sizeof(double));
    //Error check if program ran out of memory
    if (!number) {
        return NULL;
    }
    number[0][cols] = rows;
    number[rows][0] = cols;
    printf("Entered size (floats are automatically converted to integer): %d * %d\n", rows, cols);
    rand = input_int("Type:\n 0 - Enter matrix elements\n 1 - Randomize matrix elements: ", 1, 0);
    if (rand == 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; ++j) {
                printf("Matrix[%d][%d] = ", i, j);
                number[i][j] = input("", MAX_INPUT, MIN_INPUT);
            }
        }
    } else {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; ++j) {
                number[i][j] = randomize();
            }
        }
    }
    return number;
}

void fill_matrix(double arr[MAX_PRERALLOC_MATRIX_SIZE][MAX_PRERALLOC_MATRIX_SIZE]) {
    int rand, i, rows, cols;
    rows = input_int("Enter rows number here: ", MAX_PRERALLOC_MATRIX_SIZE, 1);
    cols = input_int("Enter cols number here: ", MAX_PRERALLOC_MATRIX_SIZE, 1);
    printf("Entered size (floats are automatically converted to integer): %d * %d\n", rows, cols);
    rand = input_int("Type:\n 0 - Enter matrix elements\n 1 - Randomize matrix elements: ", 1, 0);
    if (rand == 0) {
        for (i = 0; i < rows; i++) {
            for (int j = 0; j < cols; ++j) {
                printf("Enter matrix[%d][%d] element: ", i, j);
                arr[i][j] = input("", MAX_INPUT, MIN_INPUT);
            }
        }
    } else {
        for (i = 0; i < rows; i++) {
            for (int j = 0; j < cols; ++j) {
                arr[i][j] = randomize();
            }
        }
    }
}

void quicksort(double *arr, int first, int last) {
    double temp;
    int pivot, i, j;
    if (first < last) {
        pivot = first;
        i = first;
        j = last;

        while (i < j) {
            while (arr[i] <= arr[pivot] && i < last)
                i++;
            while (arr[j] > arr[pivot])
                j--;
            if (i < j) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;
        quicksort(arr, first, j - 1);
        quicksort(arr, j + 1, last);

    }
}

double randomize() {
    //adding negative numbers to possible random results
    double res = rand() * pow(-1, randomize_bool() + 1);
    return res;
}

int randomize_bool() {
    int pow = (rand() % 2);
    return pow;
}

double pow2(int degree) {
    double a = 2;
    for (int i = 2; i < degree; ++i) {
        a *= 2;
    }
    return a;
}

void clear(void) {
    system("cls||clear");
}

static char *rand_string(char *str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\n';
        str[size + 1] = '\0';
    }
    return str;
}

char *rand_string_alloc(size_t size) {
    char *s = malloc(size + 2);
    if (s) {
        rand_string(s, size);
    }
    return s;
}
