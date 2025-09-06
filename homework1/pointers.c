#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

int main() {
	//Assignment 1
	printf("***** Assignment 1 *****\n");
	int a;
	a = 42;
	int *ptr = &a;

	printf("The address of the var a is %p\n", &a);
	printf("The address of the var a is %p\n", ptr);

	*(ptr) = 23;

	printf("The new value of var a is %d\n", a);
	printf("\n");

	//Assignment 2
	
	printf("***** Assignment 2 *****\n");
	
	int arr[5] = {0, 1, 2, 3, 4};
	for(int i = 0; i < 5; i++) {
		printf("%d ", *(arr + i));
	}
	printf("\n");

	for(int i = 0; i < 5; i++) {
		*(arr + i) += 1;
	}

	for(int i = 0; i < 5; i++) {
		printf("%d ", *(arr+i));
	}
	printf("\n");
	for(int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n\n");

	//Assignment 3
	
	printf("***** Assignment 3 *****\n");
	int b = 42;
	printf("BEFORE SWAP\nValue of var a is %d\nValue of var b is %d\n", a, b);
	swap(&a, &b);
	printf("AFTER SWAP\nValue of var a is %d\nValue of var b is %d\n", a, b);
	printf("\n");

	//Assignment 4
	printf("***** Assignment 4 *****\n");
	int var;
	int *ptr_to_var = &var;
	int **double_ptr = &ptr_to_var;
	*(*(double_ptr)) = 23;
	printf("Value of var by single pointer %d\n", *(ptr_to_var));
	printf("Value of var by double pointer %d\n", *(*(double_ptr)));
	printf("\n");

	//Assignment 5
	printf("***** Assignment 5 *****\n");

	char str[] = "Hello";
	char *str_ptr = str; // or we could assign = &str[0];

	for(int i = 0; *(str_ptr + i) != '\0'; i++) {
		printf("%c", *(str_ptr + i));
	}
	printf("\n");
	int len = 0;
	int i = 0;
	while(*(str_ptr + i) != '\0') {
		len++;
		i++;
	}
	printf("The length of the string is %d\n", len);
	printf("\n");
}

