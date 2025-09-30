#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {

	int user_input;

	while(1) {
		printf("Please, enter a number: ");
		if(scanf("%d", &user_input) != 1) {
			printf("Not a number\n");
			return 1;
		}

		if(user_input <= 0 || user_input > SIZE_MAX/sizeof(int)) {
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

	printf("Please, enter %d integers: ", user_input);
	for(int i = 0; i < user_input; i++) {
		if(scanf("%d", &arr[i]) != 1) {
			printf("Not a number\n");
			free(arr);arr = NULL;
			return 1;
		}
	}
	
	long long sum = 0;
	for(int i = 0 ; i < user_input; i++) {
		sum += *(arr + i);
	}

	printf("The sum is %lld\n", sum);

	free(arr);
	arr = NULL;
	return 0;
}
