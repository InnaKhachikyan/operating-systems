#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int user_input;

	while(1) {
		printf("Please, enter a number: ");
		if(scanf("%d", &user_input) != 1) {
			printf("Not a number\n");
			return 1;
		}

		if(user_input <= 0) {
			printf("Invalid input\n");
			continue;
		}
		break;
	}
		
	int *arr = (int*)calloc(user_input, sizeof(int));
	if(!arr) {
		perror("calloc");
		return 1;
	}

	printf("Array after calloc: ");
	for(int i = 0 ; i < user_input; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("Please, enter %d integers: ", user_input);
	for(int i = 0; i < user_input; i++) {
		scanf("%d", &arr[i]);
	}
	
	int sum = 0;
	for(int i = 0 ; i < user_input; i++) {
		sum += *(arr + i);
	}

	printf("Updated array: ");
	for(int i = 0; i < user_input; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
		
	double average = (double)sum/user_input;

	printf("The average is %.10f\n", average);

	free(arr);
	arr = NULL;
}
