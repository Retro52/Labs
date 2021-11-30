#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//defining function which is responsible for first task (math operations)
void global_task_1();
//defining functions for each math task
float task_1();
float task_2();
//defining function which is responsible for second task (bitwise operations)
void global_task_2();
//defining functions for each bitwise task (packing and unpacking)
void task_2_1();
void task_2_2();
//defining function to check float/int variables given by user which takes text (question/request to user)
float check_for_task_1(char* text);
int check_for_task_2(char* text, int upper_bound);
//advanced random generator returning random integer number added just for fun
int random_number(int min_num, int max_num);
//defining useful variables - bool
bool task_choose_1;
bool task_choose_2;
bool task_choose_2_1;
bool program_exit;

//defining useful variables - bool
int a;
int b;
int c;
int d;
//integer responsible for random language 
int rand_lang;
//main funtion
int main(int argc, char *argv[]) {
	task_choose_1 = true;//bool fuction to use in whie cyckle for choosing global task
	task_choose_2 = true;//bool fuction to use in whie cyckle for choosing local task 1 for math function`s menu
	task_choose_2_1 = true;//bool fuction to use in whie cyckle for choosing local task 1 for bitwise function`s menu
	program_exit = false;//bool responsible for exiting from program throught menu
	rand_lang = random_number(0, 1);//generating random int 0 or 1 for language
	//printing welcome note
	printf("Laboratory work\n Orlenko Anton\n KM-03\n Variant 11\n\n");
	//global while cyckle for main menu and program exit
	while(program_exit == false) {
		task_choose_1 = true;//row for refreshing variable value
		//main menu infinite cyckle
		while(task_choose_1 == true ) {
			a = 0;//a - variable responsible for integer entered by user to choose task from main menu
			task_choose_2 = true;//row for refreshing variable value
			task_choose_2_1 = true;//row for refreshing variable value
			printf("Main menu:\n 1. Math functions\n 2. Bitwise operations\n 3. Exit from program\n");//main menu text
			scanf("%i", &a);//geting value entered by user to choose task
			fflush(stdin);//writing buffer values preventing errors and bugs
			//task 1 menu - math function
			if(a == 1) {
				global_task_1();
				task_choose_1 = false;
			}
			//checking if a is not 1
			else{	
				//task 2 local menu - bitwise operations	
				if(a == 2) {
					global_task_2();
					task_choose_1 = false;
					}
				//checking if a is not 1 or 2
				else{
					//exit from program command
					if(a == 3) {
						task_choose_1 = false;
						program_exit = true;
					}
					//else remained for errors (NUMBER IS NOT 1 OR 2 OR 3)
					else{
						printf("ERROR! You can choose only programs 1 or 2\n");
					}
				}
			}
		}
	}
	system("pause");
	return 0;
}
//Math operations task 
void global_task_1(){
	while(task_choose_2 == true) {
		printf("Math functions menu:\n 1. Area of traoezoid\n 2. Area of rhombus\n 3. Exit to main menu\n");
		scanf("%i", &c);
		fflush(stdin);
		if(c == 1) {
			float result_1 = task_1();
			printf("Area of trapezoid = %.2f\n\n", result_1);
		}
		else{
			if(c == 2) {
				float result_2 = task_2();
				printf("Area of this rhombus = %.2f\n\n", result_2);
			}
			else{
				if(c == 3) {
					task_choose_2 = false;
				}
				else{
					printf("ERROR! You can choose only programs 1 or 2\n");
				}
			}
		}
	}
}
//bitwise operations menu
void global_task_2(){
	while(task_choose_2_1 == true ) {
		printf("Bitwise operations menu:\n 1. Packing operation\n 2. Unpacking operation\n 3. Exit to main menu\n");
		scanf("%i", &d);
		fflush(stdin);
		if(d == 1) {
			task_2_1();
		}
		else{		
			if(d == 2) {
				task_2_2();
				}
			else{
				if(d == 3) {
					task_choose_2_1	 = false;
					task_choose_1 = true;
				}
				else{
					printf("ERROR! You can choose only programs 1 or 2\n");
				}
			}
		}
	}
}
//packing operation function
void task_2_1(){
	int c;//channel number
	int u;//device number
	int e;//state code
	int b;//sign of device occupancy
	unsigned int UnitStateWord;
	c = check_for_task_2("Enter channel number(0-7): ", 7);
	u = check_for_task_2("Enter device number (0-31): ", 31);
	e = check_for_task_2("Enter state code (0-63): ", 63);
	b = check_for_task_2("Enter sign of device occupancy (0/1): ", 1);
	UnitStateWord = ((unsigned int) c & 0x07) << 13;
	UnitStateWord |= ((unsigned int) u & 0x1F) << 8;
	UnitStateWord |= ((unsigned int) e & 0x3F) << 2;
	UnitStateWord |= ((unsigned int) 0 & 1) << 1;
	UnitStateWord |= ((unsigned int) b & 1) << 0;
	printf("\nDevice situation = %04x\n", UnitStateWord);
}
//unpacking operation function
void task_2_2(){
	int c;
	int u;
	int e;
	int b;
	unsigned int UnitStateWord;
	bool proverOCHKA = true;
	while(proverOCHKA == true) {
		printf("Enter device code situation (Heximal number between 0 and 0xFFFD): ");
		scanf("%x", &UnitStateWord);
		if(0 <= UnitStateWord &&  UnitStateWord <= 0xFFFD){
			proverOCHKA = false;
		}
		else{
			printf("The number cannot be higher than the specified number - 0xFFFD - or lower than zero\n");
		}
	}
	c = (UnitStateWord >> 13) & 0x07;
	u = (UnitStateWord >> 8) & 0x1F;
	e = (UnitStateWord >> 2) & 0x3F;
	b = UnitStateWord & 1;
	putchar('\n');
	printf("Channel number code = %d\n", c);
	printf("Device number code = %d\n", u);
	printf("State code = %d\n", e);
	printf("Sign of device occupancy = %d\n\n", b);
}
//math function task 1 - area of trapezoid
float task_1(){
	float f1;
	float f2;
	bool t1b = true;
	bool t1b2 = true;
	while(t1b == true) {
		f1 = check_for_task_1("Enter midsegment`s length: ");
		if(f1 > 0) {
			t1b = false;
		}
		else{
			printf("Length can`t be below 0\n");
		}

	}
	while(t1b2 == true) {
		f2 = check_for_task_1("Enter midsegment`s length: ");
		if(f2 > 0) {
			t1b2 = false;
		}
		else{
			printf("Length can`t be below 0\n");
		}

	}
	return f1*f2;
}
//math function task 2 - area of rhombus
float task_2(){
	float f3;
	float f4;
	bool t2b = true;
	bool t2b2 = true;
	while(t2b == true) {
		f3 = check_for_task_1("Enter first diagonal length: ");
		if(f3 > 0) {
			t2b = false;
		}
		else{
			printf("Wrong number, try again\n");
		}

	}
	while(t2b2 == true) {
		f4 = check_for_task_1("Enter second diagonal length: ");
		if(f4 > 0) {
			t2b2 = false;
		}
		else{
			printf("Wrong number, try again\n");

		}
	}
	return 0.5*f3*f4;
}

//defining function to check float variables given by user which takes text (question/request to user)
float check_for_task_1(char* text) {
    float res = 0;
    int error = 0;
    char term;
    bool choose = true;
    while(choose == true){
        printf("%s", text);
        error = scanf("%f%c", &res, &term);
        fflush(stdin);
        if(error != 2 || term != '\n'){
        	printf("Wrong input, try again!\n");
		}
		else{
			choose = false;
		}
    }
    return  res;
}

//defining function to check float/int variables given by user which takes text (question/request to user) and upper bound for limiting values whick can be entered by user
int check_for_task_2(char* text, int upper_bound){
    int res = 0;
    int error = 0;
    char term;
    bool choose = true;
    while(choose == true){
        printf("%s", text);
        error = scanf("%d%c", &res, &term);
        fflush(stdin);
        if(error != 2 || term != '\n'){
        	printf("You eneted wrong type of variable\n");
		}
		else{
			if(res > upper_bound || res < 0){
				printf("The number cannot be higher than the specified number - %d - or lower than zero\n", upper_bound);
			}
			else{
				choose = false;
			}
		}
    }
    return  res;
}
//random generator
int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } 
	else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}
