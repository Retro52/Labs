//
// Created by Anton on 27.04.2021.
//

#ifndef HROMOVA_7_LIST_H
#define HROMOVA_7_LIST_H

struct list
{
    int field;
    struct list *next;
};

struct list * init(int a);

struct list * insert(struct list *lst, int field);

struct list * delete(struct list *lst, struct list *root);

struct list * VivaLaHead(struct list *root, int num);

struct list * deletehead(struct list *root);

void PrintList(struct list *lst, char *string);

#endif //HROMOVA_7_LIST_H
