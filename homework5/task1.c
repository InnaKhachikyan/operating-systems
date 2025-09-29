#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int user_input;

	while(1) {
		printf("Please, enter a number: ");
		scanf("%d", &user_input);

		if(user_input <= 0) {
			printf("Invalid input\n");
			continue;
		}
		break;
	}
		
	int *arr = (int*)malloc(sizeof(int)*user_input);
	if(!arr) {
		perror("malloc");
		return 1;
	}

	printf("Please, enter %d integers\n", user_input);
	for(int i = 0; i < user_input; i++) {
		scanf("%d", &arr[i]);
	}
	
	int sum = 0;
	for(int i = 0 ; i < user_input; i++) {
		sum += *(arr + i);
	}

	printf("The sum is %d\n", sum);

	free(arr);
	arr = NULL;
}
