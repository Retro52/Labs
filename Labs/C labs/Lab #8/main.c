#include <stdio.h>
#include "myfunc.h"
#include "task_1.h"
#include "task_2.h"

int main() {
    bool program = true;
    while (program) {
        static bool initialized;
        if (!initialized) {
            initialized = true;
            printf("Laboratory work #8\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");
        }
        int menu = input_int("Main menu\n"
                             "  1. Text files operation\n"
                             "  2. Binary files operation\n"
                             "  3. Clear console\n"
                             "  4. Exit program\n", 4, 1);
        switch (menu) {
            case 1:
                task_1();
                break;
            case 2:
                task_2();
                break;
            case 3:
                clear();
                break;
            case 4:
                program = false;
            default:
                break;
        }
    }
    return 0;
}