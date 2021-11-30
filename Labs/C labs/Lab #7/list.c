//
// Created by Anton on 27.04.2021.
//

#include "list.h"
#include "stdio.h"
#include "stdlib.h"

struct list * init(int a)
{
    struct list *lst;
    lst = (struct list*) malloc(sizeof(struct list));
    lst->field = a;
    lst->next = NULL;
    return(lst);
}

struct list * insert(struct list *lst, int field)
{
    struct list *new, *p;
    new = (struct list*)malloc(sizeof(struct list));
    if (lst->next != NULL)
    {
        p = lst->next;
        lst->next = new;
        new->field = field;
        new->next = p;
    }
    else
    {
        lst->next = new;
        new->field = field;
        new->next = NULL;
    }
    return(new);
}

struct list * delete(struct list *lst, struct list *root)
{
    struct list *temp;
    temp = root;
    while (temp->next != lst)
    {
        temp = temp->next;
    }
    temp->next = lst->next;
    free(lst);
    return(temp);
}

struct list * VivaLaHead(struct list *root, int num)
{
    struct list *temp = (struct list*)malloc(sizeof(struct list));
    temp->next = root;
    temp->field = num;
    return(temp);
}

struct list * deletehead(struct list *root)
{
    struct list *temp;
    temp = root->next;
    free(root); 
    return(temp); // новый корень списка
}

void PrintList(struct list *lst, char *string)
{
    struct list *p;
    p = lst;
    int iter = 0;
    printf("====================[ %s ]===============================\n", string);
    do {
        printf("List[%d]: %d\n",iter, p->field);
        p = p->next;
        iter++;
    } while (p != NULL);
    printf("===================================================================\n");
}