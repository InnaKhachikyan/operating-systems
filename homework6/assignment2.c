/*
 * Assignment 2. Struct Padding
Objective: To observe how padding is used in struct alignment and how it affects memory layout.
Task:
Create a struct in C with the following fields in the given order:
char a;
int b;
double c;
Use sizeof() to print the size of the struct and print the addresses of each field using the & operator.
Change the order of the fields (for example, place double first, then int, then char) and observe the size of the struct again.
Answer the following questions:
Does changing the order of fields reduce or increase the size of the struct? Why?
How is memory padding affecting the size of your struct?
Submission:
Include your C code.
Provide screenshots or the output of the program showing the size of the struct and the addresses of each field.
Write a short explanation of how rearranging fields affects the struct size.
*/

#include <stdio.h>

typedef struct str1 {
	char a;
	int b;
	double c;
} str1;

typedef struct str2 {
	double a;
	int b;
	char c;
} str2;

typedef struct str3 {
	int a;
	double b;
        char c;
} str3;	

int main(void) {
	struct str1 a_str = {'a', 42, 0.01};
	struct str2 b_str = {0.01, 42, 'c'};
	struct str3 c_str = {42, 0.01, 'c'};

	printf(" ***** STRUCT 1 ***** \n");
	printf("Size of the str1 is %lu \n", sizeof(str1));
	printf("Address of char a in str1: %p \n", &(a_str.a));
	printf("Address of int b in str1: %p \n", &(a_str.b));
	printf("Address of double c in str1: %p \n", &(a_str.c));

	printf(" ***** STRUCT 2 ***** \n");
	printf("Size of the str2 is %lu \n", sizeof(str2));
	printf("Address of double a in str1: %p \n", &(b_str.a));
	printf("Address of int b in str1: %p \n", &(b_str.b));
	printf("Address of char c in str1: %p \n", &(b_str.c));

	printf(" ***** STRUCT 3 ***** \n");
	printf("Size of the str3 is %lu \n", sizeof(str3));
	printf("Address of int a in str1: %p \n", &(c_str.a));
	printf("Address of double b in str1: %p \n", &(c_str.b));
	printf("Address of char c in str1: %p \n", &(c_str.c));

	return 0;
}
