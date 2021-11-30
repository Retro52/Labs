//
// Created by Anton on 14.05.2021.
//

#include "task_1.h"

void create() {
    printf("Enter new file name (20 chars max): ");
    char name[20];
    scanf("%s", name);
    FILE *new;
    if ((new = fopen(name, "r"))) {
        fclose(new);
        printf("File already exists\n");
    } else {
        if ((new = fopen(name, "w"))) {
            fclose(new);
            printf("File '%s' successfully created\n", name);
        } else {
            printf("Couldn`t create a file\n");
        }
    }
}

void line(FILE *fp, int cur_line, int total_lines, char *fname) {
    char ch;
    fseek(fp, 0, SEEK_SET);
    int count = 0;
    if (cur_line == 0) {
        puts("========[FILE BEGINNING]=======");
    } else {
        puts("===============================");
    }
    while (count != cur_line) {
        ch = (char) getc(fp);
        if (ch == '\n') {
            count++;
        }
    }
    ch = (char) fgetc(fp);
    if (ch == EOF && total_lines == 0) {
        //set memory for input string
        char str[BUFFER_SIZE];
        //closing current file
        fclose(fp);
        //cleaning buffers
        fflush(stdin);
        fflush(stdout);
        //re-opening file to write
        fp = fopen(fname, "w");
        //user prints
        printf("\n==========[File is empty]==========\n\n"
               "Enter a string to fill a file with something: ");
        fgets(str, BUFFER_SIZE, stdin);
        fflush(stdin);
        edit_str(str);
        //preparing to write data to file
        fseek(fp, 0, SEEK_SET);
        fwrite(str, sizeof(char), (int) strlen(str), fp);
        //finishing writing
        fclose(fp);
        //re-opening file to continue operation
        fp = fopen(fname, "r");
        fseek(fp, 0, SEEK_SET);
        ch = (char) fgetc(fp);
    }
    while (ch != '\n' && ch != EOF) {
        putchar(ch);
        ch = (char) fgetc(fp);
    }
    if (cur_line == total_lines) {
        puts("\n==========[FILE ENDS]==========");
    } else {
        puts("\n===============================");
    }
}

void display() {
    char fname[100], ch;
    FILE *fp;
    printf("Enter the Name of File (100 char max.): ");
    scanf("%s", fname);
    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Error Occurred while Opening the File!\n");
    } else {
        int cur_line = 0;
        int total_lines = 0;
        fseek(fp, 0, SEEK_SET);
        while (!feof(fp)) {
            ch = (char) fgetc(fp);
            if (ch == '\n') {
                total_lines++;
            }
        }
        fseek(fp, 0, SEEK_SET);
        bool active = true;
        ch = (char) fgetc(fp);
        if (ch == EOF) {
            printf("\n==========[File is empty]==========\n\n");
            fflush(stdout);
            fclose(fp);
            return;
        }
        while (ch != '\n' && ch != EOF) {
            putchar(ch);
            ch = (char) fgetc(fp);
        }
        while (active) {
            clear();
            printf("File '%s':\n", fname);
            printf("Line #%d:\n", cur_line + 1);
            line(fp, cur_line, total_lines, fname);
            int choice = input_int("\n"
                                   "  1. Move one line up\n"
                                   "  2. Move one line down\n"
                                   "  3. Back to previous menu\n", 3, 1);
            switch (choice) {
                case 1:
                    if (cur_line == 0) {
                        puts("\nThat`s a beginning of the file\n");
                        break;
                    } else {
                        cur_line--;
                        break;
                    }
                case 2:
                    if (cur_line == total_lines) {
                        printf("That`s an end of the file anyway\n");
                        break;
                    } else {
                        cur_line++;
                        break;
                    }
                case 3:
                    active = false;
                    fclose(fp);
                    break;
                default:
                    break;
            }
        }
    }
}

int replace_line(const char *path, const int line) {
    FILE *fPtr;
    FILE *fTemp;

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];
    char temp_name[20];
    strcpy(temp_name, "replace.tmp");
    int count;

    /* Remove extra new line character from stdin */
    fflush(stdin);

    printf("Replace '%d' line with: ", line);
    fgets(newline, BUFFER_SIZE, stdin);


    /*  Open all required files */
    fPtr = fopen(path, "r");
    fTemp = fopen(temp_name, "w+");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL) {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return -1;
    }

    printf("File 1 %p File 2 %p\n", fPtr, fTemp);
    /*
     * Read line from source file and write to destination
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
        count++;

        /* If current line is line to replace */
        if (count == line)
            fputs(newline, fTemp);
        else
            fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    int err_1;
    if ((err_1 = remove(path)) == 0) {
        printf("Successfully removed a file\n");
    } else {
        printf("Err = %d\n", err_1);
        puts("Error! Step 1 - couldnt delete a file path\n");
        return -1;
    }

    /* Delete original source file */

    if ((err_1 = rename(temp_name, path)) == 0) {
        puts("Successfully renamed a file\n");
    } else {
        printf("Err = %d\n", err_1);
        puts("Error! Step 2 - couldnt rename a file path\n");
        return -1;
    }
    return 0;
    /* Rename temporary file as original file */
}

int delete_line(const char *path, const int line) {
    FILE *fPtr;
    FILE *fTemp;

    char buffer[BUFFER_SIZE];
    char temp_name[20];
    strcpy(temp_name, "delete.tmp");
    int count;

    /* Remove extra new line character from stdin */
    fflush(stdin);

    /*  Open all required files */
    fPtr = fopen(path, "r");
    fTemp = fopen(temp_name, "w+");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL) {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return -1;
    }

    /*
     * Read line from source file and write to destination
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {
        count++;

        /* If current line is line to replace */
        if (count == line)
            continue;
        fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    int err_1;
    if ((err_1 = remove(path)) == 0) {
        printf("Successfully removed a file\n");
    } else {
        printf("Err = %d\n", err_1);
        puts("Error! Step 1 - couldnt delete a file path\n");
//        system
        return -1;
    }

    /* Delete original source file */

    if ((err_1 = rename(temp_name, path)) == 0) {
        puts("Successfully renamed a file\n");
    } else {
        printf("Err = %d\n", err_1);
        puts("Error! Step 2 - couldnt rename a file path\n");
        return -1;
    }
    return 0;

    /* Rename temporary file as original file */
}

int insert_line(const char *path, const int line) {
    FILE *fPtr;
    FILE *fTemp;

    char buffer[BUFFER_SIZE], str[BUFFER_SIZE];
    char temp_name[20];
    int count;

    strcpy(temp_name, "insert.tmp");

    puts("Enter some text for new string: ");
    fgets(str, BUFFER_SIZE, stdin);

    edit_str(str);

    /*  Open all required files */
    fPtr = fopen(path, "r");
    fTemp = fopen(temp_name, "w+");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL) {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        return -1;
    }

    /*
     * Read line from source file and write to destination
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL) {

        count++;
        /* If current line is line to replace */
        fputs(buffer, fTemp);
        if (count == line) {
            if (buffer[strlen(buffer) - 1] != '\n' || buffer[strlen(buffer) - 1] == EOF) {
                fputc('\n', fTemp);
            }
            fputs(str, fTemp);
            fputc('\n', fTemp);
        }
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    int err_1;
    if ((err_1 = remove(path)) == 0) {
        printf("Successfully removed a file\n");
    } else {
        printf("Err = %d\n", err_1);
        puts("Error! Step 1 - couldnt delete a file path\n");
//        system
        return -1;
    }

    /* Delete original source file */

    if ((err_1 = rename(temp_name, path)) == 0) {
        puts("Successfully renamed a file\n");
    } else {
        printf("Err = %d\n", err_1);
        puts("Error! Step 2 - couldnt rename a file path\n");
        return -1;
    }
    return 0;

    /* Rename temporary file as original file */
}

void edit() {
    char fname[100], ch, res;
    FILE *fp;
    printf("Enter the Name of File (100 char max.): ");
    fgets(fname, 100, stdin);
    fname[strlen(fname) - 1] = '\0';
    if ((fp = fopen(fname, "r")) == NULL) {
        printf("Error Occurred while Opening the File!\n");
    } else {
        int cur_line = 0;
        int total_lines = 0;
        fseek(fp, 0, SEEK_SET);
        while (!feof(fp)) {
            ch = (char) fgetc(fp);
            if (ch == '\n') {
                total_lines++;
            }
        }
        fseek(fp, 0, SEEK_SET);
        bool active = true;
        ch = (char) fgetc(fp);
        if (ch == EOF) {
            //set memory for input string
            char str[BUFFER_SIZE];
            //closing current file
            fclose(fp);
            //cleaning buffers
            fflush(stdin);
            fflush(stdout);
            //re-opening file to write
            fp = fopen(fname, "w");
            //user prints
            printf("\n==========[File is empty]==========\n\n"
                   "Enter a string to fill a file with something: ");
            fgets(str, BUFFER_SIZE, stdin);
            edit_str(str);
            //preparing to write data to file
            fseek(fp, 0, SEEK_SET);
            fwrite(str, sizeof(char), (int) strlen(str), fp);
            //finishing writing
            fclose(fp);
            //re-opening file to continue operation
            fp = fopen(fname, "r");
            fseek(fp, 0, SEEK_SET);
            ch = (char) fgetc(fp);
        }
        while (ch != '\n' && ch != EOF) {
            putchar(ch);
            ch = (char) fgetc(fp);
        }
        fclose(fp);
        while (active) {
            if ((fp = fopen(fname, "r")) == NULL) {
                printf("Error Occurred while Opening the File!\n");
                break;
            } else {
                clear();
                printf("File '%s':\n", fname);
                printf("Line #%d:\n", cur_line + 1);
                line(fp, cur_line, total_lines, fname);
                int choice = input_int("\n"
                                       "  1. Move one line up\n"
                                       "  2. Move one line down\n"
                                       "  3. Replace current line (with new string)\n"
                                       "  4. Delete current line\n"
                                       "  5. Add a new line after current\n"
                                       "  6. Back to previous menu\n", 6, 1);
                switch (choice) {
                    case 1:
                        if (cur_line == 0) {
                            break;
                        } else {
                            cur_line--;
                            break;
                        }
                    case 2:
                        if (cur_line == total_lines) {
                            break;
                        } else {
                            cur_line++;
                            break;
                        }
                    case 3:
                        fclose(fp);
                        res = (char) replace_line(fname, cur_line + 1);
                        if (res == -1) {
                            printf("Couldn`t replace the line\n");
                        }
                        break;
                    case 4:
                        fclose(fp);
                        res = (char) delete_line(fname, cur_line + 1);
                        if (res != -1) {
                            if (total_lines > 0) {
                                total_lines--;
                            }
                            if (cur_line > 0)
                                cur_line--;
                        } else {
                            puts("Some kind of error was occured. Probably, reading error\n");
                        }
                        break;
                    case 5:
                        fclose(fp);
                        res = (char) insert_line(fname, cur_line + 1);
                        if (res != -1)
                            total_lines++;
                        else
                            puts("Some kind of error was occured. Probably, reading error\n");
                        break;
                    case 6:
                        active = false;
                        fclose(fp);
                        break;
                    default:
//                        calculate(fp);
                        break;
                }
            }
        }
    }
}

void delete() {
    char name[20];
    int del;
    printf("Enter file name to delete (20 chars max.): ");
    scanf("%s", name);
    del = remove(name);
    if (!del) {
        printf("File deleted successfully\n");
    } else {
        printf("Couldn`t delete a file\n");
    }
}

void move() {
    char from[100], to[100];
    int words;
    FILE *fFrom, *fTo;
    fflush(stdin);
    puts("Enter a file name to copy from: ");
    fgets(from, 100, stdin);
    puts("Enter a file name to copy to: ");
    fgets(to, 100, stdin);
    edit_str(from);
    edit_str(to);
    fFrom = fopen(from, "r");
    fTo = fopen(to, "w");
    if (fFrom == NULL || fTo == NULL) {
        puts("One of the files does not exist\n");
        return;
    }
    char buffer[BUFFER_SIZE];
    while ((fgets(buffer, BUFFER_SIZE, fFrom)) != NULL) {
        words = calculate(buffer);
        if (words == 1) {
            fputs(buffer, fTo);
        }
    }
    fclose(fFrom);
    fclose(fTo);
}

int calculate(const char *s) {
    int count = 1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' && s[i + 1] != ' ')
            count++;
    }
    return count;
}

int count() {
    char fname[100], ch;
    int len = 0, idx = 1, cons = 0, idx_return;
    FILE *fp;
    fflush(stdin);
    puts("Enter a file name to count words len in: ");
    fgets(fname, 100, stdin);
    edit_str(fname);
    fp = fopen(fname, "r");
    char consonants[100];
    strcpy(consonants, "qwrtpsdfghjklzxcvbnmQWRTPSDFGHJKLZXCVBNM\0");
    if (!fp) {
        puts("File not found!\n");
        return -1;
    }
    while ((ch = (char) fgetc(fp)) != EOF) {
        if (ch != ' ' && ch != '\0' && ch != '\n' && ch != EOF && ch != '\t') {
            for (int i = 0; consonants[i] != '\0'; ++i) {
                if (ch == consonants[i]) {
                    len++;
                    break;
                }
            }
        } else {
            if (len > cons) {
                cons = len;
                idx_return = idx;
            }
            idx++;
            len = 0;
        }
    }
    if (ch != ' ' && ch != '\0' && ch != '\n' && ch != EOF && ch != '\t') {
        for (int i = 0; consonants[i] != '\0'; ++i) {
            if (ch == consonants[i]) {
                len++;
                break;
            }
        }
    } else {
        if (len >= cons) {
            cons = len;
            idx_return = idx;
        }
        idx++;
        len = 0;
    }
    fclose(fp);
    return idx_return;
}

void task_1() {
    bool task = true;
    int cons;
    while (task) {
        int choice = input_int("Subtask 1 menu\n"
                               "  1. Create a new file\n"
                               "  2. Display a file\n"
                               "  3. Edit a file\n"
                               "  4. Delete a file\n"
                               "  5. Rename file\n"
                               "  6. Move lines with only one word in it to another file\n"
                               "  7. Find word index with biggest number of consonants in file\n"
                               "  8. Show files in current directory\n"
                               "  9. Clear console\n"
                               "  10. Back to Main Menu\n", 10, 1);
        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                edit();
                break;
            case 4:
                delete();
                break;
            case 5:
                printf("Enter a file name you want to rename: ");
                fflush(stdin);
                char before[100];
                fgets(before, 100, stdin);
                puts("Enter new file name: ");
                char after[100];
                fgets(after, 100, stdin);
                edit_str(before);
                edit_str(after);
                int err = rename(before, after);
                if (!err)
                    printf("File %s successfully renamed to %s\n", before, after);
                else
                    puts("Couldn't rename a file :-(\n");
                break;
            case 6:
                move();
                break;
            case 7:
                cons = count();
                printf("Word index with highest number of consonants is %d\n", cons);
                break;
            case 8:
                system("ls -l");
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