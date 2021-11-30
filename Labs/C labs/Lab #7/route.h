//
// Created by Anton on 28.04.2021.
//

#ifndef HROMOVA_7_ROUTE_H
#define HROMOVA_7_ROUTE_H

#include "myfunc.h"

struct ROUTE {
    char *name_a;
    char *name_b;
    int route_number;
};

struct rlist
{
    struct ROUTE *item;
    struct rlist *next;
};

struct ROUTE *additem(bool random);

struct rlist *get_tail(struct rlist *head);

struct rlist *swap(struct rlist *lst1, struct rlist *lst2, struct rlist *head);

void listprint(struct ROUTE *lst, int index);

struct rlist * rinit(bool random);

struct rlist * rinsert(struct rlist *rlst, struct ROUTE *item);

struct rlist * rdelete(struct rlist *lst, struct rlist *root);

struct rlist * VivaLaRHead(struct rlist *root, struct ROUTE *item);

struct rlist * rdeletehead(struct rlist *root);

void RPrintList(struct rlist *lst);

#endif //HROMOVA_7_ROUTE_H
