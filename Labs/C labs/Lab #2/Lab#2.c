#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


//defining function which is responsible for first task (math operations)
void global_task_1();

//defining functions for each math task
void task_1_1();
void task_1_2();

//defining function which is responsible for second task (bitwise operations)
void global_task_2();

//defining functions for each bitwise task (packing and unpacking)
void task_2();

//defining function to check float/int variables given by user which takes text (question/request to user)
float input(char* text, float upper_bound, float lower_bound);
int input_int(char* text, int upper_bound, int lower_bound);

//quick sort function
void quicksort(int number[10000],int first,int last);

//find
void find(int number[10000], int len);

//defining arrays functions
int array(int idx, bool boost);
int array_2D(int idx, int jdx);

//defining useful variables - bool
bool main_bool;
bool task_1_bool;
bool task_2_bool;
bool program_exit;

//defining useful variables - bool
int a;
int b;
int c;
int d;

//fuction to clean console
void clear(); 

//random generators; bool boost - special bool var to increase chance of appearing 0  between another options
int randomize(int seed, bool boost);
int power(int x, int y);

//main funtion
int main(int argc, char *argv[]) {
	main_bool = true;
	task_1_bool = true;
	task_2_bool = true;
	program_exit = false;
	
	printf("Laboratory work #2\n  Orlenko Anton\n  KM-03\n  Variant 11\n\n");
	
	while(program_exit == false) {
		main_bool = true;
		
		while(main_bool == true ) {
			a = 0;
			task_1_bool = true;
			task_2_bool = true;
			
			printf("Main menu:\n 1. Single level array operations\n 2. Matrix operations\n 3. Clean console\n 4. Exit from program\n");
			
			a = input_int("", 4, 1);
			
			if(a == 1) {
				global_task_1();
				main_bool = false;
			} else{	
				if(a == 2) {
					global_task_2();
					main_bool = false;
					} else{
					if(a == 3) {
						main_bool = false;
						clear();
					} else{
						if(a == 4){
							main_bool = false;
							program_exit = true;
						} else{
							printf("ERROR! You can choose only programs 1 or 2\n");
						}
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
	while(task_1_bool == true){
		b = input_int("Single level array menu:\n 1. Calculate the maximum number of positive elements located between zeros\n 2. Arrange the array by fast sorting (Hoare method)\n 3. Clean console\n 4. Back do main menu\n * - Max array size = 10 000\n", 4, 1);
		if(b == 1){
			task_1_1();
		} else{
			if(b == 2){
				task_1_2();
			} else{
				if(b == 3){
					clear();
				} else{
					task_1_bool = false;
					main_bool = true;
				}
			}
		}
	}
}
//bitwise operations menu
void global_task_2(){
	while(task_2_bool == true){
		b = input_int("Matrix menu:\n 1. Calculate: 0.5*(A + A*) and 0.5*(A - A*)\n 2. Clean console\n 3. Back do main menu\n * - Max array size = 100x100\n", 3, 1);
		if(b == 1){
			task_2();
		} else{
			if(b == 2){
				clear();
			} else{
				if(b == 3){
					task_2_bool = false;
					main_bool = true;
				} 
			}
		}
	}
}
//packing operation function
void task_1_1(){
	int a,id, len_arr;
	len_arr = array(0, true);
	int arr[10000];
	for(id=1;id<=len_arr;id++){
		arr[id-1] = array(id, false);
	}
	printf("\n");
	for(id=0;id<89;id++){
		printf("-");
	}
	printf("\nArray: \n");
	for(a=0;a<len_arr;a++){
		printf("Arr[%d]=%d\n", a, arr[a]);
	}
	for(id=0;id<89;id++){
		printf("-");
	}
	printf("\n");
	find(arr, len_arr);
	for(id=0;id<89;id++){
		printf("-");
	}
	printf("\n");
}
//unpacking operation function
void task_1_2(){
	int a,id, len_arr;
	len_arr = array(0, false);
	int arr[10000];
	for(id=1;id<=len_arr;id++){
		arr[id-1] = array(id, true);
	}
	printf("\nArray before sorting:\n");
	for(id=0;id<89;id++){
		printf("-");
	}
	printf("\n");
	for(a=0;a<len_arr;a++){
		printf("Arr[%d]=%d\n", a, arr[a]);
	}
	for(id=0;id<89;id++){
		printf("-");
	}
	printf("\n");
	quicksort(arr, 0, len_arr - 1);
	printf("\nOrder of Sorted elements:\n");
	for(id=0;id<len_arr;id++){
		printf("Arr[%d]=%d\n", id, arr[id]);
	}
	printf("\n");
	for(id=0;id<89;id++){
		printf("-");
	}
	printf("\n");
}
//math function task 1 - area of trapezoid
void task_2(){
	int id, jd, n, m[100][100], t[100][100], r[100][100];
	n = array_2D(-1, 0);
	for(id=0;id<n;id++){
		for(jd=0;jd<n;jd++){
			m[id][jd] = array_2D(id, jd);
		}
	}
	printf("You have entered: \n");
	for(id=0;id<n;id++){
		printf("|");
		for(jd=0;jd<n;jd++){
			printf(" %d ", m[id][jd]);
		}
		printf("|\n");
	}
	for(id=0;id<n;id++){
		for(jd=0;jd<n;jd++){
			t[jd][id] = m[id][jd];
		}
	}
	printf("Transposed matrix: \n");
	for(id=0;id<n;id++){
		printf("|");
		for(jd=0;jd<n;jd++){
			printf(" %d ", t[id][jd]);
		}
		printf("|\n");
	}
	printf("0.5*(A + A*):\n");
	for(id=0;id<n;id++){
		for(jd=0;jd<n;jd++){
			r[id][jd] = 0.5*(m[id][jd] + t[id][jd]);
		}
	}
	for(id=0;id<n;id++){
		printf("|");
		for(jd=0;jd<n;jd++){
			printf(" %d ", r[id][jd]);
		}
		printf("|\n");
	}
	printf("0.5*(A - A*):\n");
	for(id=0;id<n;id++){
		for(jd=0;jd<n;jd++){
			r[id][jd] = 0.5*(m[id][jd] - t[id][jd]);
		}
	}
	for(id=0;id<n;id++){
		printf("|");
		for(jd=0;jd<n;jd++){
			printf(" %d ", r[id][jd]);
		}
		printf("|\n");
	}
}

int input_int(char* text, int upper_bound, int lower_bound){
    int err = 0;
    int res = 0;
    int error = 0;
    char chr;
    bool choose = true;
    while(choose == true) {
        printf("%s", text);
        error = scanf("%d", &res);
        while ((chr = getchar()) != '\n' && chr != EOF) {}
        if(error != 1){
       	printf("You eneted wrong type of variable\n");
        } else {
          if(res > upper_bound || res < lower_bound) {
           printf("The number cannot be higher than the specified number - %d - or lower than %d\n", upper_bound, lower_bound);
          } else {
            choose = false;
          }
        }
    }
    return  res;
}

float input(char* text, float upper_bound, float lower_bound) {
    float res = 0;
    int error = 0;
    char chr;
    bool choose = true;
    while(choose == true){
        printf("%s", text);
        error = scanf("%f", &res);
        while ((chr = getchar()) != '\n' && chr != EOF) {}
        if(error != 1){
        	printf("Wrong input, try again!\n");
		}
		else{
			if(res > upper_bound || res < lower_bound) {
           printf("The number cannot be higher than the specified number - %.2f - or lower than %.2f\n", upper_bound, lower_bound);
          } else {
			choose = false;
          }
		}
    }
    return  res;
}

int array(int idx, bool boosted){
	int rand, i, count, number[10000];
	char* text;
	if(idx == 0){
		count = input_int("Enter array size here: ", 10000, 1);
		printf("Entered size (floats are automaticly comverted to integer): %d\n", count);
		number[0] = count;
		rand = input_int("Type:\n 0 - Enter array elements\n 1 - Randomize array elements: ", 1, 0);
		if(rand==0){
			printf("Enter %d elements: \n", count);
			for(i=1;i<=count;i++){
				printf("Enter array[%d] element: ", i-1);
				number[i] = input("", 2147483647.0, -2147483647.0);
			}
		}else{
			for(i=1;i<=count;i++){
				int * pointer = &i;
				number[i] = randomize(* pointer, boosted);
			}
		}
	}
	return number[idx];
}

int array_2D(int idx, int jdx){
	int rand, i, j, count, number[100][100];
	if(idx == -1 && jdx == 0){
		count = input_int("Enter matrix size (n): ", 100, 1);
	//	number[0] = count;
		rand = input_int("Type:\n 0 - Enter array elements\n 1 - Randomize array elements: ", 1, 0);
		if(rand==0){
			printf("Enter %d*%d elements: \n", count, count);
			for(i=0;i<count;i++){
				for(j=0;j<count;j++){
					printf("Enter array[%d][%d] element: ", i, j);
					number[i][j] = input("", 2147483647.0, -2147483647.0);
				}
			}
		}else{
			for(i=0;i<count;i++){
				for(j=0;j<count;j++){
					int * pointer = &i;
					number[i][j] = randomize(* pointer, false);
				}
			}
		}
		return j;
	} else{
		return number[idx][jdx];
	}
}

void quicksort(int number[10000],int first,int last){
   int x, i, j, pivot, temp;
   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

   }
}

int randomize(int seed, bool boost) {
	int pbool;
	srand(seed);
	if(boost == true){
		pbool = randomize_bool(seed);
		if(pbool == 1){
			double res = power(rand(), sin(rand())) * power(-1, rand()/rand());
			return res;
		} else{
			return 0;
		}
	} else{
		double res = power(rand(), sin(rand())) * power(-1, rand()/rand());
		return res;
	}
}

int randomize_bool(int seed){
	srand(seed);
	int pow = (rand() % 2);
	return pow;
}

void find(int number[10000], int len){
	int pos[10000], zer[10000];
	//index vars
	int i = 0;
	int j = 0;
	//index for additional arrays
	int x = 0;
	int y = 0;
	//len to compare
	int a = 0;
	int b = 0;
	//double for loop to find indexes of every 0 and positive number and set them to array
	for(i=0;i<len;i++) {
		if(number[i] == 0){
			zer[x] = i;
			x++;
		} else{
			if(number[i] > 0){
				pos[y] = i;
				y++;
			}
		}		
	}
	//double for loop to check every 0 in list except the last one (not gonna work really fast - O(n*k))
	for(i=0;i<x;i++){
		a = 0;
		for(j=0;j<=y;j++){
			if(zer[i] < pos[j] && pos[j] < zer[i+1]){
				a++;
			}
			if(b < a){
				b = a;
			}
		}
	}
	printf("Max len = %d\n\n", b);

}

void clear(void) 
{
  system("cls||clear");
}

int power(int x, int y){
	int i;
	for(i=1;i<=y;i++){
		x *= x	;
	}
	return x;
}
