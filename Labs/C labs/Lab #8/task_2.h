//
// Created by Anton on 14.05.2021.
//

#ifndef TEXT_EDITOR_TASK_2_H
#define TEXT_EDITOR_TASK_2_H
#include "myfunc.h"

struct team
{
    char name[200];
    char city[200];
    int players;
    long points;
    unsigned char status;
} team;

void task_2();

void swrite(const char * path);

void sdisplay(const char *path);

#endif //TEXT_EDITOR_TASK_2_H
