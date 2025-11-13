#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 5

int *arr;

void *square_func(void *arg) {
	int *a = (int*)arg;
	int result = (*a) * (*a);
	printf("Square of %d is %d\n", *a, result);
	return NULL;
}

int main(void) {

	arr = malloc(sizeof(int)*SIZE);
	if(!arr) {
		perror("malloc");
		return 1;
	}

	for(int i = 0; i < SIZE; i++) {
		arr[i] = i + 1;
	}

	pthread_t *threads = malloc(sizeof(pthread_t)*SIZE);
	if(!threads) {
		perror("malloc");
		free(arr);
		arr = NULL;
		return 1;
	}

	for(int i = 0; i < SIZE; i++) {
		if(pthread_create(&threads[i], NULL, &square_func, (void*)&arr[i]) != 0) {
			perror("pthread_create");
			free(arr);
			free(threads);
			arr = NULL;
			threads = NULL;
			return 1;
		}
	}

	for(int i = 0; i < SIZE; i++) {
		if(pthread_join(threads[i], NULL) != 0) {
			perror("pthread_join");
			free(arr);
			free(threads);
			arr = NULL;
			threads = NULL;
			return 1;
		}
	}

	free(arr);
	free(threads);
	arr = NULL;
	threads = NULL;

	return 0;
}

