//
// Created by Anton on 28.04.2021.
//

#include "route.h"

#include "list.h"
#include "stdio.h"
#include "stdlib.h"

#define str_len 100
#define rand_str_len 10

struct rlist *swap(struct rlist *lst1, struct rlist *lst2, struct rlist *head)
{
    struct rlist *prev1, *prev2, *next1, *next2;
    prev1 = head;
    prev2 = head;
    if (prev1 == lst1)
        prev1 = NULL;
    else
        while (prev1->next != lst1)
            prev1 = prev1->next;
    if (prev2 == lst2)
        prev2 = NULL;
    else
        while (prev2->next != lst2)
            prev2 = prev2->next;
    next1 = lst1->next;
    next2 = lst2->next;  
    if (lst2 == next1)
    {                    
        lst2->next = lst1;
        lst1->next = next2;
        if (lst1 != head)
            prev1->next = lst2;
    }
    else
    if (lst1 == next2)
    {
        lst1->next = lst2;
        lst2->next = next1;
        if (lst2 != head)
            prev2->next = lst2;
    }
    else
    {
        if (lst1 != head)
            prev1->next = lst2;
        lst2->next = next1;
        if (lst2 != head)
            prev2->next = lst1;
        lst1->next = next2;
    }

    if (lst1 == head)
        return(lst2);
    if (lst2 == head)
        return(lst1);
    else
        return(head);
}

struct rlist *get_tail(struct rlist *head)
{
//    printf("Entered tail search\n");
    struct rlist * tail = head;
    do {
        if (tail->next != NULL){
            tail = tail->next;
        }
    } while (tail->next != NULL);
//    printf("Exit from tail search\n");
    return tail;
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

struct rlist * rinit(bool random)
{
    struct rlist *lst;
    lst = (struct rlist*) malloc(sizeof(struct rlist));
    lst->item = additem(random);
    lst->next = NULL;
    return(lst);
}

struct rlist * rinsert(struct rlist *rlst, struct ROUTE *item)
{
    struct rlist *new, *p;
    new = (struct rlist*)malloc(sizeof(struct rlist));
    if (rlst->next != NULL)
    {
        p = rlst->next;
        rlst->next = new;
        new->item = item;
        new->next = p;
    }
    else
    {
        rlst->next = new;
        new->item = item;
        new->next = NULL;
    }
    return(new);
}

struct rlist * rdelete(struct rlist *lst, struct rlist *root)
{
    struct rlist *temp;
    temp = root;
    while (temp->next != lst)
    {
        temp = temp->next;
    }
    temp->next = lst->next;
    free(lst);
    return(temp);
}

struct rlist * VivaLaRHead(struct rlist *root, struct ROUTE *item)
{
    struct rlist *temp = (struct rlist*)malloc(sizeof(struct rlist));
    temp->next = root;
    temp->item = item;
    return(temp);
}

struct rlist * rdeletehead(struct rlist *root)
{
    struct rlist *temp;
    temp = root->next;
    free(root);
    return(temp);
}

void RPrintList(struct rlist *lst)
{
    struct rlist *p;
    p = lst;
    int iter = 0;
    printf("====================[ Current list ]===============================\n");
    do {
        printf("Structure #%d: \n"
               "  Name of location A is %s\n"
               "  Name of location B is %s\n"
               "  Route number = %d\n",
               iter + 1,
               p->item->name_a,
               p->item->name_b,
               p->item->route_number);
        p = p->next;
        iter++;
    } while (p != NULL);
    printf("====================[ Current list ]===============================\n");
}