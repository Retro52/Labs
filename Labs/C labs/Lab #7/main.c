#include <stdio.h>
#include "stdbool.h"
#include "myfunc.h"
#include "list.h"
#include "route.h"

void task_1(void);

void task_2(void);


int main(void) {
    struct timeval time;
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
    bool exit_program = false;
    int menu;
    while (exit_program == false)
    {
        static bool initialized;
        if (!initialized)
        {
            initialized = true;
            printf("Laboratory work #7\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");
        }
        menu = input_int("Main menu\n"
                         "  1. Numbers array task\n"
                         "  2. Route structures array task\n"
                         "  3. Clean console\n"
                         "  4. Exit from program\n"
                         "  5. Rate this masterpiece\n",
                         5, 1);
        if (menu == 1)
            task_1();
        if (menu == 2)
            task_2();
        if (menu == 3)
            clear();
        if (menu == 4)
            exit_program = true;
        if (menu == 5)
            printf("https://docs.google.com/spreadsheets/d/19psiLkwRZoC9aLW0Pcmy8t72dspfBn9A_ez8uGbSEeo/edit#gid=0\n");
    }
    return 0;
}

void task_1(void) {
    int num = input_int("Now, please enter a key for first list element: ", MAX_INPUT, MIN_INPUT);
    struct list *head = init(num);
    struct list *cur = head;
    struct list *tail = head;
    bool end = false;
    while (!end)
    {
        int menu = input_int("Task 1 menu\n  "
                         "1. Add element\n  "
                         "2. Delete item\n  "
                         "3. Print current list\n  "
                         "4. Print all elements which are above the average of the rest\n  "
                         "5. Clean console\n  "
                         "6. Back to main menu\n  "
                         "7. Put me the highest mark for this masterpiece\n  ",
                         7, 1);
        if (menu == 1)
        {
            bool subend = false;
            while (!subend){
                int sub = input_int("Add element menu\n"
                                    "  1. Add element to the end\n"
                                    "  2. Add element to the beginning\n"
                                    "  3. Insert after element by its index\n"
                                    "  4. Insert after element by its value\n"
                                    "  5. Print current list\n"
                                    "  6. Back to Task 1 menu\n",
                                    6, 1);
                if (sub == 1)
                {
                    int value = input_int("Enter value: ", MAX_INPUT, MIN_INPUT);
                    tail = insert(tail, value);
                }
                if (sub == 2)
                {
                    int value = input_int("Enter value: ", MAX_INPUT, MIN_INPUT);
                    if (head->next == NULL)
                    {
                        tail = head;
                    }
                    head = VivaLaHead(head, value);
                }
                if (sub == 3) {

                    int idx = input_int("Enter list index: \n", MAX_INPUT, MIN_INPUT);

                    if (idx == 0) {
                        if (head->next == NULL) {
                            int value = input_int("Enter value for item", MAX_INPUT, MIN_INPUT);
                            tail = insert(cur, value);
                        } else {
                            int value = input_int("Enter value for item", MAX_INPUT, MIN_INPUT);
                            cur = insert(cur, value);
                        }
                    }
                    else{
                        cur = head;
                        int i = 0;
                        while (cur->next != NULL && i != idx)
                        {
                            cur = cur->next;
                            i++;
                        }
                        if (cur->next == NULL && i == idx){
                            int value = input_int("Enter element key: \n", MAX_INPUT, MIN_INPUT);
                            tail = insert(cur, value);
                        }
                        else if (cur->next != NULL && i == idx)
                        {
                            int value = input_int("Enter element key: \n", MAX_INPUT, MIN_INPUT);
                            cur = insert(cur, value);
                        }
                        else
                        {
                            printf("Index is not valid\n");
                        }
                    }
                }
                if (sub == 4)
                {
                    int key = input_int("Enter key value\n"
                                        "(if there is several same values program will pick "
                                        "the first one from beginning): ",
                                        MAX_INPUT, MIN_INPUT);
                    cur = head;
                    while (cur->next != NULL && cur->field != key)
                    {
                        cur = cur->next;
                    }
                    if (cur->next == NULL)
                    {
                        if(cur->field != key){
                            printf("Key not found\n");
                        }
                        else
                        {
                            int value = input_int("Enter new element value: ", MAX_INPUT, MIN_INPUT);
                            tail = insert(cur, value);
                        }
                    }
                    else
                    {
                        int value = input_int("Enter new element value: ", MAX_INPUT, MIN_INPUT);
                        cur = insert(cur, value);
                    }
                }
                if (sub == 5)
                {
                    PrintList(head, "Current list");
                }
                if (sub == 6)
                {
                    subend = true;
                }
            }
        }
        if (menu == 2)
        {
            bool subend = false;
            while (!subend) {
                int sub = input_int("Add element menu\n"
                                    "  1. Delete element by index \n"
                                    "  2. Delete element`s with some keys\n"
                                    "  3. Delete first element (head)\n"
                                    "  4. Print current list\n"
                                    "  5. Back to Task 1 menu\n",
                                    5, 1);
                if (sub == 1)
                {
                    int idx = input_int("Enter element index: ", MAX_INPUT, MIN_INPUT);
                    int i = 0;
                    cur = head;
                    while (cur->next != NULL && i != idx)
                    {
                        cur = cur->next;
                        i++;
                    }
                    if (idx == 0 && head->next == NULL){
                        printf("You cannot delete the whole list\n");
                    }
                    else if (idx == 0 && head->next != NULL)
                    {
                        sub = 3;
                    }
                    else if (cur->next == NULL && i != idx)
                    {
                        printf("Element with this index not found: \n");
                    }
                    else if (i == idx)
                    {
                        delete(cur, head);
                    }
                }
                if (sub == 2)
                {
                    int key = input_int("Enter key, items with that value will be deleted: ", MAX_INPUT, MIN_INPUT);
                    cur = head;
                    while (cur != NULL && head->next != NULL)
//                    while (cur->next != NULL && head->next != NULL)
                    {
                        if (cur->field == key)
                        {
                            if (cur == head)
                            {
                                if (head->next == NULL){
                                    printf("You cannot delete the whole list\n");
                                    cur = cur->next;
                                }
                                else
                                {
                                    cur = head->next;
                                    head = deletehead(head);
                                }
                            }
                            else
                            {
                                if (cur->next == NULL)
                                {
                                    tail = delete(cur, head);
                                    cur = NULL;
                                }
                                else{
                                    cur = delete(cur, head);
                                }
                                if (cur != NULL)
                                {
                                    cur = cur->next;
                                }
                            }
                        } else{
                            cur = cur->next;
                        }
                    }
                    printf("New list with removed '%d': \n", key);
                    PrintList(head, "Current list");
                }
                if (sub == 3)
                {
                    if (head->next == NULL){
                        printf("You cannot delete the whole list\n");
                    }
                    else
                    {
                        head = deletehead(head);
                    }
                }
                if (sub == 4)
                {
                    PrintList(head, "Current list");
                }
                if (sub == 5)
                {
                    subend = true;
                }
            }
        }
        if (menu == 4)
        {
            struct list *p = head;
            int iter = 0;
            float res = 0;
            do {
                res += (float) p->field;
                p = p->next;
                iter++;
            } while (p != NULL);
            res = res / (float) iter;
            printf("====================[ Main list average = %.2f ]=======================\n",
                   res);
            struct list *step_list = init(-1);
            struct list *step_cur = step_list;
            p = head;
            do {
                if ((float) p->field > res)
                {
                  step_cur = insert(step_cur, p->field);
                }
                p = p->next;
                iter++;
            } while (p != NULL);

            PrintList(head, "First list");
            if (step_list->next != NULL)
            {
                PrintList(step_list->next, "New list");
            } else{
                printf("New list is empty (this happens if all elements are the same) :((\n");
            }
        }
        if (menu == 3)
            PrintList(head, "Current list");
        if (menu == 5)
            clear();
        if (menu == 6)
        {
            end = true;
        }
        if (menu == 7)
        {
            printf("https://docs.google.com/spreadsheets/d/19psiLkwRZoC9aLW0Pcmy8t72dspfBn9A_ez8uGbSEeo/edit#gid=0\n");
        }
    }
}

void task_2(void) {
    bool random = input_int("First, we need to initialize list with first value\n"
                            "Type 1 for random, or 0 for your own values\n", 1, 0);
    struct rlist *head = rinit(random);
    struct rlist *cur = head;
    struct rlist *tail = head;
    bool end = false;
    while (!end)
    {
        int menu = input_int("Task 2 menu\n  "
                             "1. Add element\n  "
                             "2. Delete item\n  "
                             "3. Sort current list\n  "
                             "4. Print current list\n  "
                             "5. Clean console\n  "
                             "6. Back to main menu\n  "
                             "7. Put me the highest mark for this masterpiece\n  ",
                             8, 1);
        tail = get_tail(head);
        if (menu == 1)
        {
            bool subend = false;
            while (!subend){
                tail = get_tail(head);
                int sub = input_int("Add element menu\n"
                                    "  1. Add element to the end\n"
                                    "  2. Add element to the beginning\n"
                                    "  3. Insert after element by its index\n"
                                    "  4. Insert after element by its value\n"
                                    "  5. Print current list\n"
                                    "  6. Back to Task 2 menu\n",
                                    6, 1);
                if (sub == 1)
                {
                    int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                    struct ROUTE *new = additem(rand);
                    tail = rinsert(tail, new);
                }
                if (sub == 2)
                {
                    int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                    struct ROUTE *new = additem(rand);
                    if (head->next == NULL)
                    {
                        tail = head;
                    }
                    head = VivaLaRHead(head, new);
                }
                if (sub == 3) {

                    int idx = input_int("Enter list index: \n", MAX_INPUT, MIN_INPUT);

                    if (idx == 0) {
                        if (head->next == NULL) {
                            int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                            struct ROUTE *new = additem(rand);
                            tail = rinsert(tail, new);
                        } else {
                            int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                            struct ROUTE *new = additem(rand);
                            cur = rinsert(cur, new);
                        }
                    }
                    else{
                        cur = head;
                        int i = 0;
                        while (cur->next != NULL && i != idx)
                        {
                            cur = cur->next;
                            i++;
                        }
                        if (cur->next == NULL && i == idx){
                            int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                            struct ROUTE *new = additem(rand);
                            tail = rinsert(cur, new);
                        }
                        else if (cur->next != NULL && i == idx)
                        {
                            int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                            struct ROUTE *new = additem(rand);
                            cur = rinsert(cur, new);
                        }
                        else
                        {
                            printf("Index is not valid\n");
                        }
                    }
                }
                if (sub == 4)
                {
                    int key = input_int("Enter key value (Route number): ",
                                        MAX_INPUT, MIN_INPUT);
                    cur = head;
                    while (cur->next != NULL && cur->item->route_number != key)
                    {
                        cur = cur->next;
                    }
                    if (cur->next == NULL)
                    {
                        if(cur->item->route_number != key){
                            printf("Key not found\n");
                        }
                        else
                        {
                            int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                            struct ROUTE *new = additem(rand);
                            tail = rinsert(cur, new);
                        }
                    }
                    else
                    {
                        int rand = input_int("Would you like to randomize values (1/0): ", 1, 0);
                        struct ROUTE *new = additem(rand);
                        cur = rinsert(cur, new);
                    }
                }
                if (sub == 5)
                {
                    RPrintList(head);
                }
                if (sub == 6)
                {
                    subend = true;
                }
            }
        }
        if (menu == 2)
        {
            bool subend = false;
            while (!subend) {
                tail = get_tail(head);
                int sub = input_int("Add element menu\n"
                                    "  1. Delete element by index \n"
                                    "  2. Delete element`s with some keys\n"
                                    "  3. Delete first element (head)\n"
                                    "  4. Print current list\n"
                                    "  5. Back to Task 2 menu\n",
                                    5, 1);
                if (sub == 1)
                {
                    int idx = input_int("Enter element index: ", MAX_INPUT, MIN_INPUT);
                    int i = 0;
                    cur = head;
                    while (cur->next != NULL && i != idx)
                    {
                        cur = cur->next;
                        i++;
                    }
                    if (idx == 0 && head->next == NULL){
                        printf("You cannot delete the whole list\n");
                    }
                    else if (idx == 0 && head->next != NULL)
                    {
                        sub = 3;
                    }
                    else if (cur->next == NULL && i != idx)
                    {
                        printf("Element with this index not found: \n");
                    }
                    else if (i == idx)
                    {
                        rdelete(cur, head);
                    }
                }
                if (sub == 2)
                {
                    int key = input_int("Enter Route number. Routes with this number will be deleted: ", MAX_INPUT, MIN_INPUT);
                    cur = head;
                    while (cur != NULL && head->next != NULL)
                    {
                        if (cur->item->route_number == key)
                        {
                            if (cur == head)
                            {
                                if (head->next == NULL){
                                    printf("You cannot delete the whole list\n");
                                    cur = cur->next;
                                }
                                else
                                {
                                    cur = head->next;
                                    head = rdeletehead(head);
                                }
                            }
                            else
                            {
                                if (cur->next == NULL)
                                {
                                    tail = rdelete(cur, head);
                                    cur = NULL;
                                }
                                else{
                                    cur = rdelete(cur, head);
                                }
                                if (cur != NULL)
                                {
                                    cur = cur->next;
                                }
                            }
                        } else{
                            cur = cur->next;
                        }
                    }
                    printf("New list with removed '%d': \n", key);
                    RPrintList(head);
                }
                if (sub == 3)
                {
                    if (head->next == NULL){
                        printf("You cannot delete the whole list\n");
                    }
                    else
                    {
                        head = rdeletehead(head);
                    }
                }
                if (sub == 4)
                {
                    RPrintList(head);
                }
                if (sub == 5)
                {
                    subend = true;
                }
            }
        }
        if (menu == 3)
        {
            tail = get_tail(head);
            cur = head;
            int len = 0;
            do {
                len++;
                cur = cur->next;
            } while (cur != NULL);
            cur = head;
            struct rlist *tempcur = head;

            int sort = input_int("Select sort option\n"
                                 "  1.  Sort by road number\n"
                                 "  2.  Sort by road A name\n"
                                 "  3.  Sort by road B name\n", 3, 1);
            if (sort == 1)
            {
                while (cur->next != NULL){
                    if (cur->item->route_number > cur->next->item->route_number)
                    {
                        head = swap(cur, cur->next, head);
                        cur = head;
                    }
                    else
                    {
                        cur = cur->next;
                    }
                }
            }
            if (sort == 2)
            {
                while (cur->next != NULL){
                    if (strcmp(cur->item->name_a, cur->next->item->name_a) > 0)
                    {
                        head = swap(cur, cur->next, head);
                        cur = head;
                    }
                    else
                    {
                        cur = cur->next;
                    }
                }
            }
            if (sort == 3)
            {
                while (cur->next != NULL){
                    if (strcmp(cur->item->name_b, cur->next->item->name_b) > 0)
                    {
                        head = swap(cur, cur->next, head);
                        cur = head;
                    }
                    else
                    {
                        cur = cur->next;
                    }
                }
            }
            RPrintList(head);
        }
        if (menu == 4)
            RPrintList(head);
        if (menu == 5)
            clear();
        if (menu == 6)
        {
            tail = get_tail(head);
            end = true;
        }
        if (menu == 7)
        {
            printf("https://docs.google.com/spreadsheets/d/19psiLkwRZoC9aLW0Pcmy8t72dspfBn9A_ez8uGbSEeo/edit#gid=0\n");
        }
    }
}