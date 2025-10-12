/*
 * Assignment 1. Understanding Data Alignment in C
Objective: To understand how different data types are aligned in memory and the concept of data alignment.
Task:
Write a C program where you declare variables of the following types: int, char, double, and short.
Use sizeof() to print the size of each data type.
Print the addresses of each variable using the & operator.
Observe and compare the addresses of these variables.
Expected Output: Your program should show that variables are aligned to specific boundaries based on their types.
Submission:
Include your C code.
Write a short explanation of what you observed regarding how variables of different types are aligned in memory.
*/

#include <stdio.h>
#include <stdint.h>

int main(void) {

	int type_int = 42;
	char type_char = 'i';
	double type_double = 0.0000001;
	short type_short = 23;

	printf("Size of the int type is: %lu bytes\n", sizeof(type_int));
	printf("Size of the char type is: %lu bytes\n", sizeof(type_char));
	printf("Size of the double type is: %lu bytes\n", sizeof(type_double));
	printf("Size of the short type is: %lu bytes\n", sizeof(type_short));

	printf("Address of the int type is: %p\n", &type_int);
	printf("Address of the char type is: %p\n", &type_char);
	printf("Address of the double type is: %p\n", &type_double);
	printf("Address of the short type is: %p\n", &type_short);


	if((size_t)&type_int % sizeof(int) == 0) {
		printf("Int is aligned to multiple of %lu \n", sizeof(int));
	}
	if((size_t)&type_char % sizeof(char) == 0) {
		printf("Char is aligned to multiple of %lu \n", sizeof(char));
	}
	if((size_t)&type_double % sizeof(double) == 0) {
		printf("Double is aligned to multiple of %lu \n", sizeof(double));
	}
	if((size_t)&type_short % sizeof(short) == 0) {
		printf("Short is aligned to multiple of %lu \n", sizeof(short));
	}

	return 0;
}

