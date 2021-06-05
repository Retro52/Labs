//
// Created by Anton on 14.05.2021.
//

#include "task_2.h"

void sdisplay(const char *path) {
    FILE *fPtr;
    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("Error during reading a file");
        return;
    }
    int count = 0;
    fseek(fPtr, 0, SEEK_SET);
    puts("           |   NAME   |   CITY   | PLAYERS |  POINTS  |  EXISTS  |");

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        puts("           +----------+----------+---------+----------+----------+");
        printf("Srtuct #%d: |%10s|%10s|%9d|%10ld|%10d|\n", count + 1,
               team.name,
               team.city,
               team.players,
               team.points,
               team.status);
        count++;
    }
    puts("           +----------+----------+---------+----------+----------+");
    fclose(fPtr);
}

void swrite(const char *path) {
    char str[100];
    char temp[20];
    bool pass = true;
    FILE *fPtr, *fTmp;
    struct team temporary;
    strcpy(temp, "temp.bin");
    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("Error during reading a file\n");
        return;
    }
    fTmp = fopen(temp, "wb");

    for (int i = 0; i < 2; ++i) {
        puts("Enter a team name: ");
        fflush(stdin);
        fgets(str, 100, stdin);
        edit_str(str);
        strcpy(team.name, str);

        puts("Enter a team city: ");
        fflush(stdin);
        fgets(str, 100, stdin);
        edit_str(str);
        strcpy(team.city, str);

        team.players = input_int("Enter players number: ", MAX_INPUT, 1);
        team.points = input_int("Enter team points: ", MAX_INPUT, -MAX_INPUT);
        team.status = 1;

        fwrite(&team, sizeof(struct team), 1, fTmp);
    }

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        strcpy(temporary.name, team.name);
        strcpy(temporary.city, team.city);
        temporary.status = team.status;
        temporary.players = team.players;
        temporary.points = team.points;
        fwrite(&temporary, sizeof(struct team), 1, fTmp);
    }
    fclose(fTmp);
    fclose(fPtr);
    remove(path);
    rename(temp, path);
}

void sdelete(const char *path) {
    struct team temporary;
    FILE *fPtr, *fTmp;
    char temp[20];
    int count = 0;

    strcpy(temp, "temp.bin");

    fTmp = fopen(temp, "wb");

    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("File not found :-(");
        return;
    }

    puts("           |   NAME   |   CITY   | PLAYERS |  POINTS  |  EXISTS  |");

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        puts("           +----------+----------+---------+----------+----------+");
        printf("Srtuct #%d: |%10s|%10s|%9d|%10ld|%10d|\n", count + 1,
               team.name,
               team.city,
               team.players,
               team.points,
               team.status);
        count++;
    }
    puts("           +----------+----------+---------+----------+----------+");
    fseek(fPtr, 0, SEEK_SET);
    int delete = input_int("Pick a structure to delete: ", count, 1);

    count = 0;

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        count++;
        if (count == delete)
        {
            temporary.status = 0;
        } else
        {
            temporary.status = team.status;
        }
        strcpy(temporary.name, team.name);
        strcpy(temporary.city, team.city);
        temporary.players = team.players;
        temporary.points = team.points;
        fwrite(&temporary, sizeof(struct team), 1, fTmp);
    }
    fclose(fTmp);
    fclose(fPtr);
    remove(path);
    rename(temp, path);
}

void srestore(const char *path) {
    struct team temporary;
    FILE *fPtr, *fTmp;
    char temp[20];
    int count = 0;

    strcpy(temp, "temp.bin");

    fTmp = fopen(temp, "wb");

    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("File not found :-(");
        return;
    }

    puts("           |   NAME   |   CITY   | PLAYERS |  POINTS  |  EXISTS  |");

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        puts("           +----------+----------+---------+----------+----------+");
        printf("Srtuct #%d: |%10s|%10s|%9d|%10ld|%10d|\n", count + 1,
               team.name,
               team.city,
               team.players,
               team.points,
               team.status);
        count++;
    }
    puts("           +----------+----------+---------+----------+----------+");
    fseek(fPtr, 0, SEEK_SET);
    int restore = input_int("Pick a structure to restore: ", count, 1);

    count = 0;

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        count++;
        if (count == restore)
        {
            temporary.status = 1;
        } else
        {
            temporary.status = team.status;
        }
        strcpy(temporary.name, team.name);
        strcpy(temporary.city, team.city);
        temporary.players = team.players;
        temporary.points = team.points;
        fwrite(&temporary, sizeof(struct team), 1, fTmp);
    }
    fclose(fTmp);
    fclose(fPtr);
    remove(path);
    rename(temp, path);
}

void ssavearchive(const char *path) {
    struct team temporary;
    FILE *fPtr, *fTmp;
    char temp[50];
    int count = 0;
    sprintf (temp, "%s_archived.bin", path);

    fTmp = fopen(temp, "wb");

    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("File not found :-(");
        return;
    }
    fseek(fPtr, 0, SEEK_SET);

    count = 0;

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        count++;
        if (team.status != 0)
        {
            strcpy(temporary.name, team.name);
            strcpy(temporary.city, team.city);
            temporary.players = team.players;
            temporary.points = team.points;
            temporary.status = 1;
            fwrite(&temporary, sizeof(struct team), 1, fTmp);
        } else
        {
            continue;
        }
    }
    printf("Copy named %s saved successfully!\n", temp);
    fclose(fTmp);
    fclose(fPtr);
}

void spoints(const char *path) {
    struct team temporary;
    FILE *fPtr, *fTmp;
    char temp[50];
    int count = 0;
    int limit = input_int("Enter a points limit: ", MAX_INPUT, -MAX_INPUT);
    strcpy(temp, "temp.bin");
    fTmp = fopen(temp, "wb");

    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("File not found :-(");
        return;
    }

    fseek(fPtr, 0, SEEK_SET);

    count = 0;

    while (fread(&team, sizeof(struct team), 1, fPtr))
    {
        count++;
        if (team.points < limit)
        {
            strcpy(temporary.name, team.name);
            strcpy(temporary.city, team.city);
            temporary.players = team.players;
            temporary.points = team.points;
            temporary.status = 0;
            fwrite(&temporary, sizeof(struct team), 1, fTmp);
        } else
        {
            strcpy(temporary.name, team.name);
            strcpy(temporary.city, team.city);
            temporary.players = team.players;
            temporary.points = team.points;
            temporary.status = team.status;
            fwrite(&temporary, sizeof(struct team), 1, fTmp);
        }
    }
    printf("Structures deleted & saved successfully!\n");
    fclose(fTmp);
    fclose(fPtr);
    remove(path);
    rename(temp, path);
}

void ssaveas(const char *path, const char *new) {
    FILE *fPtr;

    if ((fPtr = fopen(path, "rb")) == NULL) {
        puts("File not found :-(");
        return;
    }
    fclose(fPtr);
    rename(path, new);
    printf("File successfully saved with name %s!\n", new);
}

void task_2() {
    bool task = true;
    bool file = true;
    char fname[100];
    FILE *fp = NULL;
    while (file) {
        printf("Please, enter a binary file name you would like to open: ");
        fflush(stdin);
        fgets(fname, 100, stdin);
        edit_str(fname);
        if ((fp = fopen(fname, "rb")) == NULL) {
            int choice = input_int("This file doesn`t exist."
                                   " Would you like to create a new one? \n"
                                   "1 - yes\n"
                                   "10 - back to previous menu\n"
                                   "11 - enter another filename\n",
                                   11, 0);
            if (choice == 1) {
                fp = fopen(fname, "ab");
                puts("File successfully created\n");
                file = false;
                fclose(fp);
            }
            else if (choice == 10)
            {
                return;
            }
            else if (choice == 11)
            {
                continue;
            } else
            {
                printf("Unacceptable code\n");
            }
        } else {
            file = false;
            fclose(fp);
            break;
        }
    }
    while (task) {
        int choice = input_int("Subtask 2 menu\n"
                               "  1. Open another file\n"
                               "  2. Display current file\n"
                               "  3. Write 2 structures to the beginning\n"
                               "  4. Delete structures\n"
                               "  5. Restore structures\n"
                               "  6. Save copy with archiving\n"
                               "  7. Delete all elements with number of points, lower, than given\n"
                               "  8. Save this file as...\n"
                               "  9. Clear console\n"
                               "  10. Back to Main Menu\n", 10, 1);
        switch (choice) {
            case 1:
                printf("Enter name of file you`d like to open: ");
                fflush(stdin);
                char test[30];
                fgets(test, 30, stdin);
                edit_str(test);

                FILE *ftest;

                if ((ftest = fopen(test, "rb")) != NULL)
                {
                    strcpy(fname, test);
                    fclose(ftest);
                } else
                {
                    printf("This file doesn`t exist");
                }
                break;
            case 2:
                sdisplay(fname);
                break;
            case 3:
                swrite(fname);
                break;
            case 4:
                sdelete(fname);
                break;
            case 5:
                srestore(fname);
                break;
            case 6:
                ssavearchive(fname);
                break;
            case 7:
                spoints(fname);
                break;
            case 8:
                fflush(stdin);
                char new[50];
                printf("Enter a name for this file: ");
                fgets(new, 50, stdin);
                edit_str(new);
                ssaveas(fname, new);
                strcpy(fname, new);
                break;
            case 9:
                clear();
                break;
            case 10:
                task = false;
                break;
            default:
                break;
        }
    }
}