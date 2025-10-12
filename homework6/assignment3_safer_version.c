#include <stdio.h>

typedef struct {
        char a;
        int b;
        double c;
} str1;

#pragma pack(push, 1)
typedef struct {
        char a;
        int b;
        double c;
} str_packed1;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct {
        char a;
        int b;
        double c;
} str_packed2;
#pragma pack(pop)

#pragma pack(push, 4)
typedef struct {
        char a;
        int b;
        double c;
} str_packed4;
#pragma pack(pop)

int main(void) {

	str1 a_str = {'a', 42, 0.01};
	str_packed1 b_str = {'a', 42, 0.01};
	str_packed2  c_str ={'a', 42, 0.01};
	str_packed4 d_str = {'a', 42, 0.01};

	printf(" ***** UNPACKED STRUCT ***** \n");
	printf("Size of struct str1 without packing is %zu \n", sizeof(str1));
	printf("Address of char type is %p\n", (void*)&a_str.a);
	printf("Address of int type is %p\n", (void*)&a_str.b);
	printf("Address of double type is %p\n", (void*)&a_str.c);

	printf(" ***** PACK(1) STRUCT ***** \n");
	printf("Size of struct str_packed1 with pack(1) is %zu \n", sizeof(str_packed1));
	printf("Address of char type is %p\n", (void*)&b_str.a);
	printf("Address of int type is %p\n", (void*)&b_str.b);
	printf("Address of double type is %p\n", (void*)&b_str.c);

	printf(" ***** PACK(2) STRUCT ***** \n");
	printf("Size of struct str_packed2 with pack(2) is %zu \n", sizeof(str_packed2));
	printf("Address of char type is %p\n", (void*)&c_str.a);
	printf("Address of int type is %p\n", (void*)&c_str.b);
	printf("Address of double type is %p\n", (void*)&c_str.c);

	printf(" ***** PACK(4) STRUCT ***** \n");
	printf("Size of struct str_packed4 with pack(4) is %zu \n", sizeof(str_packed4));
	printf("Address of char type is %p\n", (void*)&d_str.a);
	printf("Address of int type is %p\n", (void*)&d_str.b);
	printf("Address of double type is %p\n", (void*)&d_str.c);

	return 0;
}

