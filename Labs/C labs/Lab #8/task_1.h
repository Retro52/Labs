//
// Created by Anton on 14.05.2021.
//

#include <stdio.h>
#include "myfunc.h"
#include "stdlib.h"

#ifndef TEXT_EDITOR_TASK_1_H
#define TEXT_EDITOR_TASK_1_H

#define BUFFER_SIZE 1000

void task_1();

void task_2();

void create();

void display();

void edit();

void line(FILE *fp, int cur_line, int total_lines, char *fname);

int replace_line(const char *path, int line);

int delete_line(const char *path, int line);

int insert_line(const char *path, int line);

int calculate(const char *string);

void delete();

#endif //TEXT_EDITOR_TASK_1_H
