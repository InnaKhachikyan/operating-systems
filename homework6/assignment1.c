#include <stdio.h>
#include <stdint.h>

int main(void) {

	int type_int = 42;
	char type_char = 'i';
	double type_double = 0.0000001;
	short type_short = 23;

	printf("Size of the int type is: %zu bytes\n", sizeof(type_int));
	printf("Size of the char type is: %zu bytes\n", sizeof(type_char));
	printf("Size of the double type is: %zu bytes\n", sizeof(type_double));
	printf("Size of the short type is: %zu bytes\n", sizeof(type_short));

	printf("Address of the int type is: %p\n", (void*)&type_int);
	printf("Address of the char type is: %p\n", (void*)&type_char);
	printf("Address of the double type is: %p\n", (void*)&type_double);
	printf("Address of the short type is: %p\n", (void*)&type_short);


	if((size_t)&type_int % sizeof(int) == 0) {
		printf("Int is aligned to multiple of %zu \n", sizeof(int));
	}
	if((size_t)&type_char % sizeof(char) == 0) {
		printf("Char is aligned to multiple of %zu \n", sizeof(char));
	}
	if((size_t)&type_double % sizeof(double) == 0) {
		printf("Double is aligned to multiple of %zu \n", sizeof(double));
	}
	if((size_t)&type_short % sizeof(short) == 0) {
		printf("Short is aligned to multiple of %zu \n", sizeof(short));
	}

	return 0;
}

