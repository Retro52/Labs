#include "myfunc.h"
#include "string.h"

#define str_len 100
#define rand_str_len 10


struct ROUTE {
    char *name_a;
    char *name_b;
    int route_number;
};

void struct_sort(struct ROUTE **arr, int len) {
    struct ROUTE *temp;
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (arr[j]->route_number <= arr[j + 1]->route_number) {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }

}

struct ROUTE *additem(bool random) {
    struct ROUTE *new_item;

    char *string_a = malloc((str_len + 1) * sizeof(char));
    char *string_b = malloc((str_len + 1) * sizeof(char));

    int route;
    if (!random) {

        printf("Enter name for location A: ");
        fgets(string_a, str_len, stdin);
        printf("Location A name: ");
        puts(string_a);

        printf("Enter name for location B: ");
        fgets(string_b, str_len, stdin);
        printf("Location B name: ");
        puts(string_b);

        route = input_int("Enter route number: ", MAX_INPUT, MIN_INPUT);
    } else {
        int size_1 = abs((int) randomize() % rand_str_len);
        int size_2 = abs((int) randomize() % rand_str_len);
        string_a = rand_string_alloc(size_1);
        string_b = rand_string_alloc(size_2);
        route = abs((int) randomize());
    }

    new_item = (struct ROUTE *) malloc(sizeof(struct ROUTE));
    new_item->name_a = string_a;
    new_item->name_b = string_b;
    new_item->route_number = route;
    return (new_item);
}


void listprint(struct ROUTE *lst, int index) {
    struct ROUTE *p;
    p = lst;
//    printf("------------------------------------------------------------------\n");
    printf("Structure #%d: \n"
           "  Name of location A is %s\n"
           "  Name of location B is %s\n"
           "  Route number = %d\n",
           index + 1,
           p->name_a,
           p->name_b,
           p->route_number);
//    printf("------------------------------------------------------------------\n");

}

void task_1() {
    bool sort_menu = true;
    int menu;
    struct ROUTE **lst = (struct ROUTE **) malloc(sizeof(struct ROUTE *) * 5);
    bool random = input_int("Type:\n   0 - Enter matrix elements\n"
                            "   1 - Randomize structure elements (strings inclusive): ", 1, 0);
    for (int i = 0; i < 5; ++i) {
        lst[i] = additem(random);
    }
    printf("\n\nEntered data: \n\n");
    for (int i = 0; i < 5; ++i) {
        listprint(lst[i], i);
    }
    printf("\n\nSorted data: \n\n");
    struct_sort(lst, 5);
    for (int i = 0; i < 5; ++i) {
        listprint(lst[i], i);
    }
    while (sort_menu) {
        menu = input_int("Subtask menu\n  "
                         "  1. Find location by key word\n  "
                         "  2. Print current structure\n"
                         "    3. Re-create structure\n  "
                         "  4. Clean console\n  "
                         "  5. Back to main menu\n",

                         5,
                         1);
        if (menu == 1) {
            bool found_a = false, found_b = false, nf = true;
            char *string = malloc((str_len + 1) * sizeof(char));
            printf("Enter location you would like to find: ");
            fgets(string, str_len, stdin);
            for (int i = 0; i < 5; ++i) {
                found_a = false, found_b = false;
                if ((int) strlen(string) == (int) (strlen(lst[i]->name_a))) {
                    int c = (int) strlen(string);
                    for (int j = 0; j < c - 1; ++j) {
                        if (lst[i]->name_a[j] == string[j]) {
                            found_a = true;
                        } else {
                            found_a = false;
                        }
                    }
                }
                if ((int) strlen(string) == (int) (strlen(lst[i]->name_b))) {
                    int c = (int) strlen(string);
                    for (int j = 0; j < c - 1; ++j) {
                        if (lst[i]->name_b[j] == string[j]) {
                            found_b = true;
                        } else {
                            found_b = false;
                        }
                    }
                }
                if (found_a) {
                    printf("Name found as a name of location A at the following structure: \n");
                    listprint(lst[i], i);
                    nf = false;
                }
                if (found_b) {
                    printf("Name found as a name of location B at the following structure: \n");
                    listprint(lst[i], i);
                    nf = false;
                }
            }
            if (nf)
                printf("Location not found :-(\n");
            free(string);

        }
        if (menu == 2) {
            for (int i = 0; i < 5; ++i) {
                listprint(lst[i], i);
            }
        }
        if (menu == 3)
            task_1();
        if (menu == 4)
            clear();
        if (menu == 5)
            sort_menu = false;
    }
}


int main(void) {
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
            printf("Laboratory work #5\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");
        }
        menu = input_int("Main menu\n  "
                         "  1. Structure sorting & finding task \n  "
                         "  2. Clean console\n  "
                         "  3. Exit from program\n",
                         3, 1);
        if (menu == 1)
            task_1();
        if (menu == 2)
            clear();
        if (menu == 3)
            exit_program = true;
    }
    return 0;
}