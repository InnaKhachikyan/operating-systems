#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int *arr = (int*)malloc(sizeof(int)*10);
	if(!arr) {
		perror("malloc");
		return 1;
	}
	
	printf("Please enter 10 values: ");
	for(int i = 0; i < 10; i++) {
		if(scanf("%d", &arr[i]) != 1) {
			printf("Not a number\n");
			return 1;
		}
	}

	arr =(int*)realloc(arr, sizeof(int)*5);

	printf("Array after resizing: ");
	for(int i = 0; i < 5; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);
	arr = NULL;
	return 0;
}
