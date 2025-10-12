#include <stdio.h>

typedef struct {
	char a;
	int b;
	double c;
} str1;

typedef struct {
	double a;
	int b;
	char c;
} str2;

typedef struct {
	int a;
	double b;
        char c;
} str3;	

int main(void) {
	str1 a_str = {'a', 42, 0.01};
	str2 b_str = {0.01, 42, 'c'};
	str3 c_str = {42, 0.01, 'c'};

	printf(" ***** STRUCT 1 ***** \n");
	printf("Size of the str1 is %zu \n", sizeof(str1));
	printf("Address of char a in str1: %p \n", (void*)&(a_str.a));
	printf("Address of int b in str1: %p \n", (void*)&(a_str.b));
	printf("Address of double c in str1: %p \n", (void*)&(a_str.c));

	printf(" ***** STRUCT 2 ***** \n");
	printf("Size of the str2 is %zu \n", sizeof(str2));
	printf("Address of double a in str2: %p \n", (void*)&(b_str.a));
	printf("Address of int b in str2: %p \n", (void*)&(b_str.b));
	printf("Address of char c in str2: %p \n", (void*)&(b_str.c));

	printf(" ***** STRUCT 3 ***** \n");
	printf("Size of the str3 is %zu \n", sizeof(str3));
	printf("Address of int a in str3: %p \n", (void*)&(c_str.a));
	printf("Address of double b in str3: %p \n", (void*)&(c_str.b));
	printf("Address of char c in str3: %p \n", (void*)&(c_str.c));

	return 0;
}
