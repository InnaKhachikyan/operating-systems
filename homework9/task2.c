#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE 100
int *arr;
int sum1 = 0;
int sum2 = 0;

typedef struct {
	int *arr_offset;
	int size;
} args;

void* arr_sum(void* arg) {
	printf("Thread %lu working\n", (unsigned long)pthread_self());
	args *param = (args*)arg;
	int* offset = param->arr_offset;
	int num_iter = param->size;
	if(offset == arr) {
		for(int i = 0; i < num_iter; i++) {
			sum1 += *(offset + i);
		}
		printf("SUM 1 is: %d \n", sum1);
	}
	else {
		for(int i = 0; i < num_iter; i++) {
			sum2 += *(offset + i);
		}
		printf("SUM 2 is: %d \n", sum2);
	}
	return NULL;
}

int main(void) {

	pthread_t thread1, thread2;

	arr = (int*)malloc(sizeof(int) * SIZE);
	if(!arr) {
		perror("malloc");
		return 1;
	}

	for(int i = 0; i < SIZE; i++) {
		*(arr+i) = i + 1;
	}

	args arg_th1 = {arr, SIZE/2};
	args arg_th2 = {arr + SIZE/2, SIZE - SIZE/2};

	if(pthread_create(&thread1, NULL, &arr_sum, (void*)&arg_th1) != 0) {
		perror("pthread_create");
		free(arr);
		arr = NULL;
		return 1;
	}

	if(pthread_create(&thread2, NULL, &arr_sum, (void*)&arg_th2) != 0) {
		perror("pthread_create");
		free(arr);
		arr = NULL;
		return 1;
	}

	if(pthread_join(thread1, NULL) != 0) {
		perror("pthread_join");
		free(arr);
		arr = NULL;
		return 1;
	}

	if(pthread_join(thread2, NULL) != 0) {
		perror("pthread_join");
		free(arr);
		arr = NULL;
		return 1;
	}

	int result = sum1 + sum2;
	printf("Threads finished counting, the result is %d\n", result);

	free(arr);
	arr = NULL;

	return 0;
}

